#ifndef QTMATERIALSKELETON_P_H
#define QTMATERIALSKELETON_P_H

#include "qtmaterialskeleton.h"

class QColor;

class QtMaterialSkeletonPrivate
{
    Q_DISABLE_COPY(QtMaterialSkeletonPrivate)
    Q_DECLARE_PUBLIC(QtMaterialSkeleton)

public:
    QtMaterialSkeletonPrivate(QtMaterialSkeleton *q);
    ~QtMaterialSkeletonPrivate();

    void init();

    QtMaterialSkeleton *const q_ptr;
    bool useThemeColors;
    QColor *backgroundColor;
    QColor *highlightColor;
    bool animationEnabled;
    int cornerRadius;
    int lineCount;
    bool circular;
    QtMaterialSkeleton::DisplayMode displayMode;
    int shimmerOffset;
    int timerId;
};

#endif // QTMATERIALSKELETON_P_H
