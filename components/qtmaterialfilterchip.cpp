#include "qtmaterialfilterchip.h"
#include "qtmaterialfilterchip_p.h"

QtMaterialFilterChipPrivate::QtMaterialFilterChipPrivate(QtMaterialFilterChip *q)
    : q_ptr(q)
{
}

QtMaterialFilterChipPrivate::~QtMaterialFilterChipPrivate()
{
}

void QtMaterialFilterChipPrivate::init()
{
    Q_Q(QtMaterialFilterChip);
    q->setCheckable(true);
    q->setClosable(false);
}

QtMaterialFilterChip::QtMaterialFilterChip(QWidget *parent)
    : QtMaterialChip(parent), d_ptr(new QtMaterialFilterChipPrivate(this))
{
    d_func()->init();
}

QtMaterialFilterChip::~QtMaterialFilterChip()
{
}

QString QtMaterialFilterChip::label() const
{
    Q_D(const QtMaterialFilterChip);
    return d->label;
}

void QtMaterialFilterChip::setLabel(const QString &text)
{
    Q_D(QtMaterialFilterChip);
    d->label = text;
    setText(text);
}
