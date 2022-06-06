#ifndef USER_H
#define USER_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class user;
}

class user : public QMainWindow
{
    Q_OBJECT

public:
    explicit user(QWidget *parent = nullptr, QString l="");
    ~user();

private:
    Ui::user *ui;
    QSqlQueryModel *m_model;
    QSqlDatabase m_db;
    QString login;
    bool changing;

    void update_pd();
    void update_fl();

private slots:

    void on_change_clicked();
    void on_remove_clicked();
    void on_add_clicked();
    void on_tableView_clicked(const QModelIndex &index);
};

#endif // USER_H
