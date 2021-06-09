#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPOrtInfo>
#include <QDebug>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    arduino_is_available = false;
    arduino_port_name = "";
    arduino = new QSerialPort;
    ui->verticalSlider_thrust->setMaximum(100);
    ui->verticalSlider_rpm->setMaximum(100);


   foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
     {
           if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier())
           {
               if(serialPortInfo.vendorIdentifier() == arduino_mega_vendor_id)
               {
                   if(serialPortInfo.productIdentifier() == arduino_mega_product_id)
                   {
                       arduino_port_name = serialPortInfo.portName();
                       arduino_is_available = true;
                   }
               }
            }
         }
           if (arduino_is_available)
           {
               //open and configure the serialport
               arduino->setPortName(arduino_port_name);
               //arduino->open(QSerialPort::WriteOnly);
               arduino->open(QIODevice::ReadWrite); //harus bisa nulis dan baca dari Arduino
               arduino->setBaudRate(QSerialPort::Baud9600);
               arduino->setDataBits(QSerialPort::Data8);
               arduino->setParity(QSerialPort::NoParity);
               arduino->setStopBits(QSerialPort::OneStop);
               arduino->setFlowControl(QSerialPort::NoFlowControl);

           }
           else
           {
               //give error
               QMessageBox::warning(this, "Port error", "Couldn't find the Arduino!");
           }

 }

MainWindow::~MainWindow()
{
    if(arduino->isOpen())
    {
        arduino->close();
    }
    delete ui;
}

void MainWindow::on_verticalSlider_thrust_valueChanged(int value)
{
    float angka = (value);
    ui->label_Thrust->setText(QString("<span style=\" font-size:10pt;\">%1</span>").arg(value));
    MainWindow::updateSliderValue(QString("e%1").arg(value));
    qDebug() << angka;

}

void MainWindow::on_verticalSlider_rpm_valueChanged(int value)
{
    float angka = (value);
    ui->label_rpm->setText(QString("<span style=\" font-size:10pt;\">%1</span>").arg(value));
    MainWindow::updateSliderValue(QString("s%1").arg(value));
    qDebug() << angka;

}

void MainWindow::updateSliderValue(QString command)
{
    if(arduino->isWritable()){
        arduino->write(command.toStdString().c_str());
    }else{
        qDebug() << "Couldn't write to serial";
    }
}


void MainWindow::on_pushButton_clicked()
{
    QString value = ui->textEdit->toPlainText();
    float angka;
    angka =value.toFloat();
    float angka1 = angka*0.625;
    qDebug() << " angka: " << angka1;
}


/*void MainWindow::on_verticalSlider_thrust_sliderMoved(int position)
{

    qDebug() <<"posisi : " << position;
}*/
