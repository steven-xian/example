#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_write_clicked()
{
    QFile file("file.dat");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "failed to write data";
        return;
    }

    QByteArray data;
    data.clear();
    data.push_back("DPPS");
    data.push_back(quint8(1));
    data.push_back(quint8(3));
    file.write(data, data.size());

    qDebug() << "sizeof time_t:" << sizeof(time_t);
    qDebug() << "data.size:" << data.size();
//    QDataStream out(&file);
//    out.setVersion(QDataStream::Ok);

//    out << "DPPS" << quint8(1) << quint8(3);
}
