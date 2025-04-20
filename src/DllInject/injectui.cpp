#include "injectui.h"
#include "ui_injectui.h"

extern GlobalData& globalData;

InjectUi::InjectUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InjectUi)
{
    ui->setupUi(this);
    InitApp();
    InitData();
    InitConnect();
}

InjectUi::~InjectUi()
{
    delete ui;
}

void InjectUi::InitApp(){
    setWindowTitle(QString(m_software_name)+"版本:"+QString(m_software_version));
    setFixedSize(600,500);
}

void InjectUi::InitData(){
    processTimer=new QTimer;
    processTimer->start(2000);
}

void InjectUi::InitConnect(){
    connect(ui->SelectBtn,&QPushButton::clicked,this,&InjectUi::SelectFile);
    connect(processTimer,&QTimer::timeout,this,&InjectUi::FlushProcess);
}

void InjectUi::SelectFile(){
    //选择文件
    QString filePath=QFileDialog::getOpenFileName();
    globalData.BindPath(filePath);
}

void InjectUi::FlushProcess(){
    //刷新进程显示
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    // 创建进程快照
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        printf("CreateToolhelp32Snapshot 失败\n");
        return;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    // 获取第一个进程信息
    if (!Process32First(hProcessSnap, &pe32)) {
        printf("Process32First 失败\n");
        CloseHandle(hProcessSnap);
        return;
    }

    // 遍历所有进程
    do {
        printf("进程名: %s\n", pe32.szExeFile);
        printf("进程ID: %u\n\n", pe32.th32ProcessID);
    } while (Process32Next(hProcessSnap, &pe32));

    //此处可把进程信息放到表格中
    //ui->ProcessTable;
    CloseHandle(hProcessSnap);
}
