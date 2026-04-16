#ifndef QTMATERIALINPUTTIMEPICKER_P_H
#define QTMATERIALINPUTTIMEPICKER_P_H

#include <QTime>

class QtMaterialInputTimePicker;

class QtMaterialInputTimePickerPrivate
{
public:
    QtMaterialInputTimePickerPrivate(QtMaterialInputTimePicker *q);

    QtMaterialInputTimePicker *const q_ptr;
    bool useThemeColors;
    bool twentyFourHour;
    QTime time;
};

#endif // QTMATERIALINPUTTIMEPICKER_P_H
