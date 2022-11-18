#include "drawwidget.h"

DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
    setPalette(QPalette(Qt::white));
    m_pix = new QPixmap(size());
    m_pix->fill(Qt::white);
    setMinimumSize(60, 400);
}

void DrawWidget::setStyle(int s)
{
    m_style = s;
}

void DrawWidget::setWidth(int w)
{
    m_weight = w;
}

void DrawWidget::setColor(QColor c)
{
    m_color = c;
}

void DrawWidget::mousePressEvent(QMouseEvent *event)
{
    m_startPos= event->pos();
}

void DrawWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPainter *painter = new QPainter;
    QPen pen;
    pen.setStyle((Qt::PenStyle) m_style);
    pen.setWidth(m_weight);
    pen.setColor(m_color);
    painter->begin(m_pix);
    painter->setPen(pen);
    painter->drawLine(m_startPos, event->pos());
    painter->end();
    m_startPos = event->pos();
    update();
}

void DrawWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(QPoint(0, 0), *m_pix);
}

void DrawWidget::resizeEvent(QResizeEvent *event)
{
    if (height() > m_pix->height() || width() > m_pix->width())
    {
        QPixmap *newPix = new QPixmap(size());
        newPix->fill(Qt::white);
        QPainter painter(newPix);
        painter.drawPixmap(QPoint(0, 0), *m_pix);
        m_pix = newPix;
    }

    QWidget::resizeEvent(event);
}

void DrawWidget::clear()
{
    QPixmap *clearPix = new QPixmap(size());
    clearPix->fill(Qt::white);
    m_pix = clearPix;
    update();
}
