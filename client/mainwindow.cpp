#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"login.h"
#include<QDebug>
#include<chat.h>
#include<nethandle.h>
#include<QTimer>

#define OFFLINE "0"
#define ONLINE "1"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //设置ui
    ui->setupUi(this);
     //QTimer::singleShot(0, this, SLOT(init()));
    //init();
    //this->userid=Login::GetInstance().id;

   // ui->idLabel->setText(Login::GetInstance().id);
    //ui->nameLable->setText(Login::GetInstance().name);
    //this->myname=Login::GetInstance().name;

    ui->friendTree->setSortingEnabled(true);

    QTreeWidgetItem* header = new QTreeWidgetItem;
    header->setText(0, "user");
    header->setText(1, "nick");
    ui->friendTree->setHeaderItem(header);


    rowOnline = new QTreeWidgetItem(ui->friendTree);
    ui->friendTree->addTopLevelItem(rowOnline);
    rowOnline->setText(0, "Online");
    rowOnline->setText(1, "");

    rowOffline = new QTreeWidgetItem(ui->friendTree);
    ui->friendTree->addTopLevelItem(rowOffline);
    rowOffline->setText(0, "Offline");
    rowOffline->setText(1, "");

    //双击好友聊天
    connect(ui->friendTree, SIGNAL( itemDoubleClicked(QTreeWidgetItem*,int)) , this,
            SLOT( OnTreeLButtonDbClicked( QTreeWidgetItem* , int ))  );
    //登录成功信号
    connect(&Login::GetInstance(),SIGNAL(loginIn(QString,QString)),this,SLOT(MainShow(QString,QString)));
    //好友列表
    connect(&Nethandle::GetInstance(),SIGNAL(sigFriend(QStringList)),this,SLOT(WhenMyFriendListComes(QStringList)));
    //消息来临
    connect(&Nethandle::GetInstance(),SIGNAL(sigmsgComes(QStringList)),this,SLOT(WhenMsgComes(QStringList)));
    //处理退出
    connect(&Nethandle::GetInstance(),SIGNAL(sigmainclose()),this,SLOT(mainClose()));

    //初始化socket
    Nethandle::GetInstance();


}




MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::mainClose()
{
    this->close();
}

void MainWindow::on_btn_out_clicked()
{
    //Login::GetInstance().setol(OFFLINE);
    //qDebug()<< Login::GetInstance().id;
    //this->close();
    QString usage="LOGINOUT";
    QString data=usage+DELIM+userid;
    Nethandle::GetInstance().sendData(data);

}

void MainWindow::WhenMyFriendListComes(QStringList l)
{
    // FRIENDLIST|id1|nick1|online|id2|nick2|offline...
    //把自己socket存进去
    QString usage="FIRST";
    QString data=usage+DELIM+userid;
    Nethandle::GetInstance().sendData(data);
    //
    ui->friendTree->clear();
    ui->friendTree->setSortingEnabled(true);
    QTreeWidgetItem* header = new QTreeWidgetItem;
    header->setText(0, "user");
    header->setText(1, "nick");
    ui->friendTree->setHeaderItem(header);


    rowOnline = new QTreeWidgetItem(ui->friendTree);
    ui->friendTree->addTopLevelItem(rowOnline);
    rowOnline->setText(0, "Online");
    rowOnline->setText(1, "");

    rowOffline = new QTreeWidgetItem(ui->friendTree);
    ui->friendTree->addTopLevelItem(rowOffline);
    rowOffline->setText(0, "Offline");
    rowOffline->setText(1, "");
    //
    qDebug()<<"list";
    for(int i = 1; i < l.length(); i=i+3)
    {
        if(userid!=l[i])
        {
            QTreeWidgetItem* subItem = new QTreeWidgetItem;
            subItem->setText(0, l[i]);
            subItem->setText(1, l[i+1]);
                //3rd-->on/off-line
            if( ONLINE == l[i+2])
            {
                rowOnline->addChild(subItem);
            }
            else
            {
                rowOffline->addChild(subItem);
            }
        }
    }
    ui->friendTree->expandAll();
}


