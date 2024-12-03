//  负责启动服务器并接受客户端连接

#include "const.h"

class CServer :public std::enable_shared_from_this<CServer> // 可以获取自己的模板奇异递归模板类
{
    public:
        /// <summary>
        /// 构造函数，绑定io和端口
        /// </summary>
        /// <param name="ioc">io上下文</param>
        /// <param name="port">端口</param>
        CServer(boost::asio::io_context & ioc, unsigned short& port);

        /// <summary>
        /// 启动服务器开始监听
        /// </summary>
        void Start();
    private:
        tcp::acceptor  _acceptor;
        net::io_context& _ioc; // 注意这个是引用类型
        
};

