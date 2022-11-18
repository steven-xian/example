#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolBar>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_drawWidget = new DrawWidget();
    setCentralWidget(m_drawWidget);

    createToolBar();
    setMinimumSize(600, 400);
    ShowStyle();
    m_drawWidget->setWidth(m_widthSpinBox->value());
    m_drawWidget->setColor(Qt::black);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createToolBar()
{
    QToolBar *toolBar = addToolBar("Tool");
    m_styleLabel = new QLabel(tr("style"));
    m_styleComboBox = new QComboBox;
    m_styleComboBox->addItem(tr("SolidLine"), static_cast<int>(Qt::SolidLine));
    m_styleComboBox->addItem(tr("DashLine"), static_cast<int>(Qt::DashLine));
    m_styleComboBox->addItem(tr("DotLine"), static_cast<int>(Qt::DotLine));
    m_styleComboBox->addItem(tr("DashDotLine"), static_cast<int>(Qt::DashDotLine));
    m_styleComboBox->addItem(tr("DashDotDotLine"), static_cast<int>(Qt::DashDotDotLine));
    connect(m_styleComboBox, SIGNAL(activated(int)), this, SLOT(ShowStyle()));
    m_widthLabel = new QLabel(tr("Line Width"));
    m_widthSpinBox = new QSpinBox;
    connect(m_widthSpinBox, SIGNAL(valueChanged(int)), m_drawWidget, SLOT(setWidth(int)));
    m_colorBtn = new QToolButton;
    QPixmap pixmap(20, 20);
    pixmap.fill(Qt::black);
    m_colorBtn->setIcon(QIcon(pixmap));
    connect(m_colorBtn, SIGNAL(clicked(bool)), this, SLOT(ShowColor()));
    m_clearBtn = new QToolButton;
    m_clearBtn->setText(tr("Clear"));
    connect(m_clearBtn, SIGNAL(clicked(bool)), m_drawWidget, SLOT(clear()));
    toolBar->addWidget(m_styleLabel);
    toolBar->addWidget(m_styleComboBox);
    toolBar->addWidget(m_widthLabel);
    toolBar->addWidget(m_widthSpinBox);
    toolBar->addWidget(m_colorBtn);
    toolBar->addWidget(m_clearBtn);
}

void MainWindow::ShowStyle()
{
    m_drawWidget->setStyle(m_styleComboBox->itemData(m_styleComboBox->currentIndex(), Qt::UserRole).toInt());
}

void MainWindow::ShowColor()
{
    QColor color = QColorDialog::getColor(static_cast<int>(Qt::black), this);
    if (color.isValid())
    {
        m_drawWidget->setColor(color);
        QPixmap p(20,20);
        p.fill(color);
        m_colorBtn->setIcon(QIcon(p));
    }
}
