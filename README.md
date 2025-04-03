# windows-dll-injector
DLL injector written using the Qt framework

DLL基础知识
===========
1.DLL是Windows专属的动态库PE文件
2.DLL有两种
①.DLL作为库供主模块使用，适配以下场景
--主模块编辑者看不到源码，用于一些特定场合的交付
--考虑程序加载时间，不重要的内容不需要在程序启动时加载，可以放入库中需要时加载以显著提高启动效率
②.DLL作为单独的模块，由注入器注入到第三方进程中独立的执行一些任务
3.DLL使用
-隐式链接:
----需要头文件和库文件，编译时加载
-显示链接:
----只需要DLL文件，同时执行如下步骤
-》使用 LoadLibrary 加载 DLL。
-》使用 GetProcAddress 获取函数地址。
-》调用函数。
-》使用 FreeLibrary 释放 DLL。

DLL注入相关
============
①远程线程注入:
利用CreateRemoteThread在目标线程创建远程线程执行LoadLibrary加载DLL
最常用的方法，需要获取被注入进程的句柄，以及将要注入DLL的路径
首先要申请内存，把DLL写入。相当于在被注入进程中先把自己的东西放进去
其次要获取kernel.dll这个模块的LoadLiarbry这个函数，加载之前放进去的DLL
最后要创建一个线程，来运行DLL。

简单理解就是先把东西放进去，在启动自己放进去的东西
那么如果想看看自己的进程会不会被监控，显而易见CreateRemoteThread和LoadLibrary两个API是重点

②注册表注入:
AppInit_DLLs:指定要加载的DLL列表
LoadAppInit_DLLs:启用|禁用

HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Windows
HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows NT\CurrentVersion\Windows

这个方法特点:
隐蔽性好，不容易被检测
所有使用user32.dll的进程都会受影响

③消息钩子注入:
消息钩子注入是利用Windows消息机制将DLL加载到目标进程的一种方法，通过设置全局Windows钩子来实现DLL注入
注入程序（exe）
  │
  ├── 加载钩子DLL（LoadLibrary）
  │
  ├── 设置钩子（SetWindowsHookEx）
  │   │
  │   └── 系统将DLL映射到目标进程
  │       │
  │       ├── 目标进程调用HookProc
  │       │   │
  │       │   ├── 你的代码处理消息
  │       │   │
  │       │   └── CallNextHookEx
  │       │
  │       └── 消息继续传递
  │
  └── 卸载钩子（UnhookWindowsHookEx）

④APC（异步过程调用）注入
APC（异步过程调用）注入是一种利用Windows线程APC队列将DLL加载到目标进程的技术。它比远程线程注入更隐蔽，适用于特定场景

Step 1: 获取目标进程的所有线程。
Step 2: 在每个线程的APC队列插入 LoadLibraryA/W 调用。
Step 3: 当目标线程进入可警告状态时，自动加载DLL


版本控制
============
0.1
[2025|04|02]
基础框架搭建

0.2
[2025|04|02]
完成远程线程注入；注册表注入；内容补充

0.3
[2025|04|03]
完成消息钩子注入；APC注入；内容补充