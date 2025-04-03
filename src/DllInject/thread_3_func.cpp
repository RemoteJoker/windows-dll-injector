#include "thread_3_func.h"

extern GlobalData& globalData;

thread_3_func::thread_3_func()
{

}

void thread_3_func::run(){
    // 1. 打开目标进程
    HANDLE hProcess;
    //= OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!hProcess) {
        return;
    }

    // 2. 在目标进程分配内存并写入DLL路径
    LPVOID pRemoteMem;
    //= VirtualAllocEx(hProcess, NULL, strlen(dllPath) + 1,MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!pRemoteMem) {
        CloseHandle(hProcess);
        return;
    }
    //WriteProcessMemory(hProcess, pRemoteMem, dllPath, strlen(dllPath) + 1, NULL);

    // 3. 获取LoadLibraryA地址（kernel32.dll在所有进程的地址相同）
    LPTHREAD_START_ROUTINE pLoadLibrary;
    //= (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
    if (!pLoadLibrary) {
        VirtualFreeEx(hProcess, pRemoteMem, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return;
    }

    // 4. 获取目标进程的所有线程ID
    std::vector<DWORD> threadIds;
    //= GetThreadIds(pid);
    if (threadIds.empty()) {
        VirtualFreeEx(hProcess, pRemoteMem, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return;
    }

    // 5. 遍历所有线程，插入APC
    BOOL success = FALSE;
    for (DWORD tid : threadIds) {
        HANDLE hThread = OpenThread(THREAD_SET_CONTEXT, FALSE, tid);
        if (hThread) {
            QueueUserAPC((PAPCFUNC)pLoadLibrary, hThread, (ULONG_PTR)pRemoteMem);
            CloseHandle(hThread);
            success = TRUE;
        }
    }

    // 6. 清理资源
    VirtualFreeEx(hProcess, pRemoteMem, 0, MEM_RELEASE);
    CloseHandle(hProcess);
    return;
}
