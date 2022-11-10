#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTreeView"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    treeView = new QTreeView(this);
    this->setCentralWidget(treeView);

    QString data = "{ +\
                   \"name\": \"%1\", \
                   \"connection\": [], \
                   \"file\": [], \
                   \"solution\":[] \
                    }";
    treeModel = new TreeModel(data, this);

    treeView->setModel(treeModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

