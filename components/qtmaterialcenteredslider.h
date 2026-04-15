#ifndef QTMATERIALCENTEREDSLIDER_H
#define QTMATERIALCENTEREDSLIDER_H

#include <QColor>
#include <QScopedPointer>

#include "qtmaterialslider.h"

class QtMaterialCenteredSliderPrivate;

class QtMaterialCenteredSlider : public QtMaterialSlider
{
    Q_OBJECT

    Q_PROPERTY(int centerValue WRITE setCenterValue READ centerValue)
    Q_PROPERTY(bool showCenterMarker WRITE setShowCenterMarker READ showCenterMarker)
    Q_PROPERTY(bool showValueLabel WRITE setShowValueLabel READ showValueLabel)
    Q_PROPERTY(QColor centerColor WRITE setCenterColor READ centerColor)

public:
    explicit QtMaterialCenteredSlider(QWidget *parent = 0);
    ~QtMaterialCenteredSlider();

    void setCenterValue(int value);
    int centerValue() const;

    void setShowCenterMarker(bool value);
    bool showCenterMarker() const;

    void setShowValueLabel(bool value);
    bool showValueLabel() const;

    void setCenterColor(const QColor &color);
    QColor centerColor() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void sliderChange(SliderChange change) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialCenteredSliderPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialCenteredSlider)
    Q_DECLARE_PRIVATE(QtMaterialCenteredSlider)
};

#endif  // QTMATERIALCENTEREDSLIDER_H
