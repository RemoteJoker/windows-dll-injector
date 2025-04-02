#include "thread_0_func.h"

extern GlobalData& globalData;

thread_0_func::thread_0_func()
{

}

void thread_0_func::run(){
    //开始注入
    HANDLE targetHandle=globalData.GetHandle();
    const char*dllPath=globalData.GetDllPath().toUtf8().constData();
    LPVOID pRemoteMem = VirtualAllocEx(globalData.GetHandle(), NULL,
                                       strlen(dllPath) + 1,MEM_COMMIT, PAGE_READWRITE);
    WriteProcessMemory(targetHandle, pRemoteMem, dllPath, strlen(dllPath) + 1, NULL);
    // 获取LoadLibrary地址
    // 显式调用ANSI版本
    HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
    LPTHREAD_START_ROUTINE pLoadLibrary =
        (LPTHREAD_START_ROUTINE)GetProcAddress(hKernel32, "LoadLibraryW");
    // 创建远程线程
    HANDLE hThread = CreateRemoteThread(targetHandle, NULL, 0,
                                      pLoadLibrary, pRemoteMem, 0, NULL);
    if (!hThread) {
        VirtualFreeEx(targetHandle, pRemoteMem, 0, MEM_RELEASE);
    }
    // 等待线程执行完成
    WaitForSingleObject(hThread, INFINITE);
    // 清理资源
    VirtualFreeEx(targetHandle, pRemoteMem, 0, MEM_RELEASE);
    CloseHandle(hThread);
}
