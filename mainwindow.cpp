#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>  // for sin()

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("IMU Visualizer");
    resize(900, 500);

    // 1. Create a line series and fill with fake sine wave data
    m_series = new QLineSeries();
    m_series->setName("Accel X (fake)");
    for (int i = 0; i < 100; i++) {
        double x = i;
        double y = std::sin(i * 0.2);   // fake waveform
        m_series->append(x, y);
    }

    // 2. Create the chart and add the series to it
    m_chart = new QChart();
    m_chart->addSeries(m_series);
    m_chart->setTitle("IMU Data");
    m_chart->createDefaultAxes();   // auto-scale axes to data
    m_chart->legend()->setVisible(true);

    // 3. Create the chart view (the actual widget) and set it as central
    m_chartView = new QChartView(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);  // smooth lines
    setCentralWidget(m_chartView);  // fills the whole window
}

MainWindow::~MainWindow()
{
    delete ui;
    // m_chart owns m_series, m_chartView owns m_chart
    // Qt parent-child ownership cleans them up automatically
}
