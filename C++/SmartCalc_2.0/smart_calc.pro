QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/controller.cc \
    Model/model.cc \
    Model/model_credit.cc \
    Model/model_deposit.cc \
    View/credit.cc \
    View/deposit.cc \
    View/graph.cc \
    View/mainwindow.cc \
    View/main.cpp \
    qcustomplot.cc

HEADERS += \
    Controller/controller.h \
    Model/model.h \
    Model/model_credit.h \
    Model/model_deposit.h \
    View/credit.h \
    View/deposit.h \
    View/graph.h \
    View/mainwindow.h \
    qcustomplot.h

FORMS += \
    View/credit.ui \
    View/deposit.ui \
    View/graph.ui \
    View/mainwindow.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    View/pics/icon.qrc

RC_ICONS = calculator.ico
