#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
  //  ui->templcdNumber->display(999);
    arduino = new QSerialPort(this);
//    qDebug() << "Number of ports: " << QSerialPortInfo::availablePorts().length() << "\n";
//       foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
//           qDebug() << "Description: " << serialPortInfo.description() << "\n";
//           qDebug() << "Has vendor id?: " << serialPortInfo.hasVendorIdentifier() << "\n";
//           qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier() << "\n";
//           qDebug() << "Has product id?: " << serialPortInfo.hasProductIdentifier() << "\n";
//           qDebug() << "Product ID: " << serialPortInfo.productIdentifier() << "\n";
//       }

       bool arduino_is_available = false;
          QString arduino_uno_port_name;
          //
          //  For each available serial port
          foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
              //  check if the serialport has both a product identifier and a vendor identifier
              if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()){
                  //  check if the product ID and the vendor ID match those of the arduino uno
                  if((serialPortInfo.productIdentifier() == arduino_uno_product_id)
                          && (serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id)){
                      arduino_is_available = true; //    arduino uno is available on this port
                      arduino_uno_port_name = serialPortInfo.portName();
                  }
              }
          }
          if(arduino_is_available){
                  qDebug() << "Found the arduino port...\n";
                  arduino->setPortName(arduino_uno_port_name);
                  arduino->open(QSerialPort::ReadOnly);
                  arduino->setBaudRate(QSerialPort::Baud115200);
                  arduino->setDataBits(QSerialPort::Data8);
                  arduino->setFlowControl(QSerialPort::NoFlowControl);
                  arduino->setParity(QSerialPort::NoParity);
                  arduino->setStopBits(QSerialPort::OneStop);
                  QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
              }else{
                  qDebug() << "Couldn't find the correct port for the arduino.\n";
                  //QMessageBox::information(this, "Serial Port Error", "Couldn't open serial port to arduino.");
              }
}

MainWindow::~MainWindow()
{
    if(arduino->isOpen()){
        arduino->close(); //    Close the serial port if it's open.
    }
    delete ui;
}

void MainWindow::setLCD(int x)
{
    if(x>200)x=200;
    ui->templcdNumber->display(x);
}
void MainWindow::readSerial()
{
       QByteArray aData = arduino->readLine();
       QString bpm = QString::fromStdString(aData.toStdString());
       bpm.chop(1);
       if(bpm.at(0) == "B")
       {
           bpm.remove(0,1);
           bpm.chop(1);
           setLCD(bpm.toInt());
       }
       qDebug()<<bpm;
}


