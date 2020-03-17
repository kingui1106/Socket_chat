#include "chat.h"
#include "ui_chat.h"
#include<QDebug>
#include<login.h>
#include<mainwindow.h>

Chat::Chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);


}

Chat::~Chat()
{
    delete ui;
}


Chat::Chat(QString myid, QString myname,QString friendid, QString friendname,QString firstMsg,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
    this->myid = myid;
    this->friendid = friendid;
    this->Msg = firstMsg;
    this->friendname=friendname;
    this->myname=myname;

    qDebug()<<"chat";

    ui->label->setText(friendname);

    qDebug("this->myid[%s]", this->myid.toUtf8().constData() );
    qDebug("this->friendid[%s]", this->friendid.toUtf8().constData() );
    qDebug()<<myid;
    qDebug()<<friendid;

    QObject::connect(ui->btnSendMsg, SIGNAL(clicked()), this, SLOT( sendMsg()));
    //QObject::connect(ui->textEdit, SIGNAL(sigEnterKeyed()), this, SLOT( SendMsg()));
    QObject::connect(ui->textEdit,SIGNAL(returnPressed()),
    this,
    SIGNAL(sendMsg()),
    Qt::UniqueConnection
    );

}

void Chat::sendMsg()
{
    // chat | myid | friendid | mymsg | myname
    QString usage="CHAT";
    QString myMsg = ui->textEdit->toPlainText();
    QString data=usage+DELIM+myid+DELIM+friendid+DELIM+myMsg+DELIM+myname;
    if(myMsg.isEmpty())
    {
        QMessageBox::information(this, "QT网络通信", "empty");
        return ;
    }
    //show my message
    QString sendTime = myname;
    QDateTime curDateTime=QDateTime::currentDateTime();
    QString temp=curDateTime.toString("yyyy-MM-dd hh:mm:ss");
    //sendTime.append(temp);
    sendTime=sendTime+" "+temp;

    myMsg="<font color=\"#0000FF\">"+myMsg+"</font> ";
    ui->ChatMsgsTE->append(sendTime);
    ui->ChatMsgsTE->append(myMsg);
    ui->textEdit->setText("");
    Nethandle::GetInstance().sendData(data);
}

void Chat::appendMsg(QString msg)
{
    ui->ChatMsgsTE->append(msg);
}

void Chat::closeEvent(QCloseEvent *event)
{
    emit sigchatClose(friendid);
}
