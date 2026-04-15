#ifndef QTMATERIALFLOATINGTOOLBAR_P_H
#define QTMATERIALFLOATINGTOOLBAR_P_H

#include <QColor>
#include <QHBoxLayout>
#include <qglobal.h>

class QtMaterialFloatingToolBar;

class QtMaterialFloatingToolBarPrivate
{
    Q_DISABLE_COPY(QtMaterialFloatingToolBarPrivate)
    Q_DECLARE_PUBLIC(QtMaterialFloatingToolBar)

public:
    explicit QtMaterialFloatingToolBarPrivate(QtMaterialFloatingToolBar *q);
    ~QtMaterialFloatingToolBarPrivate();

    void init();

    QtMaterialFloatingToolBar *const q_ptr;
    bool useThemeColors;
    QColor backgroundColor;
    QColor textColor;
    int radius;
    int contentPadding;
    QHBoxLayout *layout;
};

#endif // QTMATERIALFLOATINGTOOLBAR_P_H
