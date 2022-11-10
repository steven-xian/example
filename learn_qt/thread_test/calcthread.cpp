#include "calcthread.h"
#include <QDebug>
#include <QElapsedTimer>

CalcThread::CalcThread()
{

}

void CalcThread::changeNumbers(QVector<int> numbers)
{
    m_numbers = numbers;
}

void CalcThread::run()
{
    qDebug() << "start sort in thread " << QThread::currentThreadId();

    QElapsedTimer timer;

    timer.start();
    for (int i = 0; i < m_numbers.size(); i++)
    {
        for (int j = i + 1; j < m_numbers.size(); j++)
        {
            if (m_numbers.at(i) > m_numbers.at(j))
            {
                int t = m_numbers.at(i);
                m_numbers[i] = m_numbers[j];
                m_numbers[j] = t;
            }
        }
    }

    int seconds = timer.elapsed();

    qDebug() << "finish sort in " << seconds << " miliseconds";

    emit sorted(m_numbers);
}
