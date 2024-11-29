// 该类负责根据不同的 URL 路由请求并执行相应的业务逻辑
#include"const.h"   

// 定义一个 HttpHandler 类型，它表示一个接受 用于读写的http连接类 作为参数并且返回 void 的函数类型
class HttpConnection;
typedef std::function<void(std::shared_ptr<HttpConnection>)> HttpHandler; 

class LogicSystem :public Singleton<LogicSystem>
{
	friend class Singleton<LogicSystem>; // 这样单例类才能访问逻辑类的构造函数
public:
    /// <summary>
    /// 析构
    /// </summary>
    ~LogicSystem();

    /// <summary>
    /// 处理get请求
    /// </summary>
    /// <param name="">url</param>
    /// <param name="">用于读写的http连接类</param>
    /// <returns></returns>
    bool HandleGet(std::string, std::shared_ptr<HttpConnection>);

    /// <summary>
    /// 注册get请求
    /// </summary>
    /// <param name="">url路径</param>
    /// <param name="handler">对应的回调函数</param>
    void RegGet(std::string, HttpHandler handler);

    /// <summary>
    /// 处理post请求
    /// </summary>
    /// <param name="">url</param>
    /// <param name="">用于读写的http连接类</param>
    /// <returns></returns>
    bool HandlePost(std::string, std::shared_ptr<HttpConnection>);

    /// <summary>
    /// 注册post请求
    /// </summary>
    /// <param name="">url路径</param>
    /// <param name="handler">对应的回调函数</param>
    void RegPost (std::string, HttpHandler handler);


    
private:
    LogicSystem();
    // post请求的回调函数map，key为路由，value为回调函数，不同url调用不同回调
    std::map<std::string, HttpHandler> _post_handlers;
    // get请求的回调函数map
    std::map<std::string, HttpHandler> _get_handlers;
};

