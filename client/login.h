#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QSqlDatabase>
#include<QSqlQuery>
#include<QTcpSocket>
#include<QMap>
#include<nethandle.h>
#define DELIM "|"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);

    ~Login();
    static Login& GetInstance()
    {
        static Login instance;
        return instance;
    }
    //static QString id;
    //static QString name;
    QTcpSocket *mp_clientSocket;

signals:
    void loginIn(QString,QString);

private slots:
    void on_login_clicked();
    void on_register_2_clicked();   
    void loginOk(QString,QString);
    void loginError();

private:
    Ui::Login *ui;

};

#endif // LOGIN_H
