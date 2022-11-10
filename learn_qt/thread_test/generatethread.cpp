#include "generatethread.h"
#include <QVector>
#include <QtDebug>
#include <QElapsedTimer>

GenerateThread::GenerateThread(QObject* parent) : QThread(parent)
{

}

void GenerateThread::setNum(int num)
{
    m_num = num;
}

void GenerateThread::run()
{
    QVector<int> numbers;

    qDebug() << "generate in thread:" << QThread::currentThreadId();

    QElapsedTimer timer;

    timer.start();
    for(int i = 0; i < m_num; i++)
    {
        numbers.push_back(qrand() % 100000 );
    }

    qDebug() << "finished generating in " << timer.elapsed() << " miliseconds";

    emit generated(numbers);
}
