#ifndef THREAD_2_FUNC_H
#define THREAD_2_FUNC_H

#include "globaldata.h"

class thread_2_func : public QThread
{
    Q_OBJECT
public:
    thread_2_func();

    void run() override;

private:
};

#endif // THREAD_2_FUNC_H
