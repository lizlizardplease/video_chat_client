#ifndef WELCOME_H
#define WELCOME_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class Welcome;
}

class Welcome : public QDialog
{
    Q_OBJECT

public:
public:
    explicit Welcome(QSqlDatabase &db);
    Welcome();
    ~Welcome();

private slots:
    void on_signin_clicked();

private:
    Ui::Welcome *ui;
    QSqlDatabase m_db;
};

#endif // WELCOME_H
