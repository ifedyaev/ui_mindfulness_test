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

DESTDIR = bin

SOURCES += \
    main.cpp \
    src/ui_mindfulness.cpp

HEADERS += \
    src/save_data.hpp \
    src/ui_mindfulness.hpp \
    ui/graphics_view.hpp

FORMS += \
    ui/ui_mindfulness.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md

# copy plugins/platforms
unix {
    # set path
    INSTALL_PATH = $$DESTDIR
    PATH_OUT_LIB = lib
    # init out dirs
    QMAKE_RPATHDIR += $$PATH_OUT_LIB
    DIRS_LIBS_PLATFORM = plugins/platforms
    MKDIR_PATH = $$INSTALL_PATH/$$PATH_OUT_LIB
    # create dirs
    create_copy.commands += $${QMAKE_MKDIR} $$shell_path($$MKDIR_PATH);
    # copy
    create_copy.commands += $${QMAKE_COPY_DIR} $$shell_path($$[QT_INSTALL_CONFIGURATION]/$$DIRS_LIBS_PLATFORM) $$INSTALL_PATH

    QMAKE_EXTRA_TARGETS += create_copy
}
