#ifndef GLOBAL_H
#define GLOBAL_H
// 把所有可能用到的库放在global中
#include <QWidget>
#include <functional>
#include "QStyle"
#include <memory>
#include <iostream>
#include <mutex>


/**
 * @brief repolish用来根据属性刷新qss
 */
extern std::function<void(QWidget*)> repolish;

/**
 * @brief The ReqId enum 表示请求的id
 */
enum ReqId{
    ID_GET_VARIFY_CODE = 1001, //获取验证码
    ID_REG_USER = 1002, //注册用户
};

/**
 * @brief The ErrorCodes enum 表示错误返回码
 */
enum ErrorCodes{
    SUCCESS = 0,
    ERR_JSON = 1, //Json解析失败
    ERR_NETWORK = 2,
};

/**
 * @brief The Modules enum 模块类型
 */
enum Modules{
    REGISTERMOD = 0,
};

#endif // GLOBAL_H
