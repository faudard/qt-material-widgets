#ifndef QTMATERIALSIDESHEET_P_H
#define QTMATERIALSIDESHEET_P_H

#include <QColor>
#include <QWidget>
#include "qtmaterialsidesheet.h"

class QtMaterialSideSheetPrivate
{
    Q_DISABLE_COPY(QtMaterialSideSheetPrivate)
    Q_DECLARE_PUBLIC(QtMaterialSideSheet)

public:
    explicit QtMaterialSideSheetPrivate(QtMaterialSideSheet *q);
    ~QtMaterialSideSheetPrivate();

    void init();
    void updateSheetGeometry();
    QColor resolveBackgroundColor() const;
    QColor resolveOverlayColor() const;

    QtMaterialSideSheet *const q_ptr;
    QWidget *sheet;
    QLayout *contentLayout;
    bool useThemeColors;
    QColor backgroundColor;
    QColor overlayColor;
    int sheetWidth;
    bool modal;
    bool dismissOnOverlayClick;
    QtMaterialSideSheet::Side edge;
    bool opened;
};

#endif // QTMATERIALSIDESHEET_P_H
