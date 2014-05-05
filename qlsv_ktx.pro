#-------------------------------------------------
#
# Project created by QtCreator 2014-03-18T02:31:32
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = qlsv_ktx
TEMPLATE = app
INCLUDEPATH += /home/xdien/NCReport2/include
LIBS += -L/home/xdien/NCReport2/lib -lNCReport

SOURCES += main.cpp\
        mainwindow.cpp \
    dialog_chitietsv.cpp \
    tablemodel_sv.cpp \
    config_sqlconnect.cpp \
    dialog_setting.cpp \
    dialogform.cpp \
    listtable.cpp \
    editdatatable.cpp \
    dialog_suadt.cpp \
    add_lop.cpp \
    form_liststbyphong.cpp

HEADERS  += mainwindow.h \
    dialog_chitietsv.h \
    tablemodel_sv.h \
    config_sqlconnect.h \
    dialog_setting.h \
    dialogform.h \
    listtable.h \
    editdatatable.h \
    dialog_suadt.h \
    add_lop.h \
    form_liststbyphong.h

FORMS    += mainwindow.ui \
    dialog_chitietsv.ui \
    dialog_setting.ui \
    dialogform.ui \
    editdatatable.ui \
    dialog_suadt.ui \
    add_lop.ui \
    form_liststbyphong.ui

RESOURCES += \
    libIcons.qrc