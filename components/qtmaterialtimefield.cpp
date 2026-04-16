#include "qtmaterialtimefield.h"
#include "qtmaterialtimefield_p.h"

QtMaterialTimeFieldPrivate::QtMaterialTimeFieldPrivate(QtMaterialTimeField *q)
    : q_ptr(q), time(QTime::currentTime()), displayFormat(QStringLiteral("hh:mm ap"))
{
}

QtMaterialTimeField::QtMaterialTimeField(QWidget *parent)
    : QtMaterialTextField(parent), d_ptr(new QtMaterialTimeFieldPrivate(this))
{
    setReadOnly(true);
}

QtMaterialTimeField::~QtMaterialTimeField()
{
}

void QtMaterialTimeField::setTime(const QTime &time)
{
    Q_D(QtMaterialTimeField);
    if (d->time == time) {
        return;
    }
    d->time = time;
    setText(d->time.toString(d->displayFormat));
    emit timeChanged(d->time);
}

QTime QtMaterialTimeField::time() const
{
    Q_D(const QtMaterialTimeField);
    return d->time;
}

void QtMaterialTimeField::setDisplayFormat(const QString &format)
{
    Q_D(QtMaterialTimeField);
    d->displayFormat = format;
    setText(d->time.toString(d->displayFormat));
}

QString QtMaterialTimeField::displayFormat() const
{
    Q_D(const QtMaterialTimeField);
    return d->displayFormat;
}
