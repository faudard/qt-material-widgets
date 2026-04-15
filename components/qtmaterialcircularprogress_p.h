#ifndef QTMATERIALCIRCULARPROGRESS_P_H
#define QTMATERIALCIRCULARPROGRESS_P_H

#include <QColor>
#include "qtmaterialcircularprogress.h"

class QtMaterialCircularProgressDelegate;

class QtMaterialCircularProgressPrivate
{
    Q_DISABLE_COPY(QtMaterialCircularProgressPrivate)
    Q_DECLARE_PUBLIC(QtMaterialCircularProgress)

public:
    QtMaterialCircularProgressPrivate(QtMaterialCircularProgress *q);
    ~QtMaterialCircularProgressPrivate();

    void init();

    QtMaterialCircularProgress *const q_ptr;
    QtMaterialCircularProgressDelegate *delegate;
    Material::ProgressType progressType;
    QColor color;
    QColor backgroundColor;
    qreal lineWidth;
    int size;
    bool useThemeColors;
    bool showPercentage;
    bool roundedCaps;
};

#endif // QTMATERIALCIRCULARPROGRESS_P_H
