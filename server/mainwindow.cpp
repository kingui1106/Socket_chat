#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->server=new Myserver(this);
    if(!this->server->listen(QHostAddress::Any,2333))
    {
       QMessageBox::information(this, "we", "服务端启动失败！");
       qDebug() << server->errorString();
       return;
    }
   // QMessageBox::information(this, "we", "服务端启动成功！");

}

MainWindow::~MainWindow()
{
    delete ui;
}
