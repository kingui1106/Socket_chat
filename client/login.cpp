#include "login.h"
#include "ui_login.h"
#include <QDebug>
#include <QStringList>
#include "mainwindow.h"
#include<register.h>
#include<QMessageBox>
#define OFFLINE "0"
#define ONLINE "1"
#define IP "192.168.0.153"
#define PORT 2333
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->id->setText("1");
    ui->passwd->setText("1");

    QObject::connect(&Nethandle::GetInstance(), SIGNAL(sigloginOk(QString,QString)),
                         this, SLOT(loginOk(QString,QString)));

    QObject::connect(&Nethandle::GetInstance(), SIGNAL(sigloginError()),
                         this, SLOT(loginError()));

}

Login::~Login()
{
    delete ui;
}


void Login::on_login_clicked()
{
    QString id=ui->id->text();
    QString passwd=ui->passwd->text();
    QString sqltext="select *from we where id='"+id+"' and passwd='"+passwd+"'and ol='0';";


    if(id=="" || passwd=="")
    {
        QMessageBox::information(this, "LOGIN", "not null");
        return;
    }

    //组装句子
    QString usage="LOGIN";
    QString data=usage+DELIM+sqltext;
    qDebug()<<data;
    Nethandle::GetInstance().sendData(data);

}

void Login::on_register_2_clicked()
{
    Register *re = new Register;
    re->show();
    qDebug()<<Nethandle::GetInstance().mysocket;
}

void Login::loginOk(QString id,QString name)
{
    this->close();
    emit loginIn(id,name);
}

void Login::loginError()
{
    qDebug()<<"error once";
    QMessageBox::information(this, "LOGIN", "return error");


}


