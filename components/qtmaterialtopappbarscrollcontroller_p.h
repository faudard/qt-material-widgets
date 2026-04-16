#ifndef QTMATERIALTOPAPPBARSCROLLCONTROLLER_P_H
#define QTMATERIALTOPAPPBARSCROLLCONTROLLER_P_H

#include <QtGlobal>

class QWidget;
class QAbstractScrollArea;

class QtMaterialTopAppBarScrollControllerPrivate
{
public:
    QtMaterialTopAppBarScrollControllerPrivate();

    QWidget *target;
    QAbstractScrollArea *scrollArea;
    int expandedHeight;
    int collapsedHeight;
    bool colorShiftEnabled;
    qreal collapseProgress;
};

#endif // QTMATERIALTOPAPPBARSCROLLCONTROLLER_P_H
