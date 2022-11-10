#ifndef CALCTHREAD_H
#define CALCTHREAD_H

#include <QThread>
#include <QVector>

class CalcThread : public QThread
{
    Q_OBJECT

public:
    CalcThread();

    void changeNumbers(QVector<int> numbers);

signals:
    void sorted(QVector<int> numbers);

protected:
    void run();

private:
    QVector<int> m_numbers;
};

#endif // CALCTHREAD_H
