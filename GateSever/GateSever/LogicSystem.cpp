#include "LogicSystem.h"
#include "HttpConnection.h" // 在.h中前置声明，在.cpp中包含，解决互引用
#include "VerifyGrpcClient.h"
#include "RedisMgr.h"

void LogicSystem::RegGet(std::string url, HttpHandler handler) {
    _get_handlers.insert(make_pair(url, handler)); // 把url路径对应的回调插入map
}

void LogicSystem::RegPost(std::string url, HttpHandler handler) {
    _post_handlers.insert(make_pair(url, handler)); // 把url路径对应的回调插入map
}

// 在构造时为不同路径对应的回调进行注册
LogicSystem::LogicSystem() {

    // 注册/get_test对应的逻辑
    RegGet("/get_test", [](std::shared_ptr<HttpConnection> connection) { 
        beast::ostream(connection->_response.body()) << "receive get_test req" << std::endl; // 将回复信息输入response内
        int i = 0;
        for (auto& elem : connection->_get_params) { // 通过友元访问HttpConnection私有变量
            i++;
            beast::ostream(connection->_response.body()) << "param" << i << " key is " << elem.first;
            beast::ostream(connection->_response.body()) << ", " << " value is " << elem.second << std::endl;
        }
    }); 

    // 注册/get_varifycode对应的逻辑
    RegPost("/get_varifycode", [](std::shared_ptr<HttpConnection> connection) {
        auto body_str = boost::beast::buffers_to_string(connection->_request.body().data()); // 将请求的body转换为string类型
        std::cout << "receive body is " << body_str << std::endl;
        connection->_response.set(http::field::content_type, "text/json"); // 将回复类型设为json类

        Json::Value root; // 用于构建并发送的 JSON 响应对象，将作为服务器回复内容
        Json::Reader reader;
        Json::Value src_root; // 用于存储解析后的客户端发送的 JSON 数据
        // 将body解析为json对象并存入src_root中
        bool parse_success = reader.parse(body_str, src_root); 
        if (!parse_success) {
            std::cout << "Failed to parse JSON data!" << std::endl;
            root["error"] = ErrorCodes::Error_Json; // 设置错误类型
            std::string jsonstr = root.toStyledString(); // 将json对象转换为string类型，再放入回复的body里
            beast::ostream(connection->_response.body()) << jsonstr;
            return true;
        }
        // 判断是否存在email键
        if (!src_root.isMember("email")) {
            std::cout << "Failed to parse key email!" << std::endl;
            root["error"] = ErrorCodes::Error_Json; // 设置错误类型
            std::string jsonstr = root.toStyledString(); // 将json对象转换为string类型，再放入回复的body里
            beast::ostream(connection->_response.body()) << jsonstr;
            return true;
        }

        auto email = src_root["email"].asString();
        GetVarifyRsp rsp = VerifyGrpcClient::GetInstance()->GetVarifyCode(email); // Gate服务器通过grpc将邮箱发给Verify服务器
        std::cout << "email is " << email << std::endl;
        root["error"] = rsp.error();
        root["email"] = src_root["email"]; // 将email返回
        std::string jsonstr = root.toStyledString();
        beast::ostream(connection->_response.body()) << jsonstr; // 将回复放到response中
        return true;
    });

    // Server注册user_register对应的逻辑
    RegPost("/user_register", [](std::shared_ptr<HttpConnection> connection) {
        // 取出请求的body
        auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
        std::cout << "receive body is " << body_str << std::endl;
        // 设置回复
        connection->_response.set(http::field::content_type, "text/json");
        Json::Value root;
        Json::Reader reader;
        Json::Value src_root;
        // 解析body
        bool parse_success = reader.parse(body_str, src_root);
        if (!parse_success) { 
            std::cout << "Failed to parse JSON data!" << std::endl;
            root["error"] = ErrorCodes::Error_Json;
            std::string jsonstr = root.toStyledString();
            beast::ostream(connection->_response.body()) << jsonstr;
            return true;
        }

        auto email = src_root["email"].asString();
        auto name = src_root["user"].asString();
        auto pwd = src_root["passwd"].asString();
        auto confirm = src_root["confirm"].asString();
        // 判断密码和确认密码是否一致
        if (pwd != confirm) {
            std::cout << "password err " << std::endl;
            root["error"] = ErrorCodes::PasswdErr;
            std::string jsonstr = root.toStyledString();
            beast::ostream(connection->_response.body()) << jsonstr;
            return true;
        }
        // 查找redis中email对应的验证码是否合理
        std::string  varify_code;
        bool b_get_varify = RedisMgr::GetInstance()->Get(CODEPREFIX + src_root["email"].asString(), varify_code);
        if (!b_get_varify) { // 验证码是否过期
            std::cout << " get varify code expired" << std::endl;
            root["error"] = ErrorCodes::VarifyExpired;
            std::string jsonstr = root.toStyledString();
            beast::ostream(connection->_response.body()) << jsonstr;
            return true;
        }
        if (varify_code != src_root["varifycode"].asString()) { // 验证码是否匹配
            std::cout << " varify code error" << std::endl;
            root["error"] = ErrorCodes::VarifyCodeErr;
            std::string jsonstr = root.toStyledString();
            beast::ostream(connection->_response.body()) << jsonstr;
            return true;
        }
        // 如果匹配，写回复
        root["error"] = 0;
        root["email"] = email;
        root["user"] = name;
        root["passwd"] = pwd;
        root["confirm"] = confirm;
        root["varifycode"] = src_root["varifycode"].asString();
        std::string jsonstr = root.toStyledString();
        beast::ostream(connection->_response.body()) << jsonstr;
        return true;
        });
}

LogicSystem::~LogicSystem()
{

}

bool LogicSystem::HandleGet(std::string path, std::shared_ptr<HttpConnection> con) {
    if (_get_handlers.find(path) == _get_handlers.end()) {
        return false;
    }
    _get_handlers[path](con); // 处理get请求，通过url路径找到对应回调函数，传入http连接类con用于读写通信
    return true;
}

bool LogicSystem::HandlePost(std::string path, std::shared_ptr<HttpConnection> con) {
    if (_post_handlers.find(path) == _post_handlers.end()) {
        return false;
    }
    _post_handlers[path](con); // 处理post请求，通过url路径找到对应回调函数，传入http连接类con用于读写通信
    return true;
}

