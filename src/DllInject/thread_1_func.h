#ifndef THREAD_1_FUNC_H
#define THREAD_1_FUNC_H

#include "globaldata.h"

class thread_1_func : public QThread
{
    Q_OBJECT
public:
    thread_1_func();

    void run() override;

private:
};
#endif // THREAD_1_FUNC_H
