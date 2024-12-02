// config.js用来读取配置
const fs = require('fs');

let config = JSON.parse(fs.readFileSync('config.json', 'utf8')); // 解析config.json
let email_user = config.email.user;
let email_pass = config.email.pass;
let mysql_host = config.mysql.host;
let mysql_port = config.mysql.port;
let redis_host = config.redis.host;
let redis_port = config.redis.port;
let redis_passwd = config.redis.passwd;
let code_prefix = "code_";
module.exports = { email_pass, email_user, mysql_host, mysql_port, redis_host, redis_port, redis_passwd, code_prefix }