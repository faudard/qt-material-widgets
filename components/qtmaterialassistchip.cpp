#include "qtmaterialassistchip.h"
#include "qtmaterialassistchip_p.h"

QtMaterialAssistChipPrivate::QtMaterialAssistChipPrivate(QtMaterialAssistChip *q)
    : q_ptr(q)
{
}

QtMaterialAssistChipPrivate::~QtMaterialAssistChipPrivate()
{
}

void QtMaterialAssistChipPrivate::init()
{
    Q_Q(QtMaterialAssistChip);
    q->setCheckable(false);
    q->setClosable(false);
}

QtMaterialAssistChip::QtMaterialAssistChip(QWidget *parent)
    : QtMaterialChip(parent), d_ptr(new QtMaterialAssistChipPrivate(this))
{
    d_func()->init();
}

QtMaterialAssistChip::~QtMaterialAssistChip()
{
}

QString QtMaterialAssistChip::label() const
{
    Q_D(const QtMaterialAssistChip);
    return d->label;
}

void QtMaterialAssistChip::setLabel(const QString &text)
{
    Q_D(QtMaterialAssistChip);
    d->label = text;
    setText(text);
}
