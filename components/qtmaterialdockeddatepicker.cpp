#include "qtmaterialdockeddatepicker.h"
#include "qtmaterialdockeddatepicker_p.h"

#include <QEvent>
#include <QPainter>

QtMaterialDockedDatePickerPrivate::QtMaterialDockedDatePickerPrivate()
    : useThemeColors(true)
    , date(QDate::currentDate())
    , minimumDate(QDate(1900, 1, 1))
    , maximumDate(QDate(2100, 12, 31))
{
}

QtMaterialDockedDatePicker::QtMaterialDockedDatePicker(QWidget *parent)
    : QWidget(parent)
    , d_ptr(new QtMaterialDockedDatePickerPrivate)
{
    setAttribute(Qt::WA_Hover);
    setVisible(false);
}

QtMaterialDockedDatePicker::~QtMaterialDockedDatePicker()
{
}

void QtMaterialDockedDatePicker::setUseThemeColors(bool value)
{
    Q_D(QtMaterialDockedDatePicker);
    d->useThemeColors = value;
    update();
}

bool QtMaterialDockedDatePicker::useThemeColors() const
{
    Q_D(const QtMaterialDockedDatePicker);
    return d->useThemeColors;
}

void QtMaterialDockedDatePicker::setDate(const QDate &date)
{
    Q_D(QtMaterialDockedDatePicker);
    d->date = date;
    update();
    emit dateSelected(d->date);
}

QDate QtMaterialDockedDatePicker::date() const
{
    Q_D(const QtMaterialDockedDatePicker);
    return d->date;
}

void QtMaterialDockedDatePicker::setMinimumDate(const QDate &date)
{
    Q_D(QtMaterialDockedDatePicker);
    d->minimumDate = date;
}

QDate QtMaterialDockedDatePicker::minimumDate() const
{
    Q_D(const QtMaterialDockedDatePicker);
    return d->minimumDate;
}

void QtMaterialDockedDatePicker::setMaximumDate(const QDate &date)
{
    Q_D(QtMaterialDockedDatePicker);
    d->maximumDate = date;
}

QDate QtMaterialDockedDatePicker::maximumDate() const
{
    Q_D(const QtMaterialDockedDatePicker);
    return d->maximumDate;
}

void QtMaterialDockedDatePicker::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialDockedDatePicker);
    d->backgroundColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialDockedDatePicker::backgroundColor() const
{
    Q_D(const QtMaterialDockedDatePicker);
    return d->backgroundColor;
}

void QtMaterialDockedDatePicker::setOverlayColor(const QColor &color)
{
    Q_D(QtMaterialDockedDatePicker);
    d->overlayColor = color;
    update();
}

QColor QtMaterialDockedDatePicker::overlayColor() const
{
    Q_D(const QtMaterialDockedDatePicker);
    return d->overlayColor;
}

void QtMaterialDockedDatePicker::open()
{
    show();
    raise();
}

void QtMaterialDockedDatePicker::close()
{
    hide();
}

bool QtMaterialDockedDatePicker::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched)
    Q_UNUSED(event)
    return false;
}

void QtMaterialDockedDatePicker::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(Qt::NoPen);
    painter.setBrush(backgroundColor().isValid() ? backgroundColor() : QColor(255, 255, 255));
    painter.drawRoundedRect(rect().adjusted(0, 0, -1, -1), 8, 8);
}
