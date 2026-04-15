QT += core gui widgets

TEMPLATE = app

CONFIG += c++11

SOURCES = appbarsettingseditor.cpp \
    autocompletesettingseditor.cpp \
    avatarsettingseditor.cpp \
    badgesettingseditor.cpp \
    carouselsettingseditor.cpp \
    checkboxsettingseditor.cpp \
    circularprogresssettingseditor.cpp \
    datetimepickersettingseditor.cpp \
    dialogsettingseditor.cpp \
    drawersettingseditor.cpp \
    fabsettingseditor.cpp \
    flatbuttonsettingseditor.cpp \
    gridlistsettingseditor.cpp \
    iconbuttonsettingseditor.cpp \
    listitemsettingseditor.cpp \
    listsettingseditor.cpp \
    loadingprogresssettingseditor.cpp \
    main.cpp \
    mainwindow.cpp \
    menusettingseditor.cpp \
    navigationsettingseditor.cpp \
    papersettingseditor.cpp \
    progresssettingseditor.cpp \
    radiobuttonsettingseditor.cpp \
    raisedbuttonsettingseditor.cpp \
    scrollbarsettingseditor.cpp \
    searchfieldsettingseditor.cpp \
    selectfieldsettingseditor.cpp \
    slidersettingseditor.cpp \
    snackbarlayoutsettingseditor.cpp \
    snackbarsettingseditor.cpp \
    steppersettingseditor.cpp \
    tablesettingseditor.cpp \
    tabssettingseditor.cpp \
    textfieldsettingseditor.cpp \
    togglesettingseditor.cpp \
    toolbarsettingseditor.cpp \
    treesettingseditor.cpp

HEADERS = appbarsettingseditor.h \
    autocompletesettingseditor.h \
    avatarsettingseditor.h \
    badgesettingseditor.h \
    carouselsettingseditor.h \
    checkboxsettingseditor.h \
    circularprogresssettingseditor.h \
    datetimepickersettingseditor.h \
    dialogsettingseditor.h \
    drawersettingseditor.h \
    fabsettingseditor.h \
    flatbuttonsettingseditor.h \
    gridlistsettingseditor.h \
    iconbuttonsettingseditor.h \
    listitemsettingseditor.h \
    listsettingseditor.h \
    loadingprogresssettingseditor.h \
    mainwindow.h \
    menusettingseditor.h \
    navigationsettingseditor.h \
    papersettingseditor.h \
    progresssettingseditor.h \
    qtmaterialselectfield.h \
    qtmaterialselectfield_p.h \
    radiobuttonsettingseditor.h \
    raisedbuttonsettingseditor.h \
    scrollbarsettingseditor.h \
    searchfieldsettingseditor.h \
    selectfieldsettingseditor.h \
    slidersettingseditor.h \
    snackbarlayoutsettingseditor.h \
    snackbarsettingseditor.h \
    steppersettingseditor.h \
    tablesettingseditor.h \
    tabssettingseditor.h \
    textfieldsettingseditor.h \
    togglesettingseditor.h \
    toolbarsettingseditor.h \
    treesettingseditor.h

win32 {
    COMPONENTS_LIB = $$top_builddir/components/$(OBJECTS_DIR)/components.lib
} else {
    COMPONENTS_LIB = $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a
}

LIBS += $$COMPONENTS_LIB
PRE_TARGETDEPS += $$COMPONENTS_LIB
INCLUDEPATH += $$top_srcdir/components

TARGET = examples-exe

RESOURCES += \
    examples.qrc

FORMS += \
    avatarsettingsform.ui \
    badgesettingsform.ui \
    checkboxsettingsform.ui \
    fabsettingsform.ui \
    flatbuttonsettingsform.ui \
    iconbuttonsettingsform.ui \
    progresssettingsform.ui \
    circularprogresssettingsform.ui \
    slidersettingsform.ui \
    snackbarsettingsform.ui \
    radiobuttonsettingsform.ui \
    togglesettingsform.ui \
    textfieldsettingsform.ui \
    tabssettingsform.ui \
    dialogsettingsform.ui \
    drawersettingsform.ui \
    scrollbarsettingsform.ui \
    appbarsettingsform.ui
