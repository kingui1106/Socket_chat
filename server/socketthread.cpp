#include "socketthread.h"
#include<QMessageBox>
#include <QDateTime>
#include<mainwindow.h>
#include<myserver.h>

#define DELIM "|"


SocketThread::SocketThread(QWidget *parent,qintptr p):QThread(parent)
{
    qDebug()<<"jiu xiancheng";
    this->ptr=p;
    this->flag=0;
    //connect(this->mysocket,SIGNAL(readyRead()),this,SLOT(ServerReadData()));

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("123456");//注意这里的密码
    if (!db.open())
        qDebug() << "Failed to connect to root mysql admin";
    else qDebug() << "open";
}


void SocketThread::run(){
    qDebug()<<"开始新线程";
    //mysocket=new QTcpSocket();
    //mysocket->setSocketDescriptor(ptr);//客户端的初始化
    //QObject::connect(mysocket,SIGNAL(readyRead()),this,SLOT(ServerReadData()));
    qDebug()<<mysocket;
    if(mysocket->waitForConnected(10000))
    {
        qDebug()<<"Connect Success";
    }
    else
    {
        qDebug()<<"Connect Fail";
    }

    QThread::run ();

}

void SocketThread::ServerReadData()
{
    //char buffer[1024] = {0};
    qDebug()<<"work1";
    //QString test="TEST|";

    QByteArray dataread = mysocket->readAll();
    qDebug()<<dataread;
    QString str = QString::fromLocal8Bit(dataread);
    QStringList data=str.split(DELIM);
    QString usage=data[0];
    qDebug()<<str;
    //注册    REGISTER|SQLTEXT
    if(usage=="REGISTER")
    {
        QSqlQuery query=QSqlQuery(db);
        qDebug()<<data[1];
        query.prepare(data[1]);
        bool success=query.exec();

        if(success)
        {
           QString re=usage+DELIM+"SUCCESS";
           qDebug()<<"re nice";
           char sendMsgChar[1024] = {0};
           strcpy_s(sendMsgChar, re.toStdString().c_str());
           qDebug()<<"my send";
           mysocket->write(sendMsgChar, strlen(sendMsgChar));
           return;
        }
        else
        {
            QString re=usage+DELIM+"FAIL";
            qDebug()<<"re ERROR";
            qDebug()<<"33";
            char sendMsgChar[1024] = {0};
            strcpy_s(sendMsgChar, re.toStdString().c_str());
            qDebug()<<"my send";
            mysocket->write(sendMsgChar, strlen(sendMsgChar));
            qDebug()<<"44";
            return;
        }
    }

    //登录  LOGIN|sqltext
    if(usage=="LOGIN")
    {
        QSqlQuery query=QSqlQuery(db);
        qDebug()<<data[1];
        query.prepare(data[1]);
        query.exec();

        if(query.next())
        {

           qDebug()<<"login nice";
           id=query.value(0).toString();
           QString name=query.value(2).toString();
           setol("1");
           QString re=usage+DELIM+"SUCCESS"+DELIM+id+DELIM+name;
           char sendMsgChar[1024] = {0};
           strcpy_s(sendMsgChar, re.toStdString().c_str());
           qDebug()<<"my send";
           mysocket->write(sendMsgChar, strlen(sendMsgChar));
           return;
        }
        else
        {
            QString re=usage+DELIM+"FAIL";
            qDebug()<<"login ERROR";
            qDebug()<<"33";
            char sendMsgChar[1024] = {0};
            strcpy_s(sendMsgChar, re.toStdString().c_str());
            qDebug()<<"my send";
            mysocket->write(sendMsgChar, strlen(sendMsgChar));
            qDebug()<<"44";
            return;
        }
    }
    //好友
    if(usage=="FRIEND")
    {
        QSqlQuery query=QSqlQuery(db);
        //QString sqltext="select id,name,ol from we where id!='"+id+"';";
        QString sqltext="select id,name,ol from we;";
        qDebug()<<sqltext;
        query.prepare(sqltext);
        query.exec();
        int flag=0;
        QString re;
        while(query.next())
        {
            if(!flag)
            {
                re=usage+DELIM+query.value(0).toString()+DELIM+
                        query.value(1).toString()+DELIM+
                        query.value(2).toString();
                qDebug()<<re;
                flag++;
            }
            else
            {
                 re=re+DELIM+query.value(0).toString()+DELIM+
                        query.value(1).toString()+DELIM+
                        query.value(2).toString();
                 qDebug()<<re;

            }
        }

        char sendMsgChar[1024] = {0};
        strcpy_s(sendMsgChar, re.toStdString().c_str());
        qDebug()<<re;
        qDebug()<<sendMsgChar;

        qDebug()<<"my send";
        //mysocket->write(sendMsgChar, strlen(sendMsgChar));
        emit sendChange(sendMsgChar);
    }

    //first
    if(usage=="FIRST")
    {
        //Myserver::GetInstance().socket_map[data[1]]=mysocket;
        Myserver::GetInstance().ptr_map[data[1]]=ptr;
        qDebug()<<mysocket<<"  first";
    }

    if(usage=="LOGINOUT")
    {
        setol("0");

        QString res=usage+DELIM+"success";
        char sendMsgChar[1024] = {0};
        strcpy_s(sendMsgChar, res.toStdString().c_str());
        qDebug()<<res;
        qDebug()<<sendMsgChar;
        qDebug()<<"my send";
        mysocket->write(sendMsgChar, strlen(sendMsgChar));
        //回复退出的让它关闭

        //update
        usage="FRIEND";
        qDebug()<<"my send";
        //mysocket->write(sendMsgChar, strlen(sendMsgChar));
        QSqlQuery query=QSqlQuery(db);
        //QString sqltext="select id,name,ol from we where id!='"+id+"';";
        QString sqltext="select id,name,ol from we;";
        qDebug()<<sqltext;
        query.prepare(sqltext);
        query.exec();
        int flag=0;
        QString re;
        while(query.next())
        {
            if(!flag)
            {
                re=usage+DELIM+query.value(0).toString()+DELIM+
                        query.value(1).toString()+DELIM+
                        query.value(2).toString();
                qDebug()<<re;
                flag++;
            }
            else
            {
                 re=re+DELIM+query.value(0).toString()+DELIM+
                        query.value(1).toString()+DELIM+
                        query.value(2).toString();
                 qDebug()<<re;

            }
        }


        char sendMsgChar2[1024] = {0};
        strcpy_s(sendMsgChar2, re.toStdString().c_str());
        qDebug()<<re;
        qDebug()<<sendMsgChar2;
        emit sendChange(sendMsgChar2);

    }

    //"CHAT|1|2|2131231231231|cxk"
    // CHAT |myid | toif| message | myname
    // data[0] 1      2   3         4
    // 直接转发消息 不处理
    if(usage=="CHAT")
    {
        auto my_map=Myserver::GetInstance().ptr_map;
        auto it=my_map.find(data[2]);
        auto p=it.value();
        qDebug()<<p;

        emit handleOk(p,str);

        //my_map=Myserver::GetInstance().socket_map;
        //auto it2=my_map.find(data[2]);
        //auto chatSocket2=it2.value();
        //qDebug()<<chatSocket2;
        //qDebug()<<"chatSocket2";
       // emit sendTo(data[2],str,chatSocket2);

    }

}

void SocketThread::setol(QString olbit)
{
    QSqlQuery query=QSqlQuery(db);
    QString sqltext="UPDATE we SET ol="+olbit+" WHERE id='"+id+"';";
    qDebug()<<sqltext;
    query.prepare(sqltext);
    query.exec();

}
void SocketThread::sendData(QString re)
{
    char sendMsgChar[1024] = {0};
    strcpy_s(sendMsgChar, re.toStdString().c_str());
    qDebug()<<re;
    qDebug()<<sendMsgChar;
    qDebug()<<"my send";
    mysocket->write(sendMsgChar, strlen(sendMsgChar));
}


