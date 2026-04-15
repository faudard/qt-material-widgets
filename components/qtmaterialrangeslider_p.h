#ifndef QTMATERIALRANGESLIDER_P_H
#define QTMATERIALRANGESLIDER_P_H

#include <QColor>
#include <QtGlobal>

class QtMaterialRangeSlider;

class QtMaterialRangeSliderPrivate
{
    Q_DISABLE_COPY(QtMaterialRangeSliderPrivate)
    Q_DECLARE_PUBLIC(QtMaterialRangeSlider)

public:
    QtMaterialRangeSliderPrivate(QtMaterialRangeSlider *q);
    ~QtMaterialRangeSliderPrivate();

    void init();
    int boundedValue(int value) const;
    int nearestStep(int value) const;
    int pixelFromValue(int value) const;
    int valueFromPixel(int x) const;
    int effectiveLowerValue() const;
    int effectiveUpperValue() const;
    void updateHoveredThumb(int x);

    QtMaterialRangeSlider *const q_ptr;

    bool useThemeColors;
    bool stepMode;
    bool showTickMarks;
    bool showValueLabels;
    bool invertedAppearance;
    bool mousePressed;

    int minimum;
    int maximum;
    int lowerValue;
    int upperValue;
    int singleStep;
    int hoveredThumb;
    int pressedThumb;

    QColor thumbColor;
    QColor trackColor;
    QColor fillColor;
    QColor disabledColor;
};

#endif // QTMATERIALRANGESLIDER_P_H
