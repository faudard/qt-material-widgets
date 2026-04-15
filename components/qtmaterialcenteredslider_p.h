#ifndef QTMATERIALCENTEREDSLIDER_P_H
#define QTMATERIALCENTEREDSLIDER_P_H

#include <QColor>

class QtMaterialCenteredSlider;
class QtMaterialCenteredSliderPrivate
{
    Q_DISABLE_COPY(QtMaterialCenteredSliderPrivate)
    Q_DECLARE_PUBLIC(QtMaterialCenteredSlider)

public:
    explicit QtMaterialCenteredSliderPrivate(QtMaterialCenteredSlider *q);
    ~QtMaterialCenteredSliderPrivate();

    void init();
    int boundedCenterValue() const;
    int clampedValue(int value) const;

    QtMaterialCenteredSlider *const q_ptr;

    int   centerValue;
    bool  showCenterMarker;
    bool  showValueLabel;
    QColor centerColor;
    bool  useThemeColors;
};

#endif  // QTMATERIALCENTEREDSLIDER_P_H
