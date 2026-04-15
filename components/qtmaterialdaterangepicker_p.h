#ifndef QTMATERIALDATERANGEPICKER_P_H
#define QTMATERIALDATERANGEPICKER_P_H

#include <QColor>
#include <QDate>
#include <QPoint>

class QtMaterialDateRangePicker;

class QtMaterialDateRangePickerPrivate
{
    Q_DISABLE_COPY(QtMaterialDateRangePickerPrivate)
    Q_DECLARE_PUBLIC(QtMaterialDateRangePicker)

public:
    explicit QtMaterialDateRangePickerPrivate(QtMaterialDateRangePicker *q);

    void init();

    QtMaterialDateRangePicker *const q_ptr;
    bool useThemeColors;
    bool showDualMonth;
    QDate startDate;
    QDate endDate;
    QDate minimumDate;
    QDate maximumDate;
    QDate displayedMonth;
    QDate hoverDate;
    QColor headerColor;
    QColor textColor;
    QColor selectedColor;
    QColor rangeColor;
    QColor disabledTextColor;
};

#endif // QTMATERIALDATERANGEPICKER_P_H
