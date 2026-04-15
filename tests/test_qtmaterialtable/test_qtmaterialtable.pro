QT += core gui widgets testlib
TEMPLATE = app
CONFIG += testcase no_testcase_installs c++11

win32 {
    COMPONENTS_LIB = $$top_builddir/components/$(OBJECTS_DIR)/components.lib
} else {
    COMPONENTS_LIB = $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a
}

LIBS += $$COMPONENTS_LIB
PRE_TARGETDEPS += $$COMPONENTS_LIB
INCLUDEPATH += $$top_srcdir/components
TARGET = test_qtmaterialtable
