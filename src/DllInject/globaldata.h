#ifndef GLOBALDATA_H
#define GLOBALDATA_H

//宏区--start
#define m_software_name "DllInject"//软件名字
#define m_software_version "0.4"//软件版本
//宏区--end

//头文件包含区--start
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QObject>
#include <QThread>

#include <windows.h>
#include <tchar.h>
//头文件包含区--end

//结构体含区--start
#pragma pack(1)
#pragma pack()
//结构体含区--end

class GlobalData
{
public:
    // 删除拷贝构造函数和赋值运算符
    GlobalData(const GlobalData&) = delete;
    GlobalData& operator=(const GlobalData&) = delete;

    // 提供获取单例实例的静态方法
    static GlobalData& getInstance()
    {
        static GlobalData instance; // 静态局部变量，确保线程安全
        return instance;
    }

private:
    // 私有化构造函数
    GlobalData() {}

public:
    void BindPath(QString dllPath){
        g_dllPath=dllPath;
    }
    void BindHandle(HANDLE targetProcess){
        g_targetProcess=targetProcess;
    }
    QString GetDllPath(){
        return g_dllPath;
    }
    HANDLE GetHandle(){
        return g_targetProcess;
    }

private:
    QString g_dllPath;
    HANDLE g_targetProcess;
};

//获取单例实例
//GlobalData& globalData = GlobalData::getInstance();

#endif // GLOBALDATA_H
