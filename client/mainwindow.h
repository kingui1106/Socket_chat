#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTreeWidget>
#include<QSqlQuery>
#include<QTcpSocket>
#include<login.h>
#include<QMap>
#include<chat.h>
typedef QMap<QString, Chat*> DlgMapT;
#define DELIM "|"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    static MainWindow& GetInstance()
    {
        static MainWindow instance;
        return instance;
    }
    ~MainWindow();
    QMenu* menu;
    QAction* act;
    QMenuBar* menuBar ;
    QStatusBar* statusBar;

    QString userid;
    QTcpSocket  *mysocket;
    QString myname;
    Login *lo;
    DlgMapT dlgMap;

public slots:
    void MainShow(QString,QString);
    void init();
    void WhenMyFriendListComes(QStringList l);
    void WhenMsgComes(QStringList msg);
    void WhenChatClose(QString id);
    void mainClose();
private slots:
    void on_btn_out_clicked();
    void OnTreeLButtonDbClicked( QTreeWidgetItem* , int );


    void on_btn_refresh_clicked();

private:
    Ui::MainWindow *ui;
    QTreeWidgetItem* rowOnline, *rowOffline;
};

#endif // MAINWINDOW_H
