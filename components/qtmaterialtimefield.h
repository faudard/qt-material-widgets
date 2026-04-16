#ifndef QTMATERIALTIMEFIELD_H
#define QTMATERIALTIMEFIELD_H

#include "qtmaterialtextfield.h"
#include <QScopedPointer>
#include <QTime>

class QtMaterialTimeFieldPrivate;

class QtMaterialTimeField : public QtMaterialTextField
{
    Q_OBJECT
    Q_PROPERTY(QTime time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(QString displayFormat READ displayFormat WRITE setDisplayFormat)

public:
    explicit QtMaterialTimeField(QWidget *parent = 0);
    ~QtMaterialTimeField();

    void setTime(const QTime &time);
    QTime time() const;

    void setDisplayFormat(const QString &format);
    QString displayFormat() const;

signals:
    void timeChanged(const QTime &time);
    void pickerRequested();

private:
    Q_DISABLE_COPY(QtMaterialTimeField)
    Q_DECLARE_PRIVATE(QtMaterialTimeField)
    const QScopedPointer<QtMaterialTimeFieldPrivate> d_ptr;
};

#endif // QTMATERIALTIMEFIELD_H
