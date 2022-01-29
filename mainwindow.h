#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QUdpSocket>
#include <QString>
#include <QSound>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mover ();

private:
    Ui::MainWindow *ui;
    int x;
    int y;
    int dir;
    QTimer *timer;
    QString *puerto;
    QUdpSocket *socket;
    QSound *ss;
    QSound *s2;
    void SalvarArchivo(QString);
    QString LeerArchivo ();
private slots:
    void moveb ();
    void on_actionConexi_n_triggered();
    void on_actionSalir_triggered();
    void on_pushButton_clicked();
    void leer ();
    void on_visitenos_clicked();
    void on_dateEdit_editingFinished();
    void on_search_clicked();

};

#endif // MAINWINDOW_H
