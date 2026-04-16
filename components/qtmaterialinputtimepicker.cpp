#include "qtmaterialinputtimepicker.h"
#include "qtmaterialinputtimepicker_p.h"

QtMaterialInputTimePickerPrivate::QtMaterialInputTimePickerPrivate(QtMaterialInputTimePicker *q)
    : q_ptr(q), useThemeColors(true), twentyFourHour(false), time(QTime::currentTime())
{
}

QtMaterialInputTimePicker::QtMaterialInputTimePicker(QWidget *parent)
    : QWidget(parent), d_ptr(new QtMaterialInputTimePickerPrivate(this))
{
}

QtMaterialInputTimePicker::~QtMaterialInputTimePicker()
{
}

void QtMaterialInputTimePicker::setUseThemeColors(bool value)
{
    Q_D(QtMaterialInputTimePicker);
    d->useThemeColors = value;
}

bool QtMaterialInputTimePicker::useThemeColors() const
{
    Q_D(const QtMaterialInputTimePicker);
    return d->useThemeColors;
}

void QtMaterialInputTimePicker::setTime(const QTime &time)
{
    Q_D(QtMaterialInputTimePicker);
    if (d->time == time) {
        return;
    }
    d->time = time;
    emit timeChanged(d->time);
}

QTime QtMaterialInputTimePicker::time() const
{
    Q_D(const QtMaterialInputTimePicker);
    return d->time;
}

void QtMaterialInputTimePicker::setTwentyFourHour(bool value)
{
    Q_D(QtMaterialInputTimePicker);
    d->twentyFourHour = value;
}

bool QtMaterialInputTimePicker::isTwentyFourHour() const
{
    Q_D(const QtMaterialInputTimePicker);
    return d->twentyFourHour;
}
