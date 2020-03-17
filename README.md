# Socket_chat
基于socket实现的qt5聊天程序  

基于socket实现的qt5多线程聊天程序
vs2015 或者 qt5运行，加入账号密码注册登陆，实时刷新在线，多线程聊天，解决中文乱码问题

--创建数据库  

CREATE DATABASE test;  
SHOW DATABASES;  
USE test;

CREATE TABLE IF NOT EXISTS `we`(
   `id` varchar(50)   NOT NULL  ,
   `passwd` varchar(50) NOT NULL,
   `ol` varchar(50) NOT NULL,
   PRIMARY KEY ( `id` )
)ENGINE=InnoDB DEFAULT CHARSET=utf8;

--server/socketthread.cpp
db.setHostName("localhost");  
db.setDatabaseName("test");  
db.setUserName("root");  
db.setPassword("123456");//注意这里的密码  



--修改client中server的ip和端口  
#define IP "192.168.0.153"  
#define PORT 2333  

--先启动server  
--再启动client  
加了很多调试日志，可以适当删除

