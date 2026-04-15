#ifndef QTMATERIALDOCKEDDATEPICKER_P_H
#define QTMATERIALDOCKEDDATEPICKER_P_H

#include <QDate>
#include <QColor>
#include <QPointer>

class QWidget;

class QtMaterialDockedDatePickerPrivate
{
    Q_DISABLE_COPY(QtMaterialDockedDatePickerPrivate)

public:
    QtMaterialDockedDatePickerPrivate();

    bool useThemeColors;
    QDate date;
    QDate minimumDate;
    QDate maximumDate;
    QColor backgroundColor;
    QColor overlayColor;
    QPointer<QWidget> anchorWidget;
};

#endif // QTMATERIALDOCKEDDATEPICKER_P_H
