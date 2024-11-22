#include "registerdialog.h"
#include "ui_registerdialog.h"
#include"global.h"
#include <QRegularExpression>

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->pass_lineEdit->setEchoMode(QLineEdit::Password);
    ui->confirm_lineEdit->setEchoMode(QLineEdit::Password);
    ui->err_tip->setProperty("state","normal");
    repolish(ui->err_tip);

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
    auto email = ui->email_lineEdit->text();
    // 邮箱地址的正则表达式
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch(); // 执行正则表达式匹配
    if(match){
        //发送http请求获取验证码
    }else{
        //提示邮箱不正确
        showTip(tr("邮箱地址不正确"), false);
    }
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

