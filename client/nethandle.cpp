#include "nethandle.h"
#include<QTimer>
#define SERVER_HOST "192.168.0.153"
#define SERVER_PORT 2333

Nethandle::Nethandle()
{
    mysocket = new QTcpSocket(this);
    //connect(mysocket, SIGNAL(connected()),this, SLOT(ServerConnected()));
    connect(mysocket, SIGNAL(readyRead()), this, SLOT(ProcessReadyRead()));
    //connect server
    mysocket->connectToHost(SERVER_HOST, SERVER_PORT );
    if(!mysocket->waitForConnected(30000))
    {
            return ;
    }
    //QMessageBox::information(this,"qt","连接成功");
    qDebug()<<"nethandel init join server ";
    qDebug()<<mysocket;





    //handling functions
#if 0
    recvPacketHandleFuncMap["REGISTER"] = &NetManager::HandleResponseEnrollUser;
    recvPacketHandleFuncMap["LOGIN"] = &NetManager::HandleResponseLogIn;
    recvPacketHandleFuncMap["CHKID"] = &NetManager::HandleResponseCheckId;
    recvPacketHandleFuncMap["FRIENDLIST"] = &NetManager::HandleResponseFriendList;
    recvPacketHandleFuncMap["ADDFRIEND"] = &NetManager::HandleResponseAddFriend;
    recvPacketHandleFuncMap["DELETEFRIEND"] = &NetManager::HandleResponseRemoveFriend;
    recvPacketHandleFuncMap["CHATMSG"] = &NetManager::HandleChatMsg;
    recvPacketHandleFuncMap["LOGGED-IN"] = &NetManager::HandleLoggedIn;
    recvPacketHandleFuncMap["LOGGED-OUT"] = &NetManager::HandleLoggedOut;
#endif
}

void Nethandle::sendData(QString msg)
{
    //char sendMsgChar[1024] = {0};
    //strcpy_s(sendMsgChar, msg.toStdString().c_str());
    qDebug()<<msg;
    QByteArray datasend = msg.toLocal8Bit();
    qDebug()<<datasend;
    mysocket->write(datasend);

}

void Nethandle::Initialize(QString id)
{
    //第一条消息，初始化保存socket
    QString usage="FIRST";
    QString data=usage+DELIM+id;
    sendData(data);
    qDebug()<<data;
}

void Nethandle::ProcessReadyRead()
{
    qDebug()<<mysocket;

   // char recvMsg[1024] = {0};
    //mysocket->read(recvMsg, 1024);
    //qDebug()<<recvMsg;

    QByteArray dataread = mysocket->readAll();
    qDebug()<<dataread;
    QString str = QString::fromLocal8Bit(dataread);
    qDebug()<<str;
   // QString str=QString(QLatin1String(recvMsg));
    QStringList data=str.split(DELIM);
    QString usage=data[0];
    qDebug()<<"111111111111";
    qDebug()<<data;
    //注册
    if(data[0]=="REGISTER")
    {
        QString result=data[1];
        if(result=="FAIL")
        {
            emit sigregisterError();


        }
        else
        {
            emit sigregisterOk();
            return;
        }
    }
    //登录
    if(data[0]=="LOGIN")
    {
        QString result=data[1];
        if(result=="FAIL")
        {
            qDebug()<<"recv handle send sig";
            emit sigloginError();
            return;


        }
        else
        {
            emit sigloginOk(data[2],data[3]);

        }
    }

    if(data[0]=="FRIEND")
    {
        qDebug()<<"FEI";
        qDebug()<<data;
        emit sigFriend(data);
    }

    if(data[0]=="CHAT")
    {
        //"CHAT|1|2|2131231231231|cxk"
        // CHAT |FROM id | MYiD| message | MYname
        // data[0] 1      2   3         4
        //emit sigmsgComes(QStringList data);
        emit sigmsgComes(data);
    }

    if(data[0]=="LOGINOUT")
    {
        emit sigmainclose();
    }

}


