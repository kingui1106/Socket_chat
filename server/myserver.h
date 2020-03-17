#ifndef MYSERVER_H
#define MYSERVER_H
#include <QObject>
#include<QTcpServer>
#include<QTcpSocket>
#include<QWidget>
#include<QMap>
#include<socketthread.h>
#include<QVector>

class Myserver : public QTcpServer
{
    Q_OBJECT
public:
    static Myserver& GetInstance()
    {
        static Myserver instance;
        return instance;
    }
    explicit Myserver(QWidget  *parent = 0);
    //QTcpSocket *mysocket;
   // QMap<QString, QTcpSocket *> socket_map;
    //QMap<QString, qintptr >  ptr_map;
    //QMap<qintptr, Process *> process_map;
    QMap<qintptr, QTcpSocket * > socket_map;
    QMap<QString, qintptr > ptr_map;

   // QVector<QTcpSocket *> array;
    int flag=0;
protected:
    virtual void incomingConnection(qintptr socketDescriptor);

signals:

public slots:
    void chat(qintptr,QString );
    void sendAll(QString);

};

#endif // MYSERVER_H
