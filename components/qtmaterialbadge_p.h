#ifndef QTMATERIALBADGE_P_H
#define QTMATERIALBADGE_P_H

#include <QColor>
#include <QString>

class QtMaterialBadge;

class QtMaterialBadgePrivate
{
    Q_DISABLE_COPY(QtMaterialBadgePrivate)
    Q_DECLARE_PUBLIC(QtMaterialBadge)

public:
    explicit QtMaterialBadgePrivate(QtMaterialBadge *q);

    void init();

    QtMaterialBadge *const q_ptr;
    bool useThemeColors;
    QString text;
    int count;
    bool countMode;
    bool visibleWhenZero;
    bool outlined;
    QColor backgroundColor;
    QColor textColor;
    QColor borderColor;
};

#endif // QTMATERIALBADGE_P_H
