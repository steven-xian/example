#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QColor>
#include <QPixmap>
#include <QPoint>
#include <QPainter>
#include <QPalette>

class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = nullptr);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

signals:

public slots:
    void setStyle(int);
    void setWidth(int);
    void setColor(QColor);
    void clear();

private:
    QPixmap *m_pix;
    QPoint m_startPos;
    QPoint m_endPos;
    int m_style;
    int m_weight;
    QColor m_color;
};

#endif // DRAWWIDGET_H
