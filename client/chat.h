#ifndef CHAT_H
#define CHAT_H

#include <QDialog>
#include<QTcpSocket>
#include<QMessageBox>
#include<QDateTime>
#include<QCloseEvent>
#define DELIM "|"

namespace Ui {
class Chat;
}

class Chat : public QDialog
{
    Q_OBJECT

public:
    explicit Chat(QWidget *parent = 0);
    Chat(QString myid,QString myname ,QString friendid,QString friendname,QString firstMsg, QWidget *parent = 0);
    ~Chat();
    QString myid,friendid, Msg,friendname,myname;
    void appendMsg(QString msg);
    void closeEvent(QCloseEvent *event);

signals:
    void sigchatClose(QString id);

private slots:
    void sendMsg();


private:
    Ui::Chat *ui;

};

#endif // CHAT_H
