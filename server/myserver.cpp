
#include"myserver.h"
#include<QMessageBox>
#include"socketthread.h"

Myserver::Myserver(QWidget * parent):QTcpServer(parent){


}

void Myserver::incomingConnection(qintptr socketDescriptor)
{
    //QMessageBox::about(0,"提示","有新连接");
    SocketThread * thread=new SocketThread(0,socketDescriptor);

    thread->mysocket=new QTcpSocket();
    thread->mysocket->setSocketDescriptor(socketDescriptor);//客户端的初始化
    socket_map[socketDescriptor]=thread->mysocket;

    //qDebug()<<array[1]<<"asdasdasdasd";
    QObject::connect(thread->mysocket,SIGNAL(readyRead()),thread,SLOT(ServerReadData()));
    QObject::connect(thread,SIGNAL(handleOk(qintptr,QString)),this,SLOT(chat(qintptr,QString)));
    QObject::connect(thread,SIGNAL(sendChange(QString)),this,SLOT(sendAll(QString)));
   // QObject::connect(mysocket,SIGNAL(readyRead()),this,SLOT(ServerReadData()));
   // QObject::connect(thread->mysocket,SIGNAL(readyRead()),thread,SLOT(ServerReadData()));
    qDebug()<<"111";
    thread->start();
}


void Myserver::chat(qintptr p,QString msg)
{
    auto it=socket_map.find(p);
    auto socket=it.value();
    qDebug()<<socket;

    //char sendMsgChar[1024] = {0};
    //strcpy_s(sendMsgChar, msg.toStdString().c_str());
    //qDebug()<<sendMsgChar;
    qDebug()<<"my sendhererere";

    qDebug()<<msg;
    QByteArray datasend = msg.toLocal8Bit();

    qDebug()<<datasend;
    socket->write(datasend);
}


void Myserver::sendAll(QString msg)
{
    auto it=socket_map.begin();
    for(;it!=socket_map.end();it++)
    {
        auto socket=it.value();
        qDebug()<<socket;
        qDebug()<<"send all";
        qDebug()<<msg;
        QByteArray datasend = msg.toLocal8Bit();
        qDebug()<<datasend;
        socket->write(datasend);
    }
}
