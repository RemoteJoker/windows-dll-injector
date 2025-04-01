#ifndef COREDISPATCH_H
#define COREDISPATCH_H

#include "globaldata.h"
#include "injectui.h"

class CoreDispatch:public QObject
{
    Q_OBJECT
public:
    CoreDispatch();

    void Dispatch(unsigned index);

private:
};

#endif // COREDISPATCH_H
