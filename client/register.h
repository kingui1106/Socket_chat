#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#define DELIM "|"

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();

private slots:
    void on_re_btn_clicked();
    void registerOk();
    void registerError();
signals:


private:
    Ui::Register *ui;
};

#endif // REGISTER_H
