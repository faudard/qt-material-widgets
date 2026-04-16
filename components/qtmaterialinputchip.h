#ifndef QTMATERIALINPUTCHIP_H
#define QTMATERIALINPUTCHIP_H

#include "qtmaterialchip.h"

class QtMaterialInputChipPrivate;

class QtMaterialInputChip : public QtMaterialChip
{
    Q_OBJECT
    Q_PROPERTY(QString label READ label WRITE setLabel)

public:
    explicit QtMaterialInputChip(QWidget *parent = nullptr);
    ~QtMaterialInputChip();

    QString label() const;
    void setLabel(const QString &text);

signals:
    void removeRequested();

protected:
    const QScopedPointer<QtMaterialInputChipPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialInputChip)
    Q_DECLARE_PRIVATE(QtMaterialInputChip)
};

#endif // QTMATERIALINPUTCHIP_H
