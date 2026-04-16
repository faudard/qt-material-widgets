#ifndef QTMATERIALBADGEDECORATOR_P_H
#define QTMATERIALBADGEDECORATOR_P_H

#include <QPointer>
#include <QPoint>

class QWidget;
class QtMaterialBadge;

class QtMaterialBadgeDecoratorPrivate
{
public:
    QtMaterialBadgeDecoratorPrivate();

    QPointer<QWidget> target;
    QPointer<QtMaterialBadge> badge;
    QPoint offset;
    bool autoHideWhenZero;
};

#endif // QTMATERIALBADGEDECORATOR_P_H
