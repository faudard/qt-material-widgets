#include "qtmaterialrangeslider.h"
#include "qtmaterialrangeslider_p.h"

#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>

static const int kMargin = 30;
static const int kTrackHeight = 4;
static const int kThumbRadius = 8;
static const int kThumbDiameter = kThumbRadius * 2;
static const int kTickRadius = 2;
static const int kLabelHeight = 24;

enum ThumbHandle {
    NoThumb = -1,
    LowerThumb = 0,
    UpperThumb = 1
};

QtMaterialRangeSliderPrivate::QtMaterialRangeSliderPrivate(QtMaterialRangeSlider *q)
    : q_ptr(q),
      useThemeColors(true),
      stepMode(false),
      showTickMarks(false),
      showValueLabels(false),
      invertedAppearance(false),
      mousePressed(false),
      minimum(0),
      maximum(100),
      lowerValue(25),
      upperValue(75),
      singleStep(1),
      hoveredThumb(NoThumb),
      pressedThumb(NoThumb)
{
}

QtMaterialRangeSliderPrivate::~QtMaterialRangeSliderPrivate()
{
}

void QtMaterialRangeSliderPrivate::init()
{
    Q_Q(QtMaterialRangeSlider);
    q->setMouseTracking(true);
    q->setAttribute(Qt::WA_Hover, true);
    q->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

int QtMaterialRangeSliderPrivate::boundedValue(int value) const
{
    if (minimum > maximum) {
        return value;
    }
    return qBound(minimum, value, maximum);
}

int QtMaterialRangeSliderPrivate::nearestStep(int value) const
{
    if (singleStep <= 1) {
        return boundedValue(value);
    }
    const int offset = value - minimum;
    const int snapped = minimum + qRound(static_cast<qreal>(offset) / singleStep) * singleStep;
    return boundedValue(snapped);
}

int QtMaterialRangeSliderPrivate::pixelFromValue(int value) const
{
    Q_Q(const QtMaterialRangeSlider);
    const int available = qMax(1, q->width() - 2 * kMargin);
    const qreal ratio = (maximum == minimum) ? 0.0 : (static_cast<qreal>(value - minimum) / (maximum - minimum));
    const qreal effective = invertedAppearance ? (1.0 - ratio) : ratio;
    return kMargin + qRound(effective * available);
}

int QtMaterialRangeSliderPrivate::valueFromPixel(int x) const
{
    Q_Q(const QtMaterialRangeSlider);
    const int available = qMax(1, q->width() - 2 * kMargin);
    const int boundedX = qBound(kMargin, x, q->width() - kMargin);
    qreal ratio = static_cast<qreal>(boundedX - kMargin) / available;
    if (invertedAppearance) {
        ratio = 1.0 - ratio;
    }
    int value = minimum + qRound(ratio * (maximum - minimum));
    if (stepMode) {
        value = nearestStep(value);
    }
    return boundedValue(value);
}

int QtMaterialRangeSliderPrivate::effectiveLowerValue() const
{
    return qMin(lowerValue, upperValue);
}

int QtMaterialRangeSliderPrivate::effectiveUpperValue() const
{
    return qMax(lowerValue, upperValue);
}

void QtMaterialRangeSliderPrivate::updateHoveredThumb(int x)
{
    const int lowerX = pixelFromValue(lowerValue);
    const int upperX = pixelFromValue(upperValue);
    const int threshold = kThumbRadius + 4;

    if (qAbs(x - lowerX) <= threshold && qAbs(x - upperX) <= threshold) {
        hoveredThumb = (qAbs(x - lowerX) <= qAbs(x - upperX)) ? LowerThumb : UpperThumb;
    } else if (qAbs(x - lowerX) <= threshold) {
        hoveredThumb = LowerThumb;
    } else if (qAbs(x - upperX) <= threshold) {
        hoveredThumb = UpperThumb;
    } else {
        hoveredThumb = NoThumb;
    }
}

QtMaterialRangeSlider::QtMaterialRangeSlider(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialRangeSliderPrivate(this))
{
    Q_D(QtMaterialRangeSlider);
    d->init();
}

QtMaterialRangeSlider::~QtMaterialRangeSlider()
{
}

void QtMaterialRangeSlider::setUseThemeColors(bool value)
{
    Q_D(QtMaterialRangeSlider);
    if (d->useThemeColors == value) {
        return;
    }
    d->useThemeColors = value;
    update();
}

bool QtMaterialRangeSlider::useThemeColors() const
{
    Q_D(const QtMaterialRangeSlider);
    return d->useThemeColors;
}

void QtMaterialRangeSlider::setThumbColor(const QColor &color)
{
    Q_D(QtMaterialRangeSlider);
    d->thumbColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialRangeSlider::thumbColor() const
{
    Q_D(const QtMaterialRangeSlider);
    return d->thumbColor.isValid() ? d->thumbColor : QColor(33, 150, 243);
}

void QtMaterialRangeSlider::setTrackColor(const QColor &color)
{
    Q_D(QtMaterialRangeSlider);
    d->trackColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialRangeSlider::trackColor() const
{
    Q_D(const QtMaterialRangeSlider);
    return d->trackColor.isValid() ? d->trackColor : QColor(189, 189, 189);
}

void QtMaterialRangeSlider::setFillColor(const QColor &color)
{
    Q_D(QtMaterialRangeSlider);
    d->fillColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialRangeSlider::fillColor() const
{
    Q_D(const QtMaterialRangeSlider);
    return d->fillColor.isValid() ? d->fillColor : thumbColor();
}

void QtMaterialRangeSlider::setDisabledColor(const QColor &color)
{
    Q_D(QtMaterialRangeSlider);
    d->disabledColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialRangeSlider::disabledColor() const
{
    Q_D(const QtMaterialRangeSlider);
    return d->disabledColor.isValid() ? d->disabledColor : QColor(189, 189, 189);
}

void QtMaterialRangeSlider::setRange(int minimum, int maximum)
{
    Q_D(QtMaterialRangeSlider);
    d->minimum = minimum;
    d->maximum = qMax(minimum, maximum);
    setValues(d->lowerValue, d->upperValue);
}

int QtMaterialRangeSlider::minimum() const
{
    Q_D(const QtMaterialRangeSlider);
    return d->minimum;
}

int QtMaterialRangeSlider::maximum() const
{
    Q_D(const QtMaterialRangeSlider);
    return d->maximum;
}

void QtMaterialRangeSlider::setLowerValue(int value)
{
    Q_D(QtMaterialRangeSlider);
    value = d->stepMode ? d->nearestStep(value) : d->boundedValue(value);
    value = qMin(value, d->upperValue);
    if (d->lowerValue == value) {
        return;
    }
    d->lowerValue = value;
    emit lowerValueChanged(value);
    emit rangeChanged(d->lowerValue, d->upperValue);
    update();
}

int QtMaterialRangeSlider::lowerValue() const
{
    Q_D(const QtMaterialRangeSlider);
    return d->lowerValue;
}

void QtMaterialRangeSlider::setUpperValue(int value)
{
    Q_D(QtMaterialRangeSlider);
    value = d->stepMode ? d->nearestStep(value) : d->boundedValue(value);
    value = qMax(value, d->lowerValue);
    if (d->upperValue == value) {
        return;
    }
    d->upperValue = value;
    emit upperValueChanged(value);
    emit rangeChanged(d->lowerValue, d->upperValue);
    update();
}

int QtMaterialRangeSlider::upperValue() const
{
    Q_D(const QtMaterialRangeSlider);
    return d->upperValue;
}

void QtMaterialRangeSlider::setValues(int lower, int upper)
{
    Q_D(QtMaterialRangeSlider);
    lower = d->stepMode ? d->nearestStep(lower) : d->boundedValue(lower);
    upper = d->stepMode ? d->nearestStep(upper) : d->boundedValue(upper);
    if (lower > upper) {
        qSwap(lower, upper);
    }
    const bool lowerChanged = (d->lowerValue != lower);
    const bool upperChanged = (d->upperValue != upper);
    d->lowerValue = lower;
    d->upperValue = upper;
    if (lowerChanged) {
        emit lowerValueChanged(lower);
    }
    if (upperChanged) {
        emit upperValueChanged(upper);
    }
    if (lowerChanged || upperChanged) {
        emit rangeChanged(lower, upper);
        update();
    }
}

void QtMaterialRangeSlider::setSingleStep(int step)
{
    Q_D(QtMaterialRangeSlider);
    d->singleStep = qMax(1, step);
    if (d->stepMode) {
        setValues(d->lowerValue, d->upperValue);
    }
    update();
}

int QtMaterialRangeSlider::singleStep() const
{
    Q_D(const QtMaterialRangeSlider);
    return d->singleStep;
}

void QtMaterialRangeSlider::setStepMode(bool value)
{
    Q_D(QtMaterialRangeSlider);
    if (d->stepMode == value) {
        return;
    }
    d->stepMode = value;
    if (d->stepMode) {
        setValues(d->lowerValue, d->upperValue);
    }
    update();
}

bool QtMaterialRangeSlider::stepMode() const
{
    Q_D(const QtMaterialRangeSlider);
    return d->stepMode;
}

void QtMaterialRangeSlider::setShowTickMarks(bool value)
{
    Q_D(QtMaterialRangeSlider);
    if (d->showTickMarks == value) {
        return;
    }
    d->showTickMarks = value;
    update();
}

bool QtMaterialRangeSlider::showTickMarks() const
{
    Q_D(const QtMaterialRangeSlider);
    return d->showTickMarks;
}

void QtMaterialRangeSlider::setShowValueLabels(bool value)
{
    Q_D(QtMaterialRangeSlider);
    if (d->showValueLabels == value) {
        return;
    }
    d->showValueLabels = value;
    update();
}

bool QtMaterialRangeSlider::showValueLabels() const
{
    Q_D(const QtMaterialRangeSlider);
    return d->showValueLabels;
}

void QtMaterialRangeSlider::setInvertedAppearance(bool value)
{
    Q_D(QtMaterialRangeSlider);
    if (d->invertedAppearance == value) {
        return;
    }
    d->invertedAppearance = value;
    update();
}

bool QtMaterialRangeSlider::invertedAppearance() const
{
    Q_D(const QtMaterialRangeSlider);
    return d->invertedAppearance;
}

QSize QtMaterialRangeSlider::minimumSizeHint() const
{
    return QSize(140, showValueLabels() ? 64 : 40);
}

QSize QtMaterialRangeSlider::sizeHint() const
{
    return minimumSizeHint();
}

bool QtMaterialRangeSlider::event(QEvent *event)
{
    return QWidget::event(event);
}

void QtMaterialRangeSlider::mousePressEvent(QMouseEvent *event)
{
    Q_D(QtMaterialRangeSlider);
    if (!isEnabled() || event->button() != Qt::LeftButton) {
        QWidget::mousePressEvent(event);
        return;
    }

    const int lowerX = d->pixelFromValue(d->lowerValue);
    const int upperX = d->pixelFromValue(d->upperValue);
    if (qAbs(event->x() - lowerX) <= qAbs(event->x() - upperX)) {
        d->pressedThumb = LowerThumb;
    } else {
        d->pressedThumb = UpperThumb;
    }

    d->mousePressed = true;
    emit sliderPressed();
    mouseMoveEvent(event);
    event->accept();
}

void QtMaterialRangeSlider::mouseMoveEvent(QMouseEvent *event)
{
    Q_D(QtMaterialRangeSlider);
    if (!isEnabled()) {
        QWidget::mouseMoveEvent(event);
        return;
    }

    d->updateHoveredThumb(event->x());

    if (d->mousePressed) {
        const int value = d->valueFromPixel(event->x());
        if (d->pressedThumb == LowerThumb) {
            setLowerValue(value);
        } else if (d->pressedThumb == UpperThumb) {
            setUpperValue(value);
        }
    }

    update();
    event->accept();
}

void QtMaterialRangeSlider::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(QtMaterialRangeSlider);
    if (d->mousePressed && event->button() == Qt::LeftButton) {
        d->mousePressed = false;
        d->pressedThumb = NoThumb;
        emit sliderReleased();
        update();
        event->accept();
        return;
    }
    QWidget::mouseReleaseEvent(event);
}

void QtMaterialRangeSlider::leaveEvent(QEvent *event)
{
    Q_D(QtMaterialRangeSlider);
    d->hoveredThumb = NoThumb;
    update();
    QWidget::leaveEvent(event);
}

void QtMaterialRangeSlider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    Q_D(QtMaterialRangeSlider);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const QColor track = isEnabled() ? trackColor() : disabledColor();
    const QColor fill = isEnabled() ? fillColor() : disabledColor();
    const QColor thumb = isEnabled() ? thumbColor() : disabledColor();

    const int y = showValueLabels() ? 38 : height() / 2;
    const QRect trackRect(kMargin, y - kTrackHeight / 2, width() - 2 * kMargin, kTrackHeight);

    painter.setPen(Qt::NoPen);
    painter.setBrush(track);
    painter.drawRoundedRect(trackRect, 2, 2);

    const int lowerX = d->pixelFromValue(d->effectiveLowerValue());
    const int upperX = d->pixelFromValue(d->effectiveUpperValue());
    const QRect fillRect(lowerX, y - kTrackHeight / 2, upperX - lowerX, kTrackHeight);
    painter.setBrush(fill);
    painter.drawRoundedRect(fillRect.normalized(), 2, 2);

    if (showTickMarks() && maximum() > minimum()) {
        const int step = qMax(1, singleStep());
        painter.setBrush(track);
        for (int v = minimum(); v <= maximum(); v += step) {
            const int x = d->pixelFromValue(v);
            painter.drawEllipse(QPointF(x, y), kTickRadius, kTickRadius);
        }
        if (((maximum() - minimum()) % step) != 0) {
            const int x = d->pixelFromValue(maximum());
            painter.drawEllipse(QPointF(x, y), kTickRadius, kTickRadius);
        }
    }

    const int values[2] = { d->lowerValue, d->upperValue };
    const int handles[2] = { lowerX, upperX };
    for (int i = 0; i < 2; ++i) {
        const bool highlighted = (d->hoveredThumb == i) || (d->pressedThumb == i);
        painter.setBrush(thumb);
        painter.drawEllipse(QPointF(handles[i], y), kThumbRadius + (highlighted ? 1 : 0), kThumbRadius + (highlighted ? 1 : 0));

        if (showValueLabels()) {
            const QRect labelRect(handles[i] - 18, 6, 36, kLabelHeight);
            painter.setBrush(fill);
            painter.drawRoundedRect(labelRect, 10, 10);
            painter.setPen(Qt::white);
            painter.drawText(labelRect, Qt::AlignCenter, QString::number(values[i]));
            painter.setPen(Qt::NoPen);
        }
    }
}
