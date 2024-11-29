//  负责与单个客户端之间的 HTTP 请求和响应的读写

# include"const.h"

class HttpConnection : public std::enable_shared_from_this<HttpConnection>
{
    friend class LogicSystem;
public:
    HttpConnection(tcp::socket socket);
    void Start();
private:
    /// <summary>
    /// 检查是否超时
    /// </summary>
    void CheckDeadline();

    /// <summary>
    /// 写回复并发送
    /// </summary>
    void WriteResponse(); 

    /// <summary>
    /// 处理请求，将收到的请求交给LogicSystem 类处理
    /// </summary>
    void HandleReq(); 

    /// <summary>
    /// 预解析获取参数
    /// </summary>
    void PreParseGetParam();

    tcp::socket  _socket;
    // The buffer for performing reads.
    beast::flat_buffer  _buffer{ 8192 };
    // request 消息. beast提供的动态类型的请求
    http::request<http::dynamic_body> _request; 
    // response 消息
    http::response<http::dynamic_body> _response;
    // 设置定时器，用调度器和超时时间初始化
    net::steady_timer deadline_{ 
        _socket.get_executor(), std::chrono::seconds(60) };

    std::string _get_url; // 用来存储url路径部分
    std::unordered_map<std::string, std::string> _get_params; // 用来存储url查询字符串部分，即参数键值对
};

