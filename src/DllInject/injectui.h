#ifndef INJECTUI_H
#define INJECTUI_H

#include <QWidget>
#include "globaldata.h"
#include "thread_0_func.h"
namespace Ui {
class InjectUi;
}

class InjectUi : public QWidget
{
    Q_OBJECT

public:
    explicit InjectUi(QWidget *parent = nullptr);
    ~InjectUi();

    void InitApp();
    void InitData();
    void InitConnect();

protected slots:
    void SelectFile();//选择DLL文件
    void StartInject();//开始注入
    void FlushProcess();//刷新进程显示

private:
    Ui::InjectUi *ui;
    QTimer *processTimer;
};

#endif // INJECTUI_H
