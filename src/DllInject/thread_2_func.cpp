#include "thread_2_func.h"

extern GlobalData& globalData;

thread_2_func::thread_2_func()
{

}

void thread_2_func::run(){
    // 在你的EXE中调用：
    // 1. 获取目标线程ID（这里假设是全局钩子，targetThreadId=0）
    DWORD targetThreadId = 0; // 0 表示所有GUI线程

    // 2. 获取DLL路径（假设 globalData.GetDllPath() 返回 QString）
    QString dllPath = globalData.GetDllPath();
    std::wstring wideDllPath = dllPath.toStdWString();

    // 3. 获取DLL模块句柄（确保DLL已加载）
    HMODULE hDllModule = GetModuleHandle(wideDllPath.c_str());
    if (!hDllModule) {
        // 如果DLL未加载，尝试加载它
        hDllModule = LoadLibrary(wideDllPath.c_str());
        if (!hDllModule) {
            qDebug() << "Failed to load DLL: " << dllPath;
            return;
        }
    }

    // 4. 获取钩子回调函数（假设 globalData.GetHandle() 返回 HOOKPROC）
    HOOKPROC hookProc;
//    = globalData.GetHandle();
//    if (!hookProc) {
//        qDebug() << "Hook procedure is null!";
//        return;
//    }

    // 5. 设置消息钩子
    HHOOK hHook = SetWindowsHookEx(
        WH_GETMESSAGE,      // 钩子类型（监控消息队列）
        hookProc,           // 回调函数（必须在DLL中）
        hDllModule,         // DLL模块句柄
        targetThreadId      // 目标线程ID（0=全局钩子）
    );

    if (!hHook) {
        DWORD error = GetLastError();
        qDebug() << "SetWindowsHookEx failed! Error code: " << error;
        return;
    }

    qDebug() << "Hook successfully installed!";

    // 6. 保持钩子生效（例如，进入消息循环或等待）
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // 7. 卸载钩子（可选）
    UnhookWindowsHookEx(hHook);
}
