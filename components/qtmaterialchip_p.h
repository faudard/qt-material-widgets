#ifndef QTMATERIALCHIP_P_H
#define QTMATERIALCHIP_P_H

#include <QColor>
#include <QIcon>
#include <QRect>

class QtMaterialChip;

class QtMaterialChipPrivate
{
    Q_DISABLE_COPY(QtMaterialChipPrivate)
    Q_DECLARE_PUBLIC(QtMaterialChip)

public:
    explicit QtMaterialChipPrivate(QtMaterialChip *q);
    ~QtMaterialChipPrivate();

    void init();

    bool hasLeadingVisual() const;
    bool hasTrailingVisual() const;
    QRect leadingIconRect() const;
    QRect trailingIconRect() const;
    QRect trailingHitRect() const;

    QColor resolvedBackgroundColor() const;
    QColor resolvedForegroundColor() const;
    QColor resolvedOutlineColor() const;

    QtMaterialChip *const q_ptr;
    bool useThemeColors;
    bool showLeadingIcon;
    bool showTrailingIcon;
    bool closable;
    bool hovered;
    bool closeHovered;
    bool closePressed;
    QColor textColor;
    QColor backgroundColor;
    QColor selectedColor;
    QColor disabledColor;
    QIcon leadingIcon;
    QIcon trailingIcon;
};

#endif // QTMATERIALCHIP_P_H
