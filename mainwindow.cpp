#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMediaPlayer"
#include "QFileInfo"
#include <QAudio>
#include <conectar.h>
#include <QUdpSocket>
#include <QMessageBox>
#include <QDate>
#include <QProcess>
#include <QDir>
#include <QUrl>
#include <QFile>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ss = new QSound ("D:/Programacion/Para proyecto Final/ringout.wav",this);
    s2 = new QSound ("D:/Programacion/Para proyecto Final/Ring07.wav",this);
    this->mover();
    socket = new QUdpSocket (this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(leer()));
    ui->dateEdit->setDate(QDate::currentDate());
    this->setMaximumHeight(this->height());
    this->setMaximumWidth(this->width());
    this->setMinimumHeight(this->height());
    this->setMinimumWidth(this->width());
    ui->notifications->append(this->LeerArchivo());//importar registros de un archivo





}

MainWindow::~MainWindow()
{

    delete ui;

}

void MainWindow::mover()
{
       x= ui->visitenos->width();//posicion en x
       y = ui->logo->height(); // posicion en y
       dir=0;// direccion en la que se va mover
       timer = new QTimer;
       connect (timer,SIGNAL(timeout()),this,SLOT(moveb()));
       timer->start(100);

}
void MainWindow::moveb()
{
    if (dir==0)
        x +=10;// aumentar posicion en x
    else
        x-=10; // disminuir posicion en x
    if(x+ui->logo->width()>=this->width())
    {
        dir=1; // cambiar direccion

    }
    if (x==ui->visitenos->width())
        dir=0;
    ui->logo->move(x,0);// funcion para mover
    ui->lcdNumber->display(QTime::currentTime().toString());


}







void MainWindow::on_actionConexi_n_triggered()
{
    if (socket->bind(3333,QUdpSocket::ShareAddress))// conectar socket
    {
        ss->play();
        QMessageBox::information(this,"Conectado","Iniciada conexion.");

    }
    else qDebug()<< "Error de conexion.";


}


void MainWindow::on_actionSalir_triggered()
{
    this->close();

}

void MainWindow::on_pushButton_clicked()
{
    QString cadena,no,des,date,name,lname,pssp,airl,noti,phne,mail;
    no=no.number(ui->lineEdit_8->text().toInt());
    des=ui->dest->currentText();
    date=ui->dateEdit->text();
    name=ui->name->text();
    lname=ui->lname->text();
    pssp=pssp.number(ui->pssp->text().toInt());
    if(ui->nphone->isChecked())
    {
        phne ="NAP";
    }
    else
    {
        phne=ui->phone1->text();
    }
    if(ui->radioButton_2->isChecked())
    {
        mail= "NAeM";
    }
    else
    {
        mail=ui->email1->text();
    }



    cadena="insert into Reservaciones (No,Destino,Nombre,Apellidos,Telefono,email,Fecha,Pasaporte) values('"+no+"','"+des+"','"+name+"','"+lname+"','"+phne+"','"+mail+"','"+date+"',"+pssp+")";
    QByteArray dtg;
    dtg= cadena.toLatin1();
    socket->writeDatagram(dtg.data(),dtg.size(),QHostAddress::Broadcast,6666);// envia cadena con el comando en sql



}

void MainWindow::leer() // leer socket
{
    QByteArray dtg;
    QString noti;
    QTextStream tsr(&noti);
    QHostAddress host0;
    unsigned short puerto0;
    dtg.resize(socket->pendingDatagramSize());
    socket->readDatagram(dtg.data(),dtg.size(),&host0,&puerto0);
    tsr<<dtg;
    if (noti.at(0)=='*')
    {

        noti.replace("*","");
        ui->notifications->append(noti);
        this->SalvarArchivo("D:/Not.txt");
        s2->play();
    }
    if (noti.at(0)=='/')
    {
        noti.replace("/","");
        ui->textEdit->append(noti);
        s2->play();
    }

}

void MainWindow::on_visitenos_clicked()
{
    system("start http://www.cubana.cu");
}

void MainWindow::SalvarArchivo( QString nombre)
{
    QFile file (nombre);
    file.open(QFile::WriteOnly);
    QTextStream srr (&file);
    srr <<ui->notifications->toPlainText();
    srr.flush();
    file .close();
    }
QString MainWindow::LeerArchivo()
{
    QFile file ("D:/Not.txt");
    file.open(QFile::ReadOnly);
    QTextStream srr (&file);
    QString x = srr.readAll();
    srr.flush();
    file.close();
    return x;
}

void MainWindow::on_dateEdit_editingFinished()
{



}

void MainWindow::on_search_clicked()
{
    QString cadena;
    QByteArray dtg;

    cadena = "/ Select * from Vuelos where Destino= '"+ui->buscar->text()+"'";
    dtg = cadena.toLatin1();
    socket->writeDatagram(dtg.data(),dtg.size(),QHostAddress::Broadcast,6666);

}

