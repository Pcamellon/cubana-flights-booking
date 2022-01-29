#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <agregar.h>
#include <QString>
#include <QUdpSocket>
#include <QSound>
#include <mod.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    class QUdpSocket *Socket;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void leerSocket();

    void on_actionConectar_triggered();
    void returnID(QString id);

private:
    Ui::MainWindow *ui;
    QSqlTableModel *modelo;
    QSqlTableModel *modelo1;
    QSqlDatabase vuelo;
    QString Dir;
    QSound *soun;


signals:


};

#endif // MAINWINDOW_H
