#include "LogicSystem.h"
#include "HttpConnection.h" // 在.h中前置声明，在.cpp中包含，解决互引用
#include "VerifyGrpcClient.h"

void LogicSystem::RegGet(std::string url, HttpHandler handler) {
    _get_handlers.insert(make_pair(url, handler)); // 把url路径对应的回调插入map
}

void LogicSystem::RegPost(std::string url, HttpHandler handler) {
    _post_handlers.insert(make_pair(url, handler)); // 把url路径对应的回调插入map
}

// 在构造时为不同路径对应的回调进行注册
LogicSystem::LogicSystem() {

    // 注册/get_test对应的回调函数
    RegGet("/get_test", [](std::shared_ptr<HttpConnection> connection) { 
        beast::ostream(connection->_response.body()) << "receive get_test req" << std::endl; // 将回复信息输入response内
        int i = 0;
        for (auto& elem : connection->_get_params) { // 通过友元访问HttpConnection私有变量
            i++;
            beast::ostream(connection->_response.body()) << "param" << i << " key is " << elem.first;
            beast::ostream(connection->_response.body()) << ", " << " value is " << elem.second << std::endl;
        }
    }); 

    // 注册/get_varifycode对应的回调函数
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

