#ifndef QTMATERIALPROGRESS_P_H
#define QTMATERIALPROGRESS_P_H

#include <QColor>
#include <QScopedPointer>
#include "qtmaterialprogress.h"

class QtMaterialProgressDelegate;

class QtMaterialProgressPrivate
{
    Q_DISABLE_COPY(QtMaterialProgressPrivate)
    Q_DECLARE_PUBLIC(QtMaterialProgress)

public:
    QtMaterialProgressPrivate(QtMaterialProgress *q);
    ~QtMaterialProgressPrivate();

    void init();

    QtMaterialProgress *const q_ptr;
    QtMaterialProgressDelegate *delegate;
    Material::ProgressType progressType;
    QColor progressColor;
    QColor backgroundColor;
    QColor textColor;
    qreal trackThickness;
    bool useThemeColors;
    bool roundedCaps;
    bool showPercentage;
};

#endif // QTMATERIALPROGRESS_P_H
