#include <iostream>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include"CServer.h"
#include "ConfigMgr.h"

int main()
{
    try
    {
        auto& gCfgMgr = ConfigMgr::Inst(); // 这里要用引用变量，因为ConfigMgr没有拷贝构造
        std::string gate_port_str = gCfgMgr["GateServer"]["Port"];
        unsigned short gate_port = atoi(gate_port_str.c_str());

        net::io_context ioc{ 1 };
        // 异步等待，捕获ctrl+c
        boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
        signals.async_wait([&ioc](const boost::system::error_code& error, int signal_number) {
            if (error) {
                return;
            }
            ioc.stop();
            }); 
        // 创建并初始化server，启动
        std::make_shared<CServer>(ioc, gate_port)->Start();
        std::cout << "Gate Server listen on port: " << gate_port << std::endl;
        // 启动ioc
        ioc.run(); 
    }
    catch (std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

