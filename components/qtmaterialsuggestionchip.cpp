#include "qtmaterialsuggestionchip.h"
#include "qtmaterialsuggestionchip_p.h"

QtMaterialSuggestionChipPrivate::QtMaterialSuggestionChipPrivate(QtMaterialSuggestionChip *q)
    : q_ptr(q)
{
}

QtMaterialSuggestionChipPrivate::~QtMaterialSuggestionChipPrivate()
{
}

void QtMaterialSuggestionChipPrivate::init()
{
    Q_Q(QtMaterialSuggestionChip);
    q->setCheckable(false);
    q->setClosable(false);
}

QtMaterialSuggestionChip::QtMaterialSuggestionChip(QWidget *parent)
    : QtMaterialChip(parent), d_ptr(new QtMaterialSuggestionChipPrivate(this))
{
    d_func()->init();
}

QtMaterialSuggestionChip::~QtMaterialSuggestionChip()
{
}

QString QtMaterialSuggestionChip::label() const
{
    Q_D(const QtMaterialSuggestionChip);
    return d->label;
}

void QtMaterialSuggestionChip::setLabel(const QString &text)
{
    Q_D(QtMaterialSuggestionChip);
    d->label = text;
    setText(text);
}
