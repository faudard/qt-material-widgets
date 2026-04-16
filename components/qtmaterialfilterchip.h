#ifndef QTMATERIALFILTERCHIP_H
#define QTMATERIALFILTERCHIP_H

#include "qtmaterialchip.h"

class QtMaterialFilterChipPrivate;

class QtMaterialFilterChip : public QtMaterialChip
{
    Q_OBJECT
    Q_PROPERTY(QString label READ label WRITE setLabel)

public:
    explicit QtMaterialFilterChip(QWidget *parent = nullptr);
    ~QtMaterialFilterChip();

    QString label() const;
    void setLabel(const QString &text);

protected:
    const QScopedPointer<QtMaterialFilterChipPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialFilterChip)
    Q_DECLARE_PRIVATE(QtMaterialFilterChip)
};

#endif // QTMATERIALFILTERCHIP_H
