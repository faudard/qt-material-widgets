#ifndef QTMATERIALRICHTOOLTIP_P_H
#define QTMATERIALRICHTOOLTIP_P_H

#include "qtmaterialtooltip_p.h"
#include <QColor>
#include <QIcon>
#include <QRect>

class QtMaterialRichTooltip;

class QtMaterialRichTooltipPrivate : public QtMaterialTooltipPrivate
{
    Q_DISABLE_COPY(QtMaterialRichTooltipPrivate)
    Q_DECLARE_PUBLIC(QtMaterialRichTooltip)

public:
    explicit QtMaterialRichTooltipPrivate(QtMaterialRichTooltip *q);
    ~QtMaterialRichTooltipPrivate();

    void init();

    QString title;
    QString supportingText;
    QString primaryActionText;
    QString secondaryActionText;
    QIcon icon;
    bool showIcon;
    int maximumTextWidth;

    QColor surfaceColor;
    QColor titleColor;
    QColor supportingTextColor;
    QColor actionColor;

    QRect primaryActionRect;
    QRect secondaryActionRect;

    QtMaterialRichTooltip *const q_ptr;
};

#endif  // QTMATERIALRICHTOOLTIP_P_H
