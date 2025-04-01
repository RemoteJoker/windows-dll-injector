#include "coredispatch.h"

CoreDispatch::CoreDispatch()
{

}

void CoreDispatch::Dispatch(unsigned index)
{
    if(index==0){
        //显示界面
        InjectUi *inject=new InjectUi;
        inject->show();
    }else if(index==1){
        //接口
        thread_0_func *t=new thread_0_func;
        t->start();
    }
}
