#ifndef QTMATERIALTIMEFIELD_P_H
#define QTMATERIALTIMEFIELD_P_H

#include <QTime>
#include <QString>

class QtMaterialTimeField;

class QtMaterialTimeFieldPrivate
{
public:
    QtMaterialTimeFieldPrivate(QtMaterialTimeField *q);

    QtMaterialTimeField *const q_ptr;
    QTime time;
    QString displayFormat;
};

#endif // QTMATERIALTIMEFIELD_P_H
