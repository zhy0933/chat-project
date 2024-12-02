// 发邮件的模块

const nodemailer = require('nodemailer');
const config_module = require("./config")
/**
 * 创建发送邮件的代理
 */
let transport = nodemailer.createTransport({
    host: 'smtp.163.com',
    port: 465,
    secure: true,
    auth: {
        user: config_module.email_user, // 发送方邮箱地址
        pass: config_module.email_pass // 邮箱授权码或者密码
    }
});

/**
 * 发送邮件的函数
 * @param {*} mailOptions_ 发送邮件的参数
 * @returns 
 */
function SendMail(mailOptions_) {
    // 邮件发送是异步的，使用 Promise 来封装 sendMail 的回调，从而使得调用者能够处理异步操作的结果。
    return new Promise(function (resolve, reject) {  // 成功时会 resolve，失败时会 reject
        transport.sendMail(mailOptions_, function(error, info){
            if (error) {
                console.log(error);
                reject(error);
            } else {
                console.log('邮件已成功发送：' + info.response);
                resolve(info.response)
            }
        });
    })
}
module.exports.SendMail = SendMail // 将 SendMail 函数暴露给其他模块，允许外部文件使用该函数来发送邮件