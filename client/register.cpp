#include "register.h"
#include "ui_register.h"
#include<login.h>
#include <QDebug>
#include<QMessageBox>
#include<nethandle.h>
Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    QObject::connect(&Nethandle::GetInstance(), SIGNAL(sigregisterOk()),
                         this, SLOT(registerOk()));

    QObject::connect(&Nethandle::GetInstance(), SIGNAL(sigregisterError()),
                         this, SLOT(registerError()));
}

Register::~Register()
{
    delete ui;
}

void Register::on_re_btn_clicked()
{
    QString id=ui->re_id->text();
    QString passwd=ui->re_passwd->text();
    QString name=ui->re_name->text();
    QString sqltext="INSERT INTO we (id,passwd,name) values('"+id+"','"+passwd+"','"+name+"');";
    qDebug()<<sqltext;
    if(id=="" || passwd=="" ||name=="")
    {
        QMessageBox::information(this, "LOGIN", "not null");
        return;
    }
    //发送到服务器处理
    QString usage="REGISTER";
    QString data=usage+DELIM+sqltext;
    qDebug()<<data;
    Nethandle::GetInstance().sendData(data);
}

void Register::registerOk()
{
    QMessageBox::information(this, "we", "return login");
    this->close();
}

void Register::registerError()
{
    QMessageBox::information(this, "we", "register error");
}
