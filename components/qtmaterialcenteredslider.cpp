#include "qtmaterialcenteredslider.h"
#include "qtmaterialcenteredslider_p.h"

#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QStyleOptionSlider>
#include <QToolTip>

#include "lib/qtmaterialstyle.h"

QtMaterialCenteredSliderPrivate::QtMaterialCenteredSliderPrivate(QtMaterialCenteredSlider *q)
    : q_ptr(q),
      centerValue(0),
      showCenterMarker(true),
      showValueLabel(false),
      centerColor(),
      useThemeColors(true)
{
}

QtMaterialCenteredSliderPrivate::~QtMaterialCenteredSliderPrivate()
{
}

void QtMaterialCenteredSliderPrivate::init()
{
    Q_Q(QtMaterialCenteredSlider);

    q->setPageStepMode(false);
    q->setTracking(true);
}

int QtMaterialCenteredSliderPrivate::boundedCenterValue() const
{
    return clampedValue(centerValue);
}

int QtMaterialCenteredSliderPrivate::clampedValue(int value) const
{
    Q_Q(const QtMaterialCenteredSlider);

    if (q->minimum() > q->maximum()) {
        return value;
    }
    return qBound(q->minimum(), value, q->maximum());
}

QtMaterialCenteredSlider::QtMaterialCenteredSlider(QWidget *parent)
    : QtMaterialSlider(parent),
      d_ptr(new QtMaterialCenteredSliderPrivate(this))
{
    Q_D(QtMaterialCenteredSlider);
    d->init();
}

QtMaterialCenteredSlider::~QtMaterialCenteredSlider()
{
}

void QtMaterialCenteredSlider::setCenterValue(int value)
{
    Q_D(QtMaterialCenteredSlider);
    value = d->clampedValue(value);
    if (d->centerValue == value) {
        return;
    }
    d->centerValue = value;
    update();
}

int QtMaterialCenteredSlider::centerValue() const
{
    Q_D(const QtMaterialCenteredSlider);
    return d->centerValue;
}

void QtMaterialCenteredSlider::setShowCenterMarker(bool value)
{
    Q_D(QtMaterialCenteredSlider);
    if (d->showCenterMarker == value) {
        return;
    }
    d->showCenterMarker = value;
    update();
}

bool QtMaterialCenteredSlider::showCenterMarker() const
{
    Q_D(const QtMaterialCenteredSlider);
    return d->showCenterMarker;
}

void QtMaterialCenteredSlider::setShowValueLabel(bool value)
{
    Q_D(QtMaterialCenteredSlider);
    d->showValueLabel = value;
}

bool QtMaterialCenteredSlider::showValueLabel() const
{
    Q_D(const QtMaterialCenteredSlider);
    return d->showValueLabel;
}

void QtMaterialCenteredSlider::setCenterColor(const QColor &color)
{
    Q_D(QtMaterialCenteredSlider);
    d->centerColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialCenteredSlider::centerColor() const
{
    Q_D(const QtMaterialCenteredSlider);

    if (d->useThemeColors || !d->centerColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("accent1");
    }
    return d->centerColor;
}

void QtMaterialCenteredSlider::paintEvent(QPaintEvent *event)
{
    QtMaterialSlider::paintEvent(event);

    Q_D(QtMaterialCenteredSlider);
    if (!d->showCenterMarker) {
        return;
    }

    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int available = (orientation() == Qt::Horizontal ? width() : height()) - 2 * QT_MATERIAL_SLIDER_MARGIN;
    if (available <= 0 || minimum() == maximum()) {
        return;
    }

    const qreal fraction = qreal(d->boundedCenterValue() - minimum()) / qMax(1, maximum() - minimum());
    const int pos = QT_MATERIAL_SLIDER_MARGIN + qRound(fraction * available);

    QPen pen(centerColor());
    pen.setWidthF(2.0);
    painter.setPen(pen);

    if (orientation() == Qt::Horizontal) {
        painter.drawLine(QPointF(pos, height() / 2.0 - 10), QPointF(pos, height() / 2.0 + 10));
    } else {
        painter.drawLine(QPointF(width() / 2.0 - 10, pos), QPointF(width() / 2.0 + 10, pos));
    }
}

void QtMaterialCenteredSlider::sliderChange(SliderChange change)
{
    QtMaterialSlider::sliderChange(change);

    if (change == SliderValueChange || change == SliderRangeChange) {
        Q_D(QtMaterialCenteredSlider);
        d->centerValue = d->clampedValue(d->centerValue);
        update();
    }
}

void QtMaterialCenteredSlider::mouseReleaseEvent(QMouseEvent *event)
{
    QtMaterialSlider::mouseReleaseEvent(event);

    Q_D(QtMaterialCenteredSlider);
    if (d->showValueLabel) {
        const QString text = QString::number(value() - d->boundedCenterValue());
        QToolTip::showText(mapToGlobal(event->pos()), text, this);
    }
}
