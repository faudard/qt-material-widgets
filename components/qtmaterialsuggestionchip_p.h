#ifndef QTMATERIALSUGGESTIONCHIP_P_H
#define QTMATERIALSUGGESTIONCHIP_P_H

#include <QtGlobal>
#include <QString>

class QtMaterialSuggestionChip;

class QtMaterialSuggestionChipPrivate
{
    Q_DISABLE_COPY(QtMaterialSuggestionChipPrivate)
    Q_DECLARE_PUBLIC(QtMaterialSuggestionChip)

public:
    QtMaterialSuggestionChipPrivate(QtMaterialSuggestionChip *q);
    ~QtMaterialSuggestionChipPrivate();

    void init();

    QtMaterialSuggestionChip *const q_ptr;
    QString label;
};

#endif // QTMATERIALSUGGESTIONCHIP_P_H
