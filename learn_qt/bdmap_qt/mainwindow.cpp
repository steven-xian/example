#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebEngineView>
#include <QWebChannel>
#include <QDir>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QThread>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    mapView = new QWebEngineView(this);
//    mapView->setParent(this);
//    this->setCentralWidget(mapView);

    QWebChannel* channel = new QWebChannel(this);
//    channel->registerObject("Route", (QObject*) this);
//    mapView->page()->setWebChannel(channel);

    ui->mapView->page()->load(QUrl("qrc:/bd/BDMap.html"));


//    connect(&m_timer, &QTimer::timeout, [=](){
//        qDebug() << "index:" << m_index;
//        QString posStr = posList.at(m_index);
//        QStringList pos = posStr.split(",");
//        mapView->page()->runJavaScript(QString("AddPoint(%1,%2)").arg(pos[0]).arg(pos[1]));
//        mapView->page()->runJavaScript("DrawPath()");

//        this->m_index ++;
//        if (m_index >= posList.length())
//        {
//            m_timer.stop();
//        }
//    });

//    m_timer.start(1000);
//    QThread::sleep(2000);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QStringList posList = {
        "87.065649,42.199145",
        "87.078297,42.217418",
        "87.095401,42.217418",
        "87.119260,42.211434",
        "87.121703,42.198931",
        "87.113367,42.189312",
        "87.092095,42.180974"
    };

    if (m_index >= posList.length())
    {
        return;
    }

    QString posStr = posList.at(m_index);
    QStringList pos = posStr.split(",");
    ui->mapView->page()->runJavaScript(QString("AddPoint(%1,%2)").arg(pos[0]).arg(pos[1]));
    ui->mapView->page()->runJavaScript("DrawPath()");
    this->m_index ++;

}
