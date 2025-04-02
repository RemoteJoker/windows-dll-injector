#include "thread_1_func.h"

extern GlobalData& globalData;

thread_1_func::thread_1_func()
{

}

void thread_1_func::run(){
    //dllPath为dll路径，使用注册表注入的方式
    std::wstring dllPath = globalData.GetDllPath().toStdWString();
    // 1. 打开目标注册表键
    HKEY hKey;
    LONG lResult = RegOpenKeyEx(
        HKEY_LOCAL_MACHINE,
        _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Windows"),
        0,
        KEY_SET_VALUE | KEY_WOW64_64KEY, // 64位系统上操作64位注册表
        &hKey);

    if (lResult != ERROR_SUCCESS) {
        qDebug() << "无法打开注册表键，错误代码:" << lResult;
        return;
    }
    // 2. 设置AppInit_DLLs值
    lResult = RegSetValueEx(
        hKey,
        _T("AppInit_DLLs"),
        0,
        REG_SZ,
        (const BYTE*)dllPath.c_str(),
        (dllPath.size() + 1) * sizeof(wchar_t));

    if (lResult != ERROR_SUCCESS) {
        qDebug() << "设置AppInit_DLLs失败，错误代码:" << lResult;
        RegCloseKey(hKey);
        return;
    }
    // 3. 启用DLL加载功能
    DWORD dwValue = 1;
    lResult = RegSetValueEx(
        hKey,
        _T("LoadAppInit_DLLs"),
        0,
        REG_DWORD,
        (const BYTE*)&dwValue,
        sizeof(dwValue));
    RegCloseKey(hKey);
    if (lResult != ERROR_SUCCESS) {
        qDebug() << "启用LoadAppInit_DLLs失败，错误代码:" << lResult;
        return;
    }
    qDebug() << "注册表注入设置成功!";
    // 4. 现代Windows系统还需要设置签名要求
    HKEY hKeySecure;
    lResult = RegOpenKeyEx(
        HKEY_LOCAL_MACHINE,
        _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Windows"),
        0,
        KEY_SET_VALUE | KEY_WOW64_64KEY,
        &hKeySecure);
    if (lResult == ERROR_SUCCESS) {
        dwValue = 0; // 0=不要求签名，1=要求签名
        RegSetValueEx(
            hKeySecure,
            _T("RequireSignedAppInit_DLLs"),
            0,
            REG_DWORD,
            (const BYTE*)&dwValue,
            sizeof(dwValue));
        RegCloseKey(hKeySecure);
    }
}
