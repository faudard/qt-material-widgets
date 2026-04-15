#ifndef QTMATERIALDOCKEDTOOLBAR_P_H
#define QTMATERIALDOCKEDTOOLBAR_P_H

#include <QColor>
#include <QHBoxLayout>
#include <qglobal.h>

class QtMaterialDockedToolBar;

class QtMaterialDockedToolBarPrivate
{
    Q_DISABLE_COPY(QtMaterialDockedToolBarPrivate)
    Q_DECLARE_PUBLIC(QtMaterialDockedToolBar)

public:
    explicit QtMaterialDockedToolBarPrivate(QtMaterialDockedToolBar *q);
    ~QtMaterialDockedToolBarPrivate();

    void init();

    QtMaterialDockedToolBar *const q_ptr;
    bool useThemeColors;
    QColor backgroundColor;
    QColor textColor;
    QColor dividerColor;
    bool showDivider;
    int contentPadding;
    QHBoxLayout *layout;
};

#endif // QTMATERIALDOCKEDTOOLBAR_P_H
