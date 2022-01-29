#include "agregar.h"
#include "ui_agregar.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

Agregar::Agregar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Agregar)
{
    ui->setupUi(this);
    dir ="D:/Cubana.mdb";
}

Agregar::~Agregar()
{
    delete ui;
}

void Agregar::on_pushButton_2_clicked()
{
    this->close();
}

void Agregar::on_pushButton_clicked()
{
    QSqlDatabase vuelo = QSqlDatabase::addDatabase("QODBC");
    vuelo.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ="+dir);
    if (vuelo.open())
    {
        QString no,des,date,go,in,cap,airl;
        no=no.number(ui->lineEdit->text().toInt());
        des = ui->lineEdit_2->text();
        date = ui->lineEdit_3->text();
        go = ui->lineEdit_4->text();
        in = ui->lineEdit_5->text();
        cap = cap.number(ui->lineEdit_6->text().toInt());
        airl = ui->lineEdit_7->text();
        QSqlQuery qry;
        if (qry.exec("insert into Vuleos (No de Vuelo, Aereolinea, Destino, Fecha de Salida, Hora de Salida, Hora de Llgada, Capacidades) values("+no+",'"+airl+"','"+des+"','"+date+"','"+go+"','"+in+"',"+cap+")"))
        {
            this->close();
            \
        }
        else qDebug ()<< "No se inserto el vuelo";


    }
    this->close();

}
