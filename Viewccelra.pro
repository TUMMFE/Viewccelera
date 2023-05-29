QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adxl355data.cpp \
    analysisdataframe.cpp \
    datafile.cpp \
    main.cpp \
    mainwindow.cpp \
    processeddatatab.cpp \
    qcustomplot.cpp \
    rawdatatab.cpp \
    savedialog.cpp

HEADERS += \
    adxl355data.h \
    analysisdataframe.h \
    datafile.h \
    mainwindow.h \
    processeddatatab.h \
    qcustomplot.h \
    rawdatatab.h \
    savedialog.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    Viewccelra_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

QMAKE_CXXFLAGS += -Wa,-mbig-obj

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

win32 {
DESTDIR = $$PWD/bin
QMAKE_POST_LINK +=  windeployqt $$shell_path($$DESTDIR/$${TARGET}.exe)
}
