#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_verticalSlider_thrust_valueChanged(int value);

    void on_verticalSlider_rpm_valueChanged(int value);
    void updateSliderValue(QString);
    //void updateSliderValue2(QString);




    void on_pushButton_clicked();

    void on_verticalSlider_thrust_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    QSerialPort *arduino;
    static const quint16 arduino_mega_vendor_id = 6790;
    static const quint16 arduino_mega_product_id = 29987;
    QString arduino_port_name;
    bool arduino_is_available;
};

#endif // MAINWINDOW_H
