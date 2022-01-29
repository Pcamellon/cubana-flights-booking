#ifndef CONECTAR_H
#define CONECTAR_H

#include <QDialog>

namespace Ui {
class Conectar;
}

class Conectar : public QDialog
{
    Q_OBJECT

public:
    explicit Conectar(QWidget *parent = 0);
    ~Conectar();

private slots:
    void on_conectar_clicked();

    void on_serv_Cancelar_clicked();

private:
    Ui::Conectar *ui;

signals:
 void puerto (QString);
};

#endif // CONECTAR_H
