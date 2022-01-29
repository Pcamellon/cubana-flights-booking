#ifndef MOD_H
#define MOD_H

#include <QWidget>

namespace Ui {
class mod;
}

class mod : public QWidget
{
    Q_OBJECT

public:
    explicit mod(QWidget *parent = 0);
    ~mod();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::mod *ui;

signals:
    void Id(QString);
};

#endif // MOD_H
