#ifndef THREAD_0_FUNC_H
#define THREAD_0_FUNC_H

#include "globaldata.h"

class thread_0_func : public QThread
{
    Q_OBJECT
public:
    thread_0_func();

    void run() override;

private:
};

#endif // THREAD_0_FUNC_H
