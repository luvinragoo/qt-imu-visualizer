#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QLineSeries>
#include <QChart>
#include <QChartView>
#include <QVBoxLayout>

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
};

#endif // MAINWINDOW_H
