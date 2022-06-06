#include "welcome.h"
#include "ui_welcome.h"
#include "user.h"

Welcome::Welcome() :
    QDialog(),
    ui(new Ui::Welcome)
{
    ui->setupUi(this);
    m_db = QSqlDatabase::addDatabase("QPSQL");
    QSettings settings;
    settings.beginGroup("/Database_browser/settings");
    m_db.setDatabaseName(settings.value("Database_name", "fn1131_2021").toString());
    m_db.setHostName(settings.value("Host_ip", "195.19.32.74").toString());
    m_db.setPort(settings.value("P0rt", 5432).toInt());
    m_db.setUserName(settings.value("L0gin", "student").toString());
    m_db.setPassword(settings.value("Password", "bmstu").toString());
    settings.endGroup();
    if(!m_db.open())
    {
        ui->error->setText("Some troubles!");
    }
}
Welcome::~Welcome()
{
    delete ui;
}

void Welcome::on_signin_clicked()
{
    QString Username, Password;
    Username = ui->login->text();
    Password = ui->password->text();
    QSqlQuery query;
    query.prepare("SELECT user FROM ourbaza WHERE login='"+Username+"' AND password='"+Password+"'");
    query.exec();
    if (query.first())
      {
        user *me = new user;
        me->show();
    }
    else
        ui->error->setText("Wrong login or password!");
}


