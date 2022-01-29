#ifndef AGREGAR_H
#define AGREGAR_H

#include <QWidget>
#include <QString>

namespace Ui {
class Agregar;
}

class Agregar : public QWidget
{
    Q_OBJECT

public:
    explicit Agregar(QWidget *parent = 0);
    ~Agregar();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();



private:
    Ui::Agregar *ui;
    QString dir;

signals:

};

#endif // AGREGAR_H
