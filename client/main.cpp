#include "mainwindow.h"
#include <QApplication>
#include<login.h>
#include<QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;
    w.hide();
    //Login l;
    //QObject::connect(&l,SIGNAL(loginOK()),&w,SLOT(show()));
    //l.show();
    //初始化login
    Login lo;
    lo.show();

    return a.exec();
}
