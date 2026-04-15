#ifndef QTMATERIALPULLTOREFRESH_P_H
#define QTMATERIALPULLTOREFRESH_P_H

#include <QString>
#include <QColor>

class QWidget;
class QtMaterialLoadingIndicator;
class QtMaterialPullToRefresh;

class QtMaterialPullToRefreshPrivate
{
    Q_DISABLE_COPY(QtMaterialPullToRefreshPrivate)
    Q_DECLARE_PUBLIC(QtMaterialPullToRefresh)

public:
    QtMaterialPullToRefreshPrivate(QtMaterialPullToRefresh *q);

    void init();

    QtMaterialPullToRefresh *const q_ptr;
    QWidget *target;
    QtMaterialLoadingIndicator *indicator;
    bool useThemeColors;
    bool refreshing;
    bool tracking;
    QColor indicatorColor;
    QColor textColor;
    QString labelText;
    QString refreshingText;
    int triggerDistance;
    int currentOffset;
    QPoint pressPos;
};

#endif // QTMATERIALPULLTOREFRESH_P_H
