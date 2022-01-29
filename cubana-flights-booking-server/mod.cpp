#include "mod.h"
#include "ui_mod.h"

mod::mod(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mod)
{
    ui->setupUi(this);
}

mod::~mod()
{
    delete ui;
}

void mod::on_pushButton_clicked()
{
    emit Id(ui->lineEdit->text());//emite el signal con el id
    this->close();
}
void mod::on_pushButton_2_clicked()
{
    this->close();
}
