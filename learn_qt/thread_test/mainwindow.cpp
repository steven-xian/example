#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calcthread.h"
#include "generatethread.h"
#include <QThread>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "main thread:" << QThread::currentThreadId();

    qRegisterMetaType<QVector<int> >("QVector");
    //    calcThread.start();
    GenerateThread *thread = new GenerateThread;

    CalcThread *calcThread = new CalcThread;

    connect(this, &MainWindow::changeNum, thread, &GenerateThread::setNum);
    connect(thread, &GenerateThread::generated, calcThread, &CalcThread::changeNumbers, Qt::QueuedConnection);

    connect(thread, &GenerateThread::generated, this, [=](QVector<int> numbers){
        ui->listRandom->clear();
        for(int i = 0; i < numbers.size(); i++)
        {
            ui->listRandom->addItem(QString::number(numbers.at(i)));
        }
    }, Qt::QueuedConnection);

    connect(thread, &GenerateThread::generated, this, [=](){
        calcThread->start();
    });

    connect(calcThread, &CalcThread::sorted, [=](QVector<int> numbers){
        ui->listSort->clear();
        for(int i = 0; i < numbers.size(); i++)
        {
            ui->listSort->addItem(QString::number(numbers.at(i)));
        }
    });

    connect(ui->pushButton, &QPushButton::clicked, [=](){
        emit changeNum(10000);

        thread->start();
    });

    connect(this, &MainWindow::destroyed, this, [=](){
        thread->quit();
        thread->wait();
        thread->deleteLater();

        calcThread->quit();
        calcThread->wait();
        calcThread->deleteLater();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

