TEMPLATE = app
INCLUDEPATH += .

QT += sql widgets widgets

SOURCES += main.cpp \
    moviewindow.cpp \
    moviedelegate.cpp \
    editablesqlmodel.cpp \
    actorsdialog.cpp



# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS =  moviewindow.h moviedelegate.h initDB.h \
    editablesqlmodel.h \
    actorsdialog.h

FORMS += \
    moviewindow.ui \
    actorsdialog.ui

INSTALLS += target


wince*: {
    CONFIG(debug, debug|release):sqlPlugins.files = $$QT_BUILD_TREE/plugins/sqldrivers/*d4.dll
    CONFIG(release, debug|release):sqlPlugins.files = $$QT_BUILD_TREE/plugins/sqldrivers/*[^d]4.dll
    sqlPlugins.path = sqldrivers
    DEPLOYMENT += sqlPlugins
}
