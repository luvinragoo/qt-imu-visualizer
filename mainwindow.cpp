#include <QValueAxis>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("IMU Visualizer");
    resize(900, 500);

    m_series = new QLineSeries();
    m_series->setName("Accel X (g)");

    // 2. Create the chart and add the series to it
    m_chart = new QChart();
    m_chart->addSeries(m_series);
    m_chart->setTitle("IMU Live Data");

    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(0, 100);
    axisX->setTitleText("Samples");

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(-2.0, 2.0); // accelerometer range in g
    axisY->setTitleText("g");

    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_chart->addAxis(axisY, Qt::AlignLeft);
    m_series->attachAxis(axisX);
    m_series->attachAxis(axisY);

    m_chart->legend()->setVisible(true);

    // 3. Create the chart view (the actual widget) and set it as central
    m_chartView = new QChartView(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);  // smooth lines
    setCentralWidget(m_chartView);  // fills the whole window

    //UDP Socket Setup
    m_udpSocket = new QUdpSocket(this);
    m_udpSocket->bind(QHostAddress::Any, 5005); // listens on port 5005

    // Signal -> Slot connection
    // When socket has data -> call onDataReceived() function
    connect(m_udpSocket, &QUdpSocket::readyRead,
            this, &MainWindow::onDataReceived);

    qDebug() << "Listening for UDP on port 5005...";

}

MainWindow::~MainWindow()
{
    delete ui;
    // m_chart owns m_series, m_chartView owns m_chart
    // Qt parent-child ownership cleans them up automatically
}

void MainWindow::onDataReceived()
{
    while (m_udpSocket->hasPendingDatagrams()) {
        QByteArray buffer;
        buffer.resize(m_udpSocket->pendingDatagramSize());
        m_udpSocket->readDatagram(buffer.data(), buffer.size());

        // Parse CSV: IMU,timestamp,ax,ay,az,gx,gy,gz
        QString message = QString::fromUtf8(buffer);
        QStringList parts = message.split(',');

        if (parts.size() >= 8 && parts[0] == "IMU") {
            float ax = parts[2].toFloat();

            // Append to chart
            m_series->append(m_sampleCount, ax);
            m_sampleCount++;

            // Scroll X axis to keep latest 100 samples visible
            if (m_sampleCount > 100) {
                QValueAxis *axisX = qobject_cast<QValueAxis*>(
                    m_chart->axes(Qt::Horizontal).first());
                if (axisX)
                    axisX->setRange(m_sampleCount - 100, m_sampleCount);
            }
        }
    }
}

