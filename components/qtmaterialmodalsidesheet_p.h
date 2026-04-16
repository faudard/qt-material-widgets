#ifndef QTMATERIALMODALSIDESHEET_P_H
#define QTMATERIALMODALSIDESHEET_P_H

#include "qtmaterialmodalsidesheet.h"

#include <QColor>
#include <QPointer>
#include <QVBoxLayout>

class QtMaterialModalSideSheetPrivate
{
    Q_DISABLE_COPY(QtMaterialModalSideSheetPrivate)
    Q_DECLARE_PUBLIC(QtMaterialModalSideSheet)

public:
    explicit QtMaterialModalSideSheetPrivate(QtMaterialModalSideSheet *q);

    void init();
    QRect sheetRect() const;
    QColor resolvedBackgroundColor() const;
    QColor resolvedOverlayColor() const;

    QtMaterialModalSideSheet *const q_ptr;
    bool useThemeColors;
    QColor backgroundColor;
    QColor overlayColor;
    int width;
    QtMaterialModalSideSheet::Side side;
    bool dismissOnOverlayClick;
    QWidget *sheetWidget;
    QVBoxLayout *sheetLayout;
};

#endif // QTMATERIALMODALSIDESHEET_P_H
