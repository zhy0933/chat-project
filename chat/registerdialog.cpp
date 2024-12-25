#include "registerdialog.h"
#include "ui_registerdialog.h"
#include"global.h"
#include <QRegularExpression>
#include "httpmgr.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    // 设置文本框的回显模式为密码模式
    ui->pass_edit->setEchoMode(QLineEdit::Password);
    ui->confirm_edit->setEchoMode(QLineEdit::Password);
    // 设置错误提示的属性和样式并更新样式
    ui->err_tip->setProperty("state","normal");
    repolish(ui->err_tip);
    // 连接注册完成的信号和槽
    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish, this, &RegisterDialog::slot_reg_mod_finish);
    initHttpHandlers();
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

/**
 * @brief RegisterDialog::on_get_code_clicked
 * 验证码点击的槽函数
 */
void RegisterDialog::on_get_code_clicked()
{
    // 获取ui文本
    // 验证邮箱的地址正则表达式
    auto email = ui->email_edit->text();
    // 邮箱地址的正则表达式
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch(); // 执行正则表达式匹配
    if(match){
        //发送http请求获取验证码
        QJsonObject json_obj;
        json_obj["email"] = email;
        HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix+"/get_varifycode"),
                                            json_obj, ReqId::ID_GET_VARIFY_CODE,Modules::REGISTERMOD);

    }else{
        //提示邮箱不正确
        showTip(tr("邮箱地址不正确"), false);
    }
}

/**
 * @brief RegisterDialog::slot_reg_mod_finish 注册完成对应的槽函数
 * @param id
 * @param res
 * @param err
 */
void RegisterDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS){
        showTip(tr("网络请求错误"),false);
        return;
    }

    // 解析 JSON 字符串, res需转化为QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    //json解析错误
    if(jsonDoc.isNull()){
        showTip(tr("json解析错误"),false);
        return;
    }

    // json解析错误
    if(!jsonDoc.isObject()){
        showTip(tr("json解析错误"),false);
        return;
    }


    // 根据不同的Reqid调用对应的逻辑
    _handlers[id](jsonDoc.object());

    return;
}


void RegisterDialog::showTip(QString str, bool b_ok)
{
    if(b_ok){
        ui->err_tip->setProperty("state","normal");
    }else{
        ui->err_tip->setProperty("state","err");
    }

    ui->err_tip->setText(str);

    repolish(ui->err_tip);
}

/**
 * @brief RegisterDialog::initHttpHandlers 注册不同id处理函数
 */
void RegisterDialog::initHttpHandlers()
{
    // 为ID_GET_VARIFY_CODE（即获取验证码成功）注册对应的回包逻辑
    _handlers.insert(ReqId::ID_GET_VARIFY_CODE, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            showTip(tr("参数错误"),false);
            return;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("验证码已发送到邮箱，注意查收"), true);
        qDebug()<< "email is " << email ;
    });

    // 为ID_REG_USER注册"注册用户"回包逻辑
    _handlers.insert(ReqId::ID_REG_USER, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            showTip(tr("参数错误"),false);
            return;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("用户注册成功"), true);
        qDebug()<< "email is " << email ;
    });

}

// 注册界面确认按钮对应槽函数
void RegisterDialog::on_sure_btn_clicked()
{
    if(ui->user_edit->text() == ""){
        showTip(tr("用户名不能为空"), false);
        return;
    }
    if(ui->email_edit->text() == ""){
        showTip(tr("邮箱不能为空"), false);
        return;
    }
    if(ui->pass_edit->text() == ""){
        showTip(tr("密码不能为空"), false);
        return;
    }
    if(ui->confirm_edit->text() == ""){
        showTip(tr("确认密码不能为空"), false);
        return;
    }
    if(ui->confirm_edit->text() != ui->pass_edit->text()){
        showTip(tr("密码和确认密码不匹配"), false);
        return;
    }
    if(ui->varify_edit->text() == ""){
        showTip(tr("验证码不能为空"), false);
        return;
    }

    // 客户端发送post请求
    QJsonObject json_obj;
    json_obj["user"] = ui->user_edit->text();
    json_obj["email"] = ui->email_edit->text();
    json_obj["passwd"] = ui->pass_edit->text();
    json_obj["confirm"] = ui->confirm_edit->text();
    json_obj["varifycode"] = ui->varify_edit->text();
    // 属于用户注册ID，注册模块
    HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix+"/user_register"),
                                        json_obj, ReqId::ID_REG_USER,Modules::REGISTERMOD);
}

