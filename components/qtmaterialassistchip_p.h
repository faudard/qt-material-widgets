#ifndef QTMATERIALASSISTCHIP_P_H
#define QTMATERIALASSISTCHIP_P_H

#include <QtGlobal>
#include <QScopedPointer>
#include <QString>

class QtMaterialAssistChip;

class QtMaterialAssistChipPrivate
{
    Q_DISABLE_COPY(QtMaterialAssistChipPrivate)
    Q_DECLARE_PUBLIC(QtMaterialAssistChip)

public:
    QtMaterialAssistChipPrivate(QtMaterialAssistChip *q);
    ~QtMaterialAssistChipPrivate();

    void init();

    QtMaterialAssistChip *const q_ptr;
    QString label;
};

#endif // QTMATERIALASSISTCHIP_P_H
