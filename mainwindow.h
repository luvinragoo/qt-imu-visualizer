#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QLineSeries>
#include <QChart>
#include <QChartView>
#include <QVBoxLayout>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT  // Qt macro — required for signals/slots to work

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // Chart components
    QLineSeries  *m_series;    // the line being plotted
    QChart       *m_chart;     // the chart container
    QChartView   *m_chartView; // the widget that displays the chart

    QUdpSocket *m_udpSocket; // listens for incoming UDP packets

private slots:
    void onDataReceived(); // called automatically when data arrives
};

#endif // MAINWINDOW_H
