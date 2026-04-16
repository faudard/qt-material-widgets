#ifndef QTMATERIALINPUTCHIP_P_H
#define QTMATERIALINPUTCHIP_P_H

#include <QtGlobal>
#include <QString>

class QtMaterialInputChip;

class QtMaterialInputChipPrivate
{
    Q_DISABLE_COPY(QtMaterialInputChipPrivate)
    Q_DECLARE_PUBLIC(QtMaterialInputChip)

public:
    QtMaterialInputChipPrivate(QtMaterialInputChip *q);
    ~QtMaterialInputChipPrivate();

    void init();

    QtMaterialInputChip *const q_ptr;
    QString label;
};

#endif // QTMATERIALINPUTCHIP_P_H
