include(./general_config.pri)

TEMPLATE = app

TARGET = akvamarin

QT += core gui widgets

unix {
    QMAKE_LFLAGS += -no-pie
}

VPATH += ./src

INCLUDEPATH += \
    ../core/src \
    ./src/compouse \
    ./src/compouse/MainCompouse \
    ./src/widgets \
    ./src/widgets/SonarTargetView \
    ./src/widgets/SonarControl

SOURCES += \
    src/main.cpp \
    src/compouse/MainWindow.cpp \
    src/compouse/MainCompouse/MainCompouse.cpp \
    src/widgets/SonarControl/SonarControl.cpp \
    src/widgets/SonarControl/SonarCursorPos.cpp \
    src/widgets/SonarControl/SonarTableModel.cpp \
    src/widgets/SonarTargetView/PolarPoint.cpp \
    src/widgets/SonarTargetView/SonarTarget.cpp \
    src/widgets/SonarTargetView/SonarTargetGrid.cpp \
    src/widgets/SonarTargetView/SonarTargetScene.cpp \
    src/widgets/SonarTargetView/SonarTargetView.cpp

HEADERS += \
    src/compouse/MainWindow.h \
    src/compouse/MainCompouse/MainCompouse.h \
    src/widgets/SonarControl/SonarControl.h \
    src/widgets/SonarControl/SonarCursorPos.h \
    src/widgets/SonarControl/SonarTableModel.h \
    src/widgets/SonarTargetView/PolarPoint.h \
    src/widgets/SonarTargetView/SonarTarget.h \
    src/widgets/SonarTargetView/SonarTargetGrid.h \
    src/widgets/SonarTargetView/SonarTargetScene.h \
    src/widgets/SonarTargetView/SonarTargetView.h

RESOURCES += \
    ../res.qrc
