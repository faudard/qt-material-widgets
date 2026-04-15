#ifndef QTMATERIALDATEFIELD_H
#define QTMATERIALDATEFIELD_H

#include "qtmaterialtextfield.h"
#include <QDate>
#include <QScopedPointer>

class QtMaterialDateFieldPrivate;
class QtMaterialDockedDatePicker;

class QtMaterialDateField : public QtMaterialTextField
{
    Q_OBJECT

    Q_PROPERTY(QString displayFormat WRITE setDisplayFormat READ displayFormat)

public:
    explicit QtMaterialDateField(QWidget *parent = 0);
    ~QtMaterialDateField();

    void setDate(const QDate &date);
    QDate date() const;

    void setDisplayFormat(const QString &format);
    QString displayFormat() const;

    void setMinimumDate(const QDate &date);
    QDate minimumDate() const;

    void setMaximumDate(const QDate &date);
    QDate maximumDate() const;

    QtMaterialDockedDatePicker *picker() const;

signals:
    void dateChanged(const QDate &date);

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    const QScopedPointer<QtMaterialDateFieldPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialDateField)
    Q_DECLARE_PRIVATE(QtMaterialDateField)
};

#endif // QTMATERIALDATEFIELD_H
