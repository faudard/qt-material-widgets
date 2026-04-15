#ifndef QTMATERIALDATEPICKER_P_H
#define QTMATERIALDATEPICKER_P_H

#include <QColor>
#include <QDate>
#include <QRect>
#include <QVector>

class QtMaterialDatePicker;

class QtMaterialDatePickerPrivate
{
    Q_DISABLE_COPY(QtMaterialDatePickerPrivate)
    Q_DECLARE_PUBLIC(QtMaterialDatePicker)

public:
    explicit QtMaterialDatePickerPrivate(QtMaterialDatePicker *q);
    ~QtMaterialDatePickerPrivate();

    void init();
    void rebuildCells();
    QRect cellRect(int index, const QRect &gridRect) const;
    int cellAt(const QPoint &pos, const QRect &gridRect) const;

    QtMaterialDatePicker *const q_ptr;
    bool useThemeColors;
    QDate selectedDate;
    QDate displayMonth;
    QDate minDate;
    QDate maxDate;
    QColor headerColor;
    QColor textColor;
    QColor selectedColor;
    QColor disabledTextColor;
    QVector<QDate> visibleDates;
};

#endif // QTMATERIALDATEPICKER_P_H
