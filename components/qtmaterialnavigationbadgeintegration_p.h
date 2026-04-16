#ifndef QTMATERIALNAVIGATIONBADGEINTEGRATION_P_H
#define QTMATERIALNAVIGATIONBADGEINTEGRATION_P_H

#include <QtGlobal>
#include <QColor>
#include <QHash>
#include <QString>

class QWidget;
class QtMaterialNavigationBadgeIntegration;

struct QtMaterialNavigationBadgeData
{
    QtMaterialNavigationBadgeData()
        : count(0),
          visible(false)
    {
    }

    int count;
    bool visible;
    QString text;
};

class QtMaterialNavigationBadgeIntegrationPrivate
{
    Q_DISABLE_COPY(QtMaterialNavigationBadgeIntegrationPrivate)
    Q_DECLARE_PUBLIC(QtMaterialNavigationBadgeIntegration)

public:
    explicit QtMaterialNavigationBadgeIntegrationPrivate(QtMaterialNavigationBadgeIntegration *q);
    ~QtMaterialNavigationBadgeIntegrationPrivate();

    void init();
    QString displayTextForIndex(int index) const;

    QtMaterialNavigationBadgeIntegration *const q_ptr;
    QWidget *navigationWidget;
    bool useThemeColors;
    QColor backgroundColor;
    QColor textColor;
    int maxCount;
    QHash<int, QtMaterialNavigationBadgeData> badges;
};

#endif // QTMATERIALNAVIGATIONBADGEINTEGRATION_P_H
