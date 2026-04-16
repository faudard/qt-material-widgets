#ifndef QTMATERIALSTANDARDSIDESHEET_P_H
#define QTMATERIALSTANDARDSIDESHEET_P_H

#include <QColor>
#include <QVBoxLayout>

class QtMaterialStandardSideSheet;

class QtMaterialStandardSideSheetPrivate
{
    Q_DISABLE_COPY(QtMaterialStandardSideSheetPrivate)
    Q_DECLARE_PUBLIC(QtMaterialStandardSideSheet)

public:
    explicit QtMaterialStandardSideSheetPrivate(QtMaterialStandardSideSheet *q);
    void init();
    QColor resolvedBackgroundColor() const;

    QtMaterialStandardSideSheet *const q_ptr;
    bool useThemeColors;
    QColor backgroundColor;
    int width;
    bool expanded;
    QVBoxLayout *layout;
};

#endif // QTMATERIALSTANDARDSIDESHEET_P_H
