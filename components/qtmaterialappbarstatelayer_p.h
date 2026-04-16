#ifndef QTMATERIALAPPBARSTATELAYER_P_H
#define QTMATERIALAPPBARSTATELAYER_P_H

#include <QColor>

class QtMaterialAppBarStateLayer;

class QtMaterialAppBarStateLayerPrivate
{
    Q_DISABLE_COPY(QtMaterialAppBarStateLayerPrivate)
    Q_DECLARE_PUBLIC(QtMaterialAppBarStateLayer)

public:
    QtMaterialAppBarStateLayerPrivate(QtMaterialAppBarStateLayer *q);
    ~QtMaterialAppBarStateLayerPrivate();

    void init();

    QtMaterialAppBarStateLayer *const q_ptr;
    bool useThemeColors;
    bool liftOnScroll;
    QColor baseColor;
    QColor scrolledColor;
    qreal scrollProgress;
};

#endif // QTMATERIALAPPBARSTATELAYER_P_H
