#include "qtmaterialinputchip.h"
#include "qtmaterialinputchip_p.h"

QtMaterialInputChipPrivate::QtMaterialInputChipPrivate(QtMaterialInputChip *q)
    : q_ptr(q)
{
}

QtMaterialInputChipPrivate::~QtMaterialInputChipPrivate()
{
}

void QtMaterialInputChipPrivate::init()
{
    Q_Q(QtMaterialInputChip);
    q->setCheckable(false);
    q->setClosable(true);
    QObject::connect(q, &QtMaterialChip::closeClicked, q, &QtMaterialInputChip::removeRequested);
}

QtMaterialInputChip::QtMaterialInputChip(QWidget *parent)
    : QtMaterialChip(parent), d_ptr(new QtMaterialInputChipPrivate(this))
{
    d_func()->init();
}

QtMaterialInputChip::~QtMaterialInputChip()
{
}

QString QtMaterialInputChip::label() const
{
    Q_D(const QtMaterialInputChip);
    return d->label;
}

void QtMaterialInputChip::setLabel(const QString &text)
{
    Q_D(QtMaterialInputChip);
    d->label = text;
    setText(text);
}
