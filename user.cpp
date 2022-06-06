#include "user.h"
#include "ui_user.h"
#include "mainwindow.h"
#include <QMessageBox>

user::user(QWidget *parent, QString l) :
    QMainWindow(parent),
    ui(new Ui::user)
{
    login = l;
    ui->setupUi(this);
    m_model = new QSqlQueryModel;
    ui->tableView->setModel(m_model);
    m_model->setQuery(" SELECT ну короче все чаты и друзей");
    update_pd();
    changing = 0;
    ui->name->setReadOnly(1);
    ui->status->setReadOnly(1);
}

void user::update_pd(){
    QSqlQuery query;
    query.prepare("SELECT * FROM ourbaza WHERE login='"+login+"'");
    query.exec();
    query.next();
    ui->name->setText(query.value(0).toString());
    ui->status->setText(query.value(2).toString());
}

user::~user()
{
    delete ui;
}

void user::on_change_clicked()
{
    if(changing){
        ui->name->setReadOnly(1);
        ui->status->setReadOnly(1);
        ui->change->setText("Change");
        QSqlQuery query;
        QString deal = "UPDATE ourbaza SET name = '" + ui->name->text() + "', status = '";
        deal += ui->status->toPlainText()+ "' WHERE login = '" + login + "';";
        query.prepare(deal);
        query.exec();
        changing = 0;
    }
    else{
        ui->status->setReadOnly(0);
        ui->name->setReadOnly(0);
        ui->change->setText("Done");
        changing = 1;
    }
}

void user::on_remove_clicked()
{
   QString bro = ui->friendd->text();
   QString task = "найти бро в друзьях";
   QSqlQuery query;
   query.prepare(task);
   if(!query.first()){
       QString msg = "You don't even have friend" + bro;
       QMessageBox msgBox;
       msgBox.setText(msg);
       msgBox.exec();
   }
   else{
       //удалить бро
       QString msg = bro + "is successfully deleted!";
       QMessageBox msgBox;
       msgBox.setText(msg);
       msgBox.exec();
   }
}

void user::on_add_clicked()
{
    QString bro = ui->friendd->text();
    QString task = "найти бро в базе";
    QSqlQuery query;
    query.prepare(task);
    if(!query.first()){
        QString msg = bro + "does not exist...";
        QMessageBox msgBox;
        msgBox.setText(msg);
        msgBox.exec();
    }
    else{
        QString task = "найти бро в друзьях";
        QSqlQuery query;
        query.prepare(task);
        if(!query.first()){
            QString msg = bro + "is asked to be your friend";
            QMessageBox msgBox;
            msgBox.setText(msg);
            msgBox.exec();
        }
        else{
            QString msg = bro + "is already your friend";
            QMessageBox msgBox;
            msgBox.setText(msg);
            msgBox.exec();
        }
    }
}

void user::on_tableView_clicked(const QModelIndex &index)
{
    QString name = m_model->data(index, Qt::DisplayRole).toString();
    //типо надо, наверно, на сервер передать, кому пишем
    //как же я не понимаю
    MainWindow* chat = new MainWindow;
    chat->show();
}
