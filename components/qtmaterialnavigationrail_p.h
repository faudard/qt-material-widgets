#ifndef QTMATERIALNAVIGATIONRAIL_P_H
#define QTMATERIALNAVIGATIONRAIL_P_H

#include "qtmaterialnavigationrail.h"
#include <QList>
#include <QRect>

class QtMaterialNavigationRailPrivate
{
    Q_DISABLE_COPY(QtMaterialNavigationRailPrivate)
    Q_DECLARE_PUBLIC(QtMaterialNavigationRail)

public:
    struct RailItem
    {
        QIcon icon;
        QString text;
        QRect geometry;
    };

    QtMaterialNavigationRailPrivate(QtMaterialNavigationRail *q);
    ~QtMaterialNavigationRailPrivate();

    void init();
    void updateLayout();
    QRect itemRect(int index) const;
    QColor resolvedBackgroundColor() const;
    QColor resolvedForegroundColor() const;
    QColor resolvedAccentColor() const;

    QtMaterialNavigationRail *const q_ptr;
    QList<RailItem> items;
    int currentIndex;
    bool useThemeColors;
    bool showLabels;
    bool compact;
    int itemSpacing;
    QSize iconSize;
    QColor backgroundColor;
    QColor foregroundColor;
    QColor accentColor;
};

#endif // QTMATERIALNAVIGATIONRAIL_P_H
