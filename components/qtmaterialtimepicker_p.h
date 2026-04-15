#ifndef QTMATERIALTIMEPICKER_P_H
#define QTMATERIALTIMEPICKER_P_H

#include <QColor>
#include <QTime>

class QtMaterialTimePicker;

class QtMaterialTimePickerPrivate
{
    Q_DISABLE_COPY(QtMaterialTimePickerPrivate)
    Q_DECLARE_PUBLIC(QtMaterialTimePicker)

public:
    explicit QtMaterialTimePickerPrivate(QtMaterialTimePicker *q);
    ~QtMaterialTimePickerPrivate();

    void init();

    QtMaterialTimePicker *const q_ptr;
    bool useThemeColors;
    bool hourMode;
    bool mode24h;
    QTime selectedTime;
    QColor accentColor;
    QColor textColor;
};

#endif // QTMATERIALTIMEPICKER_P_H
