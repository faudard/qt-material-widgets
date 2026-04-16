#ifndef QTMATERIALFILTERCHIP_P_H
#define QTMATERIALFILTERCHIP_P_H

#include <QtGlobal>
#include <QString>

class QtMaterialFilterChip;

class QtMaterialFilterChipPrivate
{
    Q_DISABLE_COPY(QtMaterialFilterChipPrivate)
    Q_DECLARE_PUBLIC(QtMaterialFilterChip)

public:
    QtMaterialFilterChipPrivate(QtMaterialFilterChip *q);
    ~QtMaterialFilterChipPrivate();

    void init();

    QtMaterialFilterChip *const q_ptr;
    QString label;
};

#endif // QTMATERIALFILTERCHIP_P_H
