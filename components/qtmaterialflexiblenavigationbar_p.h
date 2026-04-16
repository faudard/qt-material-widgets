#ifndef QTMATERIALFLEXIBLENAVIGATIONBAR_P_H
#define QTMATERIALFLEXIBLENAVIGATIONBAR_P_H

#include "qtmaterialflexiblenavigationbar.h"
#include <QVector>
#include <QRect>

class QtMaterialFlexibleNavigationBarPrivate
{
    Q_DISABLE_COPY(QtMaterialFlexibleNavigationBarPrivate)
    Q_DECLARE_PUBLIC(QtMaterialFlexibleNavigationBar)

public:
    QtMaterialFlexibleNavigationBarPrivate(QtMaterialFlexibleNavigationBar *q);
    ~QtMaterialFlexibleNavigationBarPrivate();

    struct Item {
        QIcon icon;
        QString text;
        QRect rect;
    };

    void init();
    void layoutItems();

    QtMaterialFlexibleNavigationBar *const q_ptr;
    QVector<Item> items;
    bool useThemeColors;
    bool showLabels;
    bool showActiveIndicator;
    int iconSize;
    int currentIndex;
    QColor backgroundColor;
    QColor foregroundColor;
    QColor selectedColor;
    QColor indicatorColor;
};

#endif // QTMATERIALFLEXIBLENAVIGATIONBAR_P_H
