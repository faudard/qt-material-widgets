#ifndef QTMATERIALTABLE_P_H
#define QTMATERIALTABLE_P_H

#include <QColor>

class QtMaterialTable;

class QtMaterialTablePrivate
{
    Q_DISABLE_COPY(QtMaterialTablePrivate)
    Q_DECLARE_PUBLIC(QtMaterialTable)

public:
    QtMaterialTablePrivate(QtMaterialTable *q);
    ~QtMaterialTablePrivate();

    void init();
    void setupMetrics();

    QtMaterialTable *const q_ptr;
    bool useThemeColors;
    bool dense;
    QColor headerColor;
    QColor textColor;
    QColor backgroundColor;
    QColor alternateBackgroundColor;
    QColor gridColor;
    QColor selectedRowColor;
    QColor hoverRowColor;
};

#endif // QTMATERIALTABLE_P_H
