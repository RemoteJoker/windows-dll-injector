#ifndef THREAD_3_FUNC_H
#define THREAD_3_FUNC_H

#include "globaldata.h"

class thread_3_func : public QThread
{
    Q_OBJECT
public:
    thread_3_func();

    void run() override;

private:
};

#endif // THREAD_3_FUNC_H
