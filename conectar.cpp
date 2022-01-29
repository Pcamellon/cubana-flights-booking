#include "conectar.h"
#include "ui_conectar.h"

Conectar::Conectar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Conectar)
{
    ui->setupUi(this);
}

Conectar::~Conectar()
{
    delete ui;
}

void Conectar::on_conectar_clicked()
{
    emit puerto(ui->puerto->text());
    this->close();
}

void Conectar::on_serv_Cancelar_clicked()
{
    this->close();
}
