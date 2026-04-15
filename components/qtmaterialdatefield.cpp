#include "qtmaterialdatefield.h"
#include "qtmaterialdatefield_p.h"
#include "qtmaterialdockeddatepicker.h"

#include <QEvent>

QtMaterialDateFieldPrivate::QtMaterialDateFieldPrivate()
    : date(QDate::currentDate())
    , minimumDate(QDate(1900, 1, 1))
    , maximumDate(QDate(2100, 12, 31))
    , displayFormat(QStringLiteral("yyyy-MM-dd"))
    , picker(0)
{
}

QtMaterialDateField::QtMaterialDateField(QWidget *parent)
    : QtMaterialTextField(parent)
    , d_ptr(new QtMaterialDateFieldPrivate)
{
    Q_D(QtMaterialDateField);
    d->picker = new QtMaterialDockedDatePicker(this);
    setReadOnly(true);
    setDate(d->date);
    connect(d->picker, SIGNAL(dateSelected(QDate)), this, SLOT(setDate(QDate)));
}

QtMaterialDateField::~QtMaterialDateField()
{
}

void QtMaterialDateField::setDate(const QDate &date)
{
    Q_D(QtMaterialDateField);
    d->date = date;
    setText(d->date.toString(d->displayFormat));
    emit dateChanged(d->date);
}

QDate QtMaterialDateField::date() const
{
    Q_D(const QtMaterialDateField);
    return d->date;
}

void QtMaterialDateField::setDisplayFormat(const QString &format)
{
    Q_D(QtMaterialDateField);
    d->displayFormat = format;
    setText(d->date.toString(d->displayFormat));
}

QString QtMaterialDateField::displayFormat() const
{
    Q_D(const QtMaterialDateField);
    return d->displayFormat;
}

void QtMaterialDateField::setMinimumDate(const QDate &date)
{
    Q_D(QtMaterialDateField);
    d->minimumDate = date;
    d->picker->setMinimumDate(date);
}

QDate QtMaterialDateField::minimumDate() const
{
    Q_D(const QtMaterialDateField);
    return d->minimumDate;
}

void QtMaterialDateField::setMaximumDate(const QDate &date)
{
    Q_D(QtMaterialDateField);
    d->maximumDate = date;
    d->picker->setMaximumDate(date);
}

QDate QtMaterialDateField::maximumDate() const
{
    Q_D(const QtMaterialDateField);
    return d->maximumDate;
}

QtMaterialDockedDatePicker *QtMaterialDateField::picker() const
{
    Q_D(const QtMaterialDateField);
    return d->picker;
}

bool QtMaterialDateField::event(QEvent *event)
{
    if (QEvent::MouseButtonPress == event->type()) {
        picker()->open();
    }
    return QtMaterialTextField::event(event);
}
