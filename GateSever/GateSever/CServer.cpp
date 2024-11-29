#include "CServer.h"
#include "HttpConnection.h"

CServer::CServer(boost::asio::io_context& ioc, unsigned short& port) :_ioc(ioc),
_acceptor(ioc, tcp::endpoint(tcp::v4(), port)), _socket(ioc) { // 构造时绑定端口

}

void CServer::Start()
{
    auto self = shared_from_this(); // 伪闭包，用shared共享引用计数
    _acceptor.async_accept(_socket, [self](beast::error_code ec) { // 异步监听连接
        try {
            //出错则放弃这个连接，继续监听新链接
            if (ec) {
                self->Start();
                return;
            }
            //处理新链接，创建HpptConnection类管理新连接，并启动读写
            std::make_shared<HttpConnection>(std::move(self->_socket))->Start(); // socket没有拷贝构造，所以用move右值
            //继续监听
            self->Start();
        }
        catch (std::exception& exp) {
            std::cout << "exception is " << exp.what() << std::endl;
            self->Start();
        }
        });
}
