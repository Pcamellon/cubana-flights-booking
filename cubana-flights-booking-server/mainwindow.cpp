#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <agregar.h>
#include <QInputDialog>
#include <QTime>
#include <QDate>
#include <QSound>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setCentralWidget(ui->tabWidget);


    vuelo = QSqlDatabase::addDatabase("QODBC"); //Abrir base de datos usando el driver ODBC
    Dir = QFileDialog::getOpenFileName(this,"Seleccione Base de datos","C:/Program Files (x86)/BoredCodes"); //Obtener el directorio de la base de datos
   vuelo.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ="+Dir); //Nombrar base de datos
    if (vuelo.open()) //Vincular con el model
    {
        modelo = new QSqlTableModel(this);
        modelo1= new QSqlTableModel(this);

        modelo->setTable("Vuelos");
        modelo1->setTable("Reservaciones");
        ui->tableView->setModel(modelo);
        ui->tableView_2->setModel(modelo1);
        ui->tableView->resizeColumnsToContents();
        ui->tableView_2->resizeColumnsToContents();
        modelo->setEditStrategy(QSqlTableModel::OnManualSubmit);
        modelo->select();
        modelo1->select();



    }
    else qDebug ()<< "No se abri'o base de datos";
    Socket= new QUdpSocket (this); // Declaramos el socket
    connect (Socket,SIGNAL(readyRead()),this,SLOT(leerSocket())); //Conectamos el Signal listo para leer con un slot implementado con ready read
    soun = new QSound ("C:/Program Files (x86)/BoredCodes/Cubana Server/My Product Name/ringout.wav",this);//Sonido







}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()//Agregar un registro a la bd
{


    QString cadena,no,des,date,go,in,cap,airl,noti;
            no=no.number(ui->lineEdit->text().toInt());
            des = ui->lineEdit_2->text();
            date = ui->lineEdit_3->text();
            go = ui->lineEdit_4->text();
            in = ui->lineEdit_5->text();
            cap = cap.number(ui->lineEdit_6->text().toInt());
            airl = ui->lineEdit_7->text();
            noti= "*"+ QDate::currentDate().toString()+QTime::currentTime().toString()+ "Se ha agregado un nuevo vuelo con destino: "+des+" perteneciente a:"+airl;
            QSqlQuery qry;
            cadena = "insert into Vuelos (No,Destino, Fecha, Salida, Llegada,Capacidades,Aereolinea) values ("+no+",'"+des+"','"+date+"','"+go+"','"+in+"',"+cap+",'"+airl+"')";
            if(qry.exec(cadena))
            {
                modelo->submitAll();
                modelo->select();
                QByteArray Datagrama;// Arreglos de bytes para ser enviados por el socket
                Datagrama = noti.toLatin1();//Latin1 es un tipo de byteArray
                Socket->writeDatagram(Datagrama.data(),Datagrama.size(),QHostAddress::Broadcast,3333);//Escribe una notificacion
                ui->lineEdit->clear();
                ui->lineEdit_2->clear();
                ui->lineEdit_3->clear();
                ui->lineEdit_4->clear();
                ui->lineEdit_5->clear();

            }
            else
            {
                soun->play();

                QMessageBox::critical(this,"Error!!","No se logro completar la operacion");
            }



}



void MainWindow::on_pushButton_2_clicked() //Eliminar un registro
{
    QString txt =QInputDialog::getText(this,"Eliminar","Introduzca # de Vuelo que va a Eliminar");
    QSqlQuery qry;
    if(qry.exec("Delete  from Vuelos where Id="+txt))
    {
        modelo->submitAll();
        modelo->select();

    }
    else qDebug ()<< "No se borro";

}

void MainWindow::on_pushButton_3_clicked()
{

    mod *dd = new mod; // crea una interfaz para la modificacion
    dd->show();
    connect(dd,SIGNAL(Id(QString)),this,SLOT(returnID(QString)));//conecta la senal enviada por el mod con el gestor implementado





}






