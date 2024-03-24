QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../s21_calculate.c \
    ../s21_check_str.c \
    ../s21_credit_calc.c \
    ../s21_deposit_calc.c \
    ../s21_parser.c \
    ../s21_rpn.c \
    credit.cpp \
    deposit.cpp \
    form.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    ../s21_SmartCalc.h \
    ../s21_credit_calc.h \
    ../s21_deposit_calc.h \
    credit.h \
    deposit.h \
    form.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    credit.ui \
    deposit.ui \
    form.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
