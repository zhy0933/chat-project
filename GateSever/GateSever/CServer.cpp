#include "CServer.h"
#include "HttpConnection.h"
#include "AsioIOServicePool.h"

CServer::CServer(boost::asio::io_context& ioc, unsigned short& port) :_ioc(ioc),
_acceptor(ioc, tcp::endpoint(tcp::v4(), port)){ // 构造时绑定端口和用于监听的ioc

}

void CServer::Start()
{
    auto self = shared_from_this(); // 伪闭包，用shared共享引用计数

    auto& io_context = AsioIOServicePool::GetInstance()->GetIOService(); // 从iocontext池中获取一个iocontext
    std::shared_ptr<HttpConnection> new_con = std::make_shared<HttpConnection>(io_context); // 用ioc创建一个HttpConnection，在它内部会创建一个socket与iocontext绑定
   
    // 异步监听连接，当有连接到来时，将该连接绑定到传递的 new_con->GetSocket()用于通信
    _acceptor.async_accept(new_con->GetSocket(), [self, new_con](beast::error_code ec) { 
        try {
            //出错则放弃这个连接，继续监听新链接
            if (ec) {
                self->Start();
                return;
            }
            //处理新链接，创建HpptConnection类管理新连接，并启动读写
            new_con->Start(); 
            //继续监听
            self->Start();
        }
        catch (std::exception& exp) {
            std::cout << "exception is " << exp.what() << std::endl;
            self->Start();
        }
        });
}
