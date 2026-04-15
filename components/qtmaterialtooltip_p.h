#ifndef QTMATERIALTOOLTIP_P_H
#define QTMATERIALTOOLTIP_P_H

#include <QColor>
#include <QPointer>
#include <QString>
#include <QBasicTimer>

class QWidget;
class QtMaterialTooltip;

class QtMaterialTooltipPrivate
{
    Q_DISABLE_COPY(QtMaterialTooltipPrivate)
    Q_DECLARE_PUBLIC(QtMaterialTooltip)

public:
    explicit QtMaterialTooltipPrivate(QtMaterialTooltip *q);
    void init();
    QRect tooltipRect() const;

    QtMaterialTooltip *const q_ptr;
    QPointer<QWidget> target;
    QString text;
    QColor backgroundColor;
    QColor textColor;
    qreal fontSize;
    int padding;
    int autoHideDuration;
    bool useThemeColors;
    bool visible;
    QBasicTimer hideTimer;
};

#endif // QTMATERIALTOOLTIP_P_H
