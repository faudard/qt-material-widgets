#ifndef QTMATERIALASSISTCHIP_H
#define QTMATERIALASSISTCHIP_H

#include "qtmaterialchip.h"

class QtMaterialAssistChipPrivate;

class QtMaterialAssistChip : public QtMaterialChip
{
    Q_OBJECT
    Q_PROPERTY(QString label READ label WRITE setLabel)

public:
    explicit QtMaterialAssistChip(QWidget *parent = nullptr);
    ~QtMaterialAssistChip();

    QString label() const;
    void setLabel(const QString &text);

protected:
    const QScopedPointer<QtMaterialAssistChipPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialAssistChip)
    Q_DECLARE_PRIVATE(QtMaterialAssistChip)
};

#endif // QTMATERIALASSISTCHIP_H
