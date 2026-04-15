#ifndef QTMATERIALSUBHEADER_P_H
#define QTMATERIALSUBHEADER_P_H

#include "qtmaterialsubheader.h"

class QColor;

class QtMaterialSubheaderPrivate
{
    Q_DISABLE_COPY(QtMaterialSubheaderPrivate)
    Q_DECLARE_PUBLIC(QtMaterialSubheader)

public:
    explicit QtMaterialSubheaderPrivate(QtMaterialSubheader *q);
    ~QtMaterialSubheaderPrivate();

    void init();

    QtMaterialSubheader *const q_ptr;
    bool useThemeColors;
    QString text;
    QColor *textColor;
    int inset;
    bool divider;
    bool dense;
    Qt::Alignment alignment;
};

#endif // QTMATERIALSUBHEADER_P_H
