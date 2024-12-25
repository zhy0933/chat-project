#include "httpmgr.h"

HttpMgr::~HttpMgr()
{

}

HttpMgr::HttpMgr() {
    //在构造函数中连接http请求和完成信号，信号槽机制保证队列消费
    connect(this, &HttpMgr::sig_http_finish, this, &HttpMgr::slot_http_finish);
}


/**
 * @brief PostHttpReq 发送HTTP POST请求，并获取回复
 * @param url 请求的URL
 * @param json 请求的JSON对象
 * @param req_id 请求ID，用于标识不同请求类型
 * @param mod 模块信息，用于标识请求的分类模块
 */
void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod)
{
    //创建一个HTTP POST请求，并设置请求头和请求体
    QByteArray data = QJsonDocument(json).toJson();
    //通过url构造请求
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));


    // 获取自己的智能指针，构造伪闭包并增加智能指针引用计数
    auto self = shared_from_this();
    // 发送请求，并处理响应
    QNetworkReply * reply = _manager.post(request, data);
    //设置信号和槽等待发送完成
    // connect 时传入三个参数，是因为 lambda 表达式可以直接用作槽函数，不需要指定接收对象
    // QNetworkReply::finished 信号触发时，执行捕获的 lambda 表达式
    QObject::connect(reply, &QNetworkReply::finished, [reply, self, req_id, mod](){
        //处理错误的情况                              // 这里不能直接用self捕获this，不安全，因为httpmgr可能会被释放，要有伪闭包的方式实现httpmgr生命周期延长
        if(reply->error() != QNetworkReply::NoError){
            qDebug() << reply->errorString();
            //发送信号通知其它界面http请求发送发生错误
            emit self->sig_http_finish(req_id, "", ErrorCodes::ERR_NETWORK, mod);
            reply->deleteLater();
            return;
        }

        //无错误则读回请求
        QString res = reply->readAll();

        //发送信号通知其它界面http请求发送完成
        emit self->sig_http_finish(req_id, res, ErrorCodes::SUCCESS, mod);
        reply->deleteLater();
        return;
    });
}

// 当http请求完成时，根据请求类型，发送不同类型的信号通知对应模块
void HttpMgr::slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod)
{
    // 发送信号通知注册模块http注册类型的请求完成发送
    if(mod == Modules::REGISTERMOD){
        emit sig_reg_mod_finish(id, res, err);
    }
}
