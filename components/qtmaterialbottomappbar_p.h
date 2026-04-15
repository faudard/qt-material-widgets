#ifndef QTMATERIALBOTTOMAPPBAR_P_H
#define QTMATERIALBOTTOMAPPBAR_P_H

#include <QColor>
#include <QMargins>

class QtMaterialBottomAppBar;

class QtMaterialBottomAppBarPrivate
{
    Q_DISABLE_COPY(QtMaterialBottomAppBarPrivate)
    Q_DECLARE_PUBLIC(QtMaterialBottomAppBar)

public:
    explicit QtMaterialBottomAppBarPrivate(QtMaterialBottomAppBar *q);

    void init();

    QtMaterialBottomAppBar *const q_ptr;
    bool centerFab;
    bool showFabCradle;
    int fabDiameter;
    QColor cradleColor;
    QMargins contentMargins;
};

#endif // QTMATERIALBOTTOMAPPBAR_P_H
