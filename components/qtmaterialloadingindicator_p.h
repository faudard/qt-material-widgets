#ifndef QTMATERIALLOADINGINDICATOR_P_H
#define QTMATERIALLOADINGINDICATOR_P_H

#include <QObject>
#include <QColor>

class QPropertyAnimation;
class QtMaterialLoadingIndicator;

class QtMaterialLoadingIndicatorPrivate
{
    Q_DISABLE_COPY(QtMaterialLoadingIndicatorPrivate)
    Q_DECLARE_PUBLIC(QtMaterialLoadingIndicator)

public:
    QtMaterialLoadingIndicatorPrivate(QtMaterialLoadingIndicator *q);

    void init();

    QtMaterialLoadingIndicator *const q_ptr;
    bool useThemeColors;
    bool indeterminate;
    bool autoStart;
    bool running;
    QColor indicatorColor;
    QColor trackColor;
    qreal lineWidth;
    int size;
    qreal dashOffset;
    QPropertyAnimation *dashOffsetAnimation;
};

#endif // QTMATERIALLOADINGINDICATOR_P_H
