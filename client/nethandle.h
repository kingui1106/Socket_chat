#ifndef NETHANDLE_H
#define NETHANDLE_H

#include <QObject>
#include<QMap>
#include<QTcpSocket>
#include<QDebug>
#define DELIM "|"

class Nethandle : public QObject
{
    Q_OBJECT
public:

    static Nethandle& GetInstance()
    {
        static Nethandle instance;
        return instance;
    }

    Nethandle();
    void sendData(QString);
    QTcpSocket *mysocket;
    void Initialize(QString);
    bool requestRegister(QString);


signals:
    void sigregisterOk();
    void sigregisterError();
    void sigloginOk(QString,QString);
    void sigloginError();
    void sigFriend(QStringList l);
    void sigmsgComes(QStringList l);
    void sigmainclose();

public slots:

    void ProcessReadyRead();
};

#endif // NETHANDLE_H