void MainWindow::leerSocket() // Leer el socket
{
    QByteArray Datagrama;
    QHostAddress host0; //Direccion de host
    QString cadena;
    QTextStream srr (&cadena);
    unsigned short puerto;
    Datagrama.resize(Socket->pendingDatagramSize());
    Socket->readDatagram(Datagrama.data(),Datagrama.size(),&host0,&puerto); //Lee un datagrama enviado por el socket
    // toma el tamaño del datagrama, los datos, y la direccion en memoria para la direccion de host y para el puerto.
    srr <<Datagrama;
    QSqlQuery qry;


    if (cadena.at(0)=='/')

    {
        cadena.replace("/","");
        qDebug()<<cadena;

        if (qry.exec(cadena))
        {
            cadena = "";
            while (qry.next())
            {
                cadena.append("/Este es el vuelo: "+qry.value(1).toString()+" perteneciente a la aereolinea: "+qry.value(7).toString()+ " con salida: "+qry.value(3).toString()+ " a las: "+qry.value(4).toString()+"\n");
            }
            Datagrama= cadena.toLatin1();
            Socket->writeDatagram(Datagrama.data(),Datagrama.size(),QHostAddress::Broadcast,3333);

        }
        else qDebug()<<"NO SIRVE";
    }

    else
    {


        if (qry.exec(cadena))
        {
            modelo1->submitAll();
            modelo1->select();

        }

        else
        {
            qDebug()<<"kkkk";
        }
    }
}







void MainWindow::on_actionConectar_triggered()
{
    if (Socket->bind(6666,QUdpSocket::ShareAddress))//conectar el socket
    {
        soun->play();

        QMessageBox::information(this,"Conectado","Iniciada conexion.");

    }
    else qDebug()<< "Error de conexion.";
}

void MainWindow::returnID(QString id)// Modificar un registro. Usamos la funcion update de sql
// a esta funcion se le pasa el registro a modificar y el campo de referencia
{

    QString no,des,date,go,in,cap,airl,noti;
    QSqlQuery qry;
    id=QString::number(id.toInt());


        if (!ui->lineEdit->text().isEmpty())
        {
            no=no.number(ui->lineEdit->text().toInt());
            if (qry.exec("Update Vuelos set No="+no+" where Id="+id)){
                modelo->submitAll();
                modelo->select();
            }
            else qDebug()<<"Bobo";
        }

        if (!ui->lineEdit_2->text().isEmpty())
        {
            des = ui->lineEdit_2->text();
            if (qry.exec("Update Vuelos set Destino='"+des+"' where Id="+id))
            {
                modelo->submitAll();
                modelo->select();
            }
            else qDebug()<<"rrr";
        }

        if (!ui->lineEdit_3->text().isEmpty())
        {
            date = ui->lineEdit_3->text();
            if (qry.exec("Update Vuelos set Fecha ='"+date+"' where Id="+id))
            {
                modelo->submitAll();
                modelo->select();
            }
            else qDebug()<<"LOcol";
        }

        if (!ui->lineEdit_4->text().isEmpty())
        {
            go = ui->lineEdit_4->text();
            if(qry.exec("Update Vuelos set Salida='"+go+"' where Id="+id))
            {
                modelo->submitAll();
                modelo->select();
            }
            else qDebug()<<"LMFAO Laughing my f***ing a*s off";

        }

        if (!ui->lineEdit_5->text().isEmpty())
        {
            in = ui->lineEdit_5->text();
            if (qry.exec("Update Vuelos set Llegada=' "+in+"' where Id="+id))
            {
                modelo->submitAll();
                modelo->select();
            }
            else qDebug()<<"Still LMFAO";
        }

        if(!ui->lineEdit_6->text().isEmpty())
        {
            cap = cap.number(ui->lineEdit_6->text().toInt());
            if (qry.exec("Update Vuelos set Capacidades= "+cap+" where Id="+id))
            {
                modelo->submitAll();
                modelo->select();
            }
            else qDebug()<<"fuck";

        }

        if (!ui->lineEdit_7->text().isEmpty())
        {
            airl = ui->lineEdit_7->text();
            if (qry.exec("Update Vuelos set Aereolinea =' "+airl+"' where Id="+id))
            {
                modelo->submitAll();
                modelo->select();
            }else qDebug()<<"POTOTO";
        }
        if (qry.exec("Select * from Vuelos where Id="+id)){
            QByteArray Datagrama;
            while(qry.next()){
                noti= "*Se ha modificado el vuelo: "+qry.value(1).toString()+" la informacion correspondiente al vuelo actualmente es \nDestino: "+qry.value(2).toString()+" Fecha: "+qry.value(3).toString()+" Hora de Salida: "+qry.value(4).toString()+" Hora de LLegada: "+qry.value(5).toString()+" Capacidades: "+qry.value(6).toString()+" Aereolinea: "+qry.value(7).toString();
                qDebug()<<noti;
            }
            Datagrama = noti.toLatin1();
            Socket->writeDatagram(Datagrama.data(),Datagrama.size(),QHostAddress::Broadcast,3333);
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            ui->lineEdit_3->clear();
            ui->lineEdit_4->clear();
            ui->lineEdit_5->clear();
        }
}
