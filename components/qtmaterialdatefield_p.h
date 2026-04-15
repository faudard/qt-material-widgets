#ifndef QTMATERIALDATEFIELD_P_H
#define QTMATERIALDATEFIELD_P_H

#include <QDate>
#include <QString>

class QtMaterialDockedDatePicker;

class QtMaterialDateFieldPrivate
{
    Q_DISABLE_COPY(QtMaterialDateFieldPrivate)

public:
    QtMaterialDateFieldPrivate();

    QDate date;
    QDate minimumDate;
    QDate maximumDate;
    QString displayFormat;
    QtMaterialDockedDatePicker *picker;
};

#endif // QTMATERIALDATEFIELD_P_H
