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

void InjectUi::InitData(){}

void InjectUi::InitConnect(){
    connect(ui->SelectBtn,&QPushButton::clicked,this,&InjectUi::SelectFile);
}

void InjectUi::SelectFile(){
    //选择文件
    QString filePath=QFileDialog::getOpenFileName();
    globalData.BindPath(filePath);
}