void MainWindow::OnTreeLButtonDbClicked(QTreeWidgetItem* item, int nIdex)
{

    qDebug("OnTreeLButtonDbClicked:[%d][%s]", nIdex, item->parent()->text(0).toUtf8().constData());
    if(item->parent()->text(0) == "Offline")
    {
        return;
    }
    qDebug("OnTreeLButtonDbClicked:[%s]", item->text(0).toUtf8().constData()); //id
    qDebug("OnTreeLButtonDbClicked:[%s]", item->text(1).toUtf8().constData()); //nick
    Chat* pChat = new Chat(this->userid,this->myname,item->text(0),item->text(1),"", this);
    //QObject::connect(pChatDlg, SIGNAL(ChatDlgClosing(QString)), this, SLOT( OnChatDlgClosing(QString)));

    //dlgMap.insert(item->text(0), pChatDlg);
    dlgMap.insert(item->text(0), pChat);
    pChat->show();
}


void MainWindow::MainShow(QString id, QString name)
{
    ui->idLabel->setText(id);
    ui->nameLable->setText(name);
    this->userid=id;
    this->myname=name;

    qDebug()<<"show send";
    QString usage="FRIEND";
    QString data=usage+DELIM+userid;
    Nethandle::GetInstance().sendData(data);

    this->show();

}

void MainWindow::init()
{
    lo=new Login(this);
    QObject::connect(lo,SIGNAL(loginIn(QString,QString)),this,SLOT(MainShow(QString,QString)));
    qDebug()<<"here";
    lo->show();
}

void MainWindow::on_btn_refresh_clicked()
{

    ui->friendTree->clear();
    ui->friendTree->setSortingEnabled(true);
    QTreeWidgetItem* header = new QTreeWidgetItem;
    header->setText(0, "user");
    header->setText(1, "nick");
    ui->friendTree->setHeaderItem(header);


    rowOnline = new QTreeWidgetItem(ui->friendTree);
    ui->friendTree->addTopLevelItem(rowOnline);
    rowOnline->setText(0, "Online");
    rowOnline->setText(1, "");

    rowOffline = new QTreeWidgetItem(ui->friendTree);
    ui->friendTree->addTopLevelItem(rowOffline);
    rowOffline->setText(0, "Offline");
    rowOffline->setText(1, "");



    QString usage="FRIEND";
    QString data=usage+DELIM+userid;
    Nethandle::GetInstance().sendData(data);
}

//"CHAT|1|2|2131231231231|cxk"
// CHAT |FROM id | MYiD| message | from name
// data[0] 1      2   3         4

void MainWindow::WhenMsgComes(QStringList msg)
{
    auto it =  dlgMap.find(msg[1]);
    if(it != dlgMap.end())
    {
        qDebug( "Found in DlgMap");
        Chat* pChat = it.value();

        QString sendTime = msg[4];
        QDateTime curDateTime=QDateTime::currentDateTime();
        QString temp=curDateTime.toString("yyyy-MM-dd hh:mm:ss");
        //sendTime.append(temp);
        sendTime=sendTime+" "+temp;
        pChat->appendMsg(sendTime);
        pChat->appendMsg(msg[3]);
    }
    else
    {
        Chat* pChat = new Chat(this->userid,this->myname,msg[1],msg[4],"", this);
        QObject::connect(pChat, SIGNAL(sigchatClose(QString)), this, SLOT(WhenChatClose(QString)));
        dlgMap.insert(msg[1], pChat);
        QString sendTime = msg[4];
        QDateTime curDateTime=QDateTime::currentDateTime();
        QString temp=curDateTime.toString("yyyy-MM-dd hh:mm:ss");
        //sendTime.append(temp);
        sendTime=sendTime+" "+temp;
        pChat->appendMsg(sendTime);
        pChat->appendMsg(msg[3]);
        pChat->show();
    }
}


void MainWindow::WhenChatClose(QString id)
{
    DlgMapT::const_iterator i =  dlgMap.find(id);
    if(i != dlgMap.end())
    {
        qDebug( "Found in DlgMap");
        Chat* pChatDlg = i.value();
        int nRtn = dlgMap.remove(id);
        if(nRtn >0)
        {
            qDebug( "delete");
            delete pChatDlg;
            pChatDlg = NULL;
        }
    }
}
