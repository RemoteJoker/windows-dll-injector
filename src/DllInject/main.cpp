#include "coredispatch.h"

#include <QApplication>

GlobalData& globalData = GlobalData::getInstance();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CoreDispatch *dispatch=new CoreDispatch;
    if(argc==1){
        //显示界面
        dispatch->Dispatch(0);
    }else if(argc==3){
        //接口 QString dllPath,HANDLE targetProcess
        globalData.BindPath(argv[1]);
        globalData.BindHandle(argv[2]);
        dispatch->Dispatch(1);
    }
    return a.exec();
}
