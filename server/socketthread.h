#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include<QThread>
#include<QTcpSocket>
#include<QWidget>
#include <QSqlDatabase>
#include<QSqlQuery>

class SocketThread : public QThread
{
    Q_OBJECT
public:
    //explicit SocketThread(QObject *parent = 0);
    SocketThread(QWidget * parent,qintptr p);
    qintptr ptr;
    QTcpSocket *mysocket;
    int flag;
    QSqlDatabase db;
    void setol(QString olbit);
    QString id;


signals:
    void handleOk(qintptr p,QString re);
    void sendChange(QString);

public slots:
    void ServerReadData();
    void sendData(QString);




protected:
    virtual void run();
};




#endif // SOCKETTHREAD_H
