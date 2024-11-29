﻿#include <iostream>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include"CServer.h"
int main()
{
    try
    {
        // 初始化端口和ioc
        unsigned short port = static_cast<unsigned short>(8080);
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
        std::make_shared<CServer>(ioc, port)->Start();
        std::cout << "Gate Server listen on port: " << port << std::endl;
        // 启动ioc
        ioc.run(); 
    }
    catch (std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
/*
* 启动服务器，在浏览器输入`http://localhost:8080/get_test`
会看到服务器回包`receive get_test req`
如果我们输入带参数的url请求`http://localhost:8080/get_test?key1=value1&key2=value2`
会收到服务器反馈`url not found`
所以对于get请求带参数的情况我们要实现参数解析，我们可以自己实现简单的url解析函数
*/

