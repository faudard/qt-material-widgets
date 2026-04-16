#ifndef QTMATERIALSHEETHANDLE_P_H
#define QTMATERIALSHEETHANDLE_P_H

#include <QColor>
#include <QPoint>

class QtMaterialSheetHandle;

class QtMaterialSheetHandlePrivate
{
    Q_DISABLE_COPY(QtMaterialSheetHandlePrivate)
    Q_DECLARE_PUBLIC(QtMaterialSheetHandle)

public:
    QtMaterialSheetHandlePrivate(QtMaterialSheetHandle *q);
    ~QtMaterialSheetHandlePrivate();

    void init();

    QtMaterialSheetHandle *const q_ptr;
    bool useThemeColors;
    QColor color;
    int handleWidth;
    int handleHeight;
    int hitTargetSize;
    bool cycleDetentsOnClick;
    bool pressed;
    bool dragging;
    QPoint pressPos;
};

#endif // QTMATERIALSHEETHANDLE_P_H
