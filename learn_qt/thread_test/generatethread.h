#ifndef GENERATETHREAD_H
#define GENERATETHREAD_H

#include <QThread>
#include <QVector>

class GenerateThread : public QThread
{
    Q_OBJECT

public:
    GenerateThread(QObject* parent = nullptr);
    void setNum(int num);

signals:
    void generated(QVector<int> numbers);

protected:
    void run();

private:
    int m_num = 0;
};

#endif // GENERATETHREAD_H
