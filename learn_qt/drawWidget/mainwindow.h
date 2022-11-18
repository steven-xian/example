#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QToolButton>
#include "drawwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createToolBar();

public slots:
    void ShowStyle();
    void ShowColor();

private:
    Ui::MainWindow *ui;
    DrawWidget *m_drawWidget;
    QLabel *m_styleLabel;
    QComboBox *m_styleComboBox;
    QLabel *m_widthLabel;
    QSpinBox *m_widthSpinBox;
    QToolButton *m_colorBtn;
    QToolButton *m_clearBtn;
};
#endif // MAINWINDOW_H
