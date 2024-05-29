QT += core gui sql charts core5compat

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

INCLUDEPATH += \
            src/ \
            QtCharts/

SOURCES += \
    src/FileParser.cpp \
    src/ItemDelegate.cpp \
    src/Model.cpp \
    src/OnePolicyWidget.cpp \
    src/PieChart.cpp \
    src/Policy.cpp \
    src/TableView.cpp \
    src/main.cpp \
    src/Widget.cpp \
    src/PolicyMaker.cpp

HEADERS += \
    src/FileParser.h \
    src/ItemDelegate.h \
    src/Model.h \
    src/OnePolicyWidget.h \
    src/PieChart.h \
    src/Policy.h \
    src/TableView.h \
    src/Widget.h \
    src/PolicyMaker.h

OTHER_FILES += \
        $$PWD/src/PPolic.txt

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
