#ifndef QTMATERIALMODALBOTTOMSHEET_P_H
#define QTMATERIALMODALBOTTOMSHEET_P_H

#include <QColor>

class QWidget;
class QFrame;
class QVBoxLayout;
class QtMaterialModalBottomSheet;

class QtMaterialModalBottomSheetPrivate
{
    Q_DISABLE_COPY(QtMaterialModalBottomSheetPrivate)
    Q_DECLARE_PUBLIC(QtMaterialModalBottomSheet)

public:
    QtMaterialModalBottomSheetPrivate(QtMaterialModalBottomSheet *q);
    ~QtMaterialModalBottomSheetPrivate();

    void init();
    void updatePalette();
    void updateLayoutGeometry();

    QtMaterialModalBottomSheet *const q_ptr;

    bool useThemeColors;
    bool open;
    bool dismissOnOverlayClick;
    int sheetHeight;
    QColor backgroundColor;
    QColor overlayColor;

    QFrame *sheet;
    QVBoxLayout *sheetLayout;
};

#endif // QTMATERIALMODALBOTTOMSHEET_P_H
