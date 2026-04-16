#ifndef QTMATERIALSUGGESTIONCHIP_H
#define QTMATERIALSUGGESTIONCHIP_H

#include "qtmaterialchip.h"

class QtMaterialSuggestionChipPrivate;

class QtMaterialSuggestionChip : public QtMaterialChip
{
    Q_OBJECT
    Q_PROPERTY(QString label READ label WRITE setLabel)

public:
    explicit QtMaterialSuggestionChip(QWidget *parent = nullptr);
    ~QtMaterialSuggestionChip();

    QString label() const;
    void setLabel(const QString &text);

protected:
    const QScopedPointer<QtMaterialSuggestionChipPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialSuggestionChip)
    Q_DECLARE_PRIVATE(QtMaterialSuggestionChip)
};

#endif // QTMATERIALSUGGESTIONCHIP_H
