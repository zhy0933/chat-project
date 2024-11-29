#include "HttpConnection.h"
# include"LogicSystem.h"
HttpConnection::HttpConnection(tcp::socket socket)
    : _socket(std::move(socket)) { // 移动构造，socket没有拷贝构造

}

void HttpConnection::Start()
{
    auto self = shared_from_this();
    // 异步读取socket中数据，读取完后触发回调
    http::async_read(_socket, _buffer, _request, [self](beast::error_code ec, 
        std::size_t bytes_transferred) { // 已经发送的字节数
            try {
                if (ec) {
                    std::cout << "http read err is " << ec.what() << std::endl;
                    return;
                }
                //处理读到的数据
                boost::ignore_unused(bytes_transferred); // 因为是http服务器不需要粘包处理，忽略已发送字节数
                self->HandleReq(); // 处理请求
                self->CheckDeadline(); // 启动超时检测
            }
            catch (std::exception& exp) {
                std::cout << "exception is " << exp.what() << std::endl;
            }
        }
    );
}

// 将10进制的char转为16进制
unsigned char ToHex(unsigned char x)
{
    return  x > 9 ? x + 55 : x + 48;
}
// 将16进制的char转为10进制
unsigned char FromHex(unsigned char x)
{
    unsigned char y;
    if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
    else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
    else if (x >= '0' && x <= '9') y = x - '0';
    else assert(0);
    return y;
}

// 对url中参数进行编码，放gpt上解析即可，不用自己写
std::string UrlEncode(const std::string& str)
{
    std::string strTemp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        //判断是否仅有数字和字母构成
        if (isalnum((unsigned char)str[i]) ||
            (str[i] == '-') ||
            (str[i] == '_') ||
            (str[i] == '.') ||
            (str[i] == '~'))
            strTemp += str[i];
        else if (str[i] == ' ') //为空字符
            strTemp += "+";
        else // 如中文字符
        {
            //其他字符需要提前加%并且高四位和低四位分别转为16进制
            strTemp += '%';
            strTemp += ToHex((unsigned char)str[i] >> 4);
            strTemp += ToHex((unsigned char)str[i] & 0x0F);
        }
    }
    return strTemp;
}

// url解码的工作正好相反
std::string UrlDecode(const std::string& str)
{
    std::string strTemp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        //还原+为空
        if (str[i] == '+') strTemp += ' ';
        //遇到%将后面的两个字符从16进制转为char再拼接
        else if (str[i] == '%')
        {
            assert(i + 2 < length);
            unsigned char high = FromHex((unsigned char)str[++i]);
            unsigned char low = FromHex((unsigned char)str[++i]);
            strTemp += high * 16 + low;
        }
        else strTemp += str[i];
    }
    return strTemp;
}

void HttpConnection::PreParseGetParam() {
    // 提取 URI  例如：/get_test?key1=value1&key2=value2
    auto uri = _request.target();
    // 查找查询字符串的开始位置（即 '?' 的位置）  
    auto query_pos = uri.find('?');
    if (query_pos == std::string::npos) { // 如果没有问号
        _get_url = uri;
        return;
    }

    _get_url = uri.substr(0, query_pos);
    std::string query_string = uri.substr(query_pos + 1);
    std::string key;
    std::string value;
    size_t pos = 0;
    // 按照 & 分隔查询字符串，将每个 key=value 对单独处理
    while ((pos = query_string.find('&')) != std::string::npos) {
        auto pair = query_string.substr(0, pos);
        size_t eq_pos = pair.find('=');
        if (eq_pos != std::string::npos) {
            key = UrlDecode(pair.substr(0, eq_pos)); // 假设有 url_decode 函数来处理URL解码  
            value = UrlDecode(pair.substr(eq_pos + 1));
            _get_params[key] = value;
        }
        query_string.erase(0, pos + 1);
    }
    // 处理最后一个参数对（如果没有 & 分隔符）  
    if (!query_string.empty()) {
        size_t eq_pos = query_string.find('=');
        if (eq_pos != std::string::npos) {
            key = UrlDecode(query_string.substr(0, eq_pos));
            value = UrlDecode(query_string.substr(eq_pos + 1));
            _get_params[key] = value;
        }
    }
}

void HttpConnection::HandleReq() {
    //设置版本
    _response.version(_request.version());
    //设置为短链接
    _response.keep_alive(false);

    // 判断请求类型
    if (_request.method() == http::verb::get) { 
        PreParseGetParam(); // 解析url获取路径和参数
        bool success = LogicSystem::GetInstance()->HandleGet(_get_url, shared_from_this()); // 使用逻辑类处理请求
        if (!success) {
            _response.result(http::status::not_found); // 状态码
            _response.set(http::field::content_type, "text/plain"); // 回应类型
            beast::ostream(_response.body()) << "url not found\r\n"; // 消息体
            WriteResponse(); // 写回复
            return;
        }
        // 如果没出错
        _response.result(http::status::ok);
        _response.set(http::field::server, "GateServer"); // 哪个服务器发出的
        WriteResponse(); // 具体处理放在写回复中
        return;
    }
    // 判断请求类型
    if (_request.method() == http::verb::post) {
        bool success = LogicSystem::GetInstance()->HandlePost(_request.target(), shared_from_this()); // post请求不需要解析参数，直接用_request.target()
        if (!success) {
            _response.result(http::status::not_found); // 状态码
            _response.set(http::field::content_type, "text/plain"); // 回应类型
            beast::ostream(_response.body()) << "url not found\r\n"; // 消息体
            WriteResponse(); // 写回复
            return;
        }
        // 如果没出错
        _response.result(http::status::ok);
        _response.set(http::field::server, "GateServer"); // 哪个服务器发出的
        WriteResponse(); // 具体处理放在写回复中
        return;
    }
}

void HttpConnection::WriteResponse() {
    auto self = shared_from_this();
    _response.content_length(_response.body().size()); // 设置长度，http底层根据这个切包来处理粘包
    http::async_write( // 异步写入socket
        _socket,
        _response,
        [self](beast::error_code ec, std::size_t) // size_t表示已发送数据
        {
            self->_socket.shutdown(tcp::socket::shutdown_send, ec); // 发送完毕，关闭发送端
            self->deadline_.cancel(); // 取消定时器
        });
}

void HttpConnection::CheckDeadline() {
    auto self = shared_from_this();
    deadline_.async_wait( // 使用定时器异步等待，上面的异步写长时间没有结束以取消定时器，就调用回调关闭close
        [self](beast::error_code ec)
        {
            if (!ec)
            {
                // Close socket to cancel any outstanding operation.
                self->_socket.close(ec); // 服务器这样直接关可能导致timewait，扩展学习
            }
        });
}