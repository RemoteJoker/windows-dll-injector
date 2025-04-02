QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    coredispatch.cpp \
    globaldata.cpp \
    injectui.cpp \
    main.cpp \
    thread_0_func.cpp \
    thread_1_func.cpp \ \
    thread_2_func.cpp \
    thread_3_func.cpp

HEADERS += \
    coredispatch.h \
    globaldata.h \
    injectui.h \
    thread_0_func.h \
    thread_1_func.h \ \
    thread_2_func.h \
    thread_3_func.h

FORMS += \
    injectui.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
