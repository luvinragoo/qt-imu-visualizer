#include "mainwindow.h"
#include "IMUSensor.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{

    IMUSensor mpu("MPU6050", 3);
    mpu.setCalibration(0, 0.02f);
    mpu.setCalibration(1, -0.01f);
    mpu.setCalibration(2, 0.00f);

    qDebug() << "Sensor :" << QString::fromStdString(mpu.getName());
    qDebug() << "Axis 0 :" << mpu.getReading(0);
    qDebug() << "Axis 1 :" << mpu.getReading(1);
    qDebug() << "Axis 2 :" << mpu.getReading(2);


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
