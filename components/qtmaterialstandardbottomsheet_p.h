#ifndef QTMATERIALSTANDARDBOTTOMSHEET_P_H
#define QTMATERIALSTANDARDBOTTOMSHEET_P_H

#include <QColor>

class QVBoxLayout;
class QtMaterialStandardBottomSheet;

class QtMaterialStandardBottomSheetPrivate
{
    Q_DISABLE_COPY(QtMaterialStandardBottomSheetPrivate)
    Q_DECLARE_PUBLIC(QtMaterialStandardBottomSheet)

public:
    QtMaterialStandardBottomSheetPrivate(QtMaterialStandardBottomSheet *q);
    ~QtMaterialStandardBottomSheetPrivate();

    void init();
    void updateGeometry();

    QtMaterialStandardBottomSheet *const q_ptr;

    bool useThemeColors;
    bool expanded;
    int sheetHeight;
    QColor backgroundColor;
    QColor dividerColor;

    QVBoxLayout *layout;
};

#endif // QTMATERIALSTANDARDBOTTOMSHEET_P_H
