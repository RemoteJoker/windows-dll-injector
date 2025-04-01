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

版本控制
============
[2025|04|02]
基础框架搭建