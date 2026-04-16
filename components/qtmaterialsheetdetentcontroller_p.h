#ifndef QTMATERIALSHEETDETENTCONTROLLER_P_H
#define QTMATERIALSHEETDETENTCONTROLLER_P_H

#include <QPointer>
#include "qtmaterialsheetdetentcontroller.h"

class QtMaterialSheetDetentControllerPrivate
{
    Q_DISABLE_COPY(QtMaterialSheetDetentControllerPrivate)
    Q_DECLARE_PUBLIC(QtMaterialSheetDetentController)

public:
    QtMaterialSheetDetentControllerPrivate(QtMaterialSheetDetentController *q);
    ~QtMaterialSheetDetentControllerPrivate();

    void updateTargetGeometry();
    int currentExtentForDetent(QtMaterialSheetDetentController::Detent detent) const;

    QtMaterialSheetDetentController *const q_ptr;
    QPointer<QWidget> target;
    QtMaterialSheetDetentController::Orientation orientation;
    QtMaterialSheetDetentController::Detent currentDetent;
    bool halfExpandedEnabled;
    int collapsedExtent;
    int halfExpandedExtent;
    int expandedExtent;
};

#endif // QTMATERIALSHEETDETENTCONTROLLER_P_H
