#ifndef HTTPMGR_H
#define HTTPMGR_H
#include "singleton.h"
#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include "global.h"
#include <memory>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>

// 通过CRTP来实现
class HttpMgr:public QObject, public Singleton<HttpMgr>, // 用它自身实例化模板类，通过CRTP来实现（见笔记）
            public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT

public:
    ~HttpMgr(); // 析构设为公有是因为singleton中的instance是httpmgr类型的，释放它时要调用httpmgr的析构函数

    /**
     * @brief PostHttpReq 发送HTTP POST请求，并获取回复
     * @param url 请求的URL
     * @param json 请求的JSON对象
     * @param req_id 请求ID，用于标识不同请求类型
     * @param mod 模块信息，用于请求的分类
     */
    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);

private:
    friend class Singleton<HttpMgr>; //设为友元是因为singleton中的instance构造时，要调用httpmgr的构造函数
    HttpMgr();
    QNetworkAccessManager _manager; // 用于管理网络请求的对象

public slots:
    /**
     * @brief slot_http_finish HTTP请求完成槽函数
     * @param id 请求ID，用于标识该信号对应的请求
     * @param res 请求返回结果字符串
     * @param err 错误代码，标识请求是否成功
     * @param mod 模块信息，用于区分不同的模块请求
     */
    void slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);

signals:
    /**
     * @brief sig_http_finish HTTP请求完成信号
     * @param id 请求ID，用于标识该信号对应的请求
     * @param res 请求返回结果字符串
     * @param err 错误代码，标识请求是否成功
     * @param mod 模块信息，用于区分不同的模块请求
     */
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);


    /**
     * @brief sig_reg_mod_finish 注册模块的http相关请求完成发送此信号
     * @param id 请求ID，用于标识该信号对应的请求
     * @param res 请求返回结果字符串
     * @param err 错误代码，标识请求是否成功
     */
    void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
};

#endif // HTTPMGR_H
