#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort>
#include <QSerialPortInfo>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QSerialPort *arduino;
    ~MainWindow();
    void setLCD(int x);
private slots:
    void readSerial();



private:
    Ui::MainWindow *ui;
    static const quint16 arduino_uno_vendor_id = 6790;
    static const quint16 arduino_uno_product_id = 29987;
};

#endif // MAINWINDOW_H
