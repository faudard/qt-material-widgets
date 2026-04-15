#include "qtmaterialloadingindicator.h"
#include "qtmaterialloadingindicator_p.h"

#include <QPainter>
#include <QPropertyAnimation>
#include <QtMath>

QtMaterialLoadingIndicatorPrivate::QtMaterialLoadingIndicatorPrivate(QtMaterialLoadingIndicator *q)
    : q_ptr(q),
      useThemeColors(true),
      indeterminate(true),
      autoStart(true),
      running(false),
      lineWidth(4.0),
      size(48),
      dashOffset(0),
      dashOffsetAnimation(0)
{
}

void QtMaterialLoadingIndicatorPrivate::init()
{
    Q_Q(QtMaterialLoadingIndicator);

    dashOffsetAnimation = new QPropertyAnimation(q, "windowOpacity", q);
    dashOffsetAnimation->setStartValue(0);
    dashOffsetAnimation->setEndValue(1);
    dashOffsetAnimation->setDuration(1200);
    dashOffsetAnimation->setLoopCount(-1);

    q->setAttribute(Qt::WA_TransparentForMouseEvents);
    q->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

QtMaterialLoadingIndicator::QtMaterialLoadingIndicator(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialLoadingIndicatorPrivate(this))
{
    d_func()->init();
}

QtMaterialLoadingIndicator::~QtMaterialLoadingIndicator()
{
}

void QtMaterialLoadingIndicator::setUseThemeColors(bool value)
{
    Q_D(QtMaterialLoadingIndicator);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool QtMaterialLoadingIndicator::useThemeColors() const
{
    Q_D(const QtMaterialLoadingIndicator);
    return d->useThemeColors;
}

void QtMaterialLoadingIndicator::setIndicatorColor(const QColor &color)
{
    Q_D(QtMaterialLoadingIndicator);
    d->indicatorColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialLoadingIndicator::indicatorColor() const
{
    Q_D(const QtMaterialLoadingIndicator);
    return d->useThemeColors ? palette().highlight().color() : d->indicatorColor;
}

void QtMaterialLoadingIndicator::setTrackColor(const QColor &color)
{
    Q_D(QtMaterialLoadingIndicator);
    d->trackColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialLoadingIndicator::trackColor() const
{
    Q_D(const QtMaterialLoadingIndicator);
    QColor base = d->useThemeColors ? palette().midlight().color() : d->trackColor;
    if (!base.isValid()) {
        base = palette().midlight().color();
    }
    return base;
}

void QtMaterialLoadingIndicator::setLineWidth(qreal width)
{
    Q_D(QtMaterialLoadingIndicator);
    d->lineWidth = width;
    updateGeometry();
    update();
}

qreal QtMaterialLoadingIndicator::lineWidth() const
{
    Q_D(const QtMaterialLoadingIndicator);
    return d->lineWidth;
}

void QtMaterialLoadingIndicator::setSize(int size)
{
    Q_D(QtMaterialLoadingIndicator);
    d->size = size;
    updateGeometry();
    update();
}

int QtMaterialLoadingIndicator::size() const
{
    Q_D(const QtMaterialLoadingIndicator);
    return d->size;
}

void QtMaterialLoadingIndicator::setIndeterminate(bool value)
{
    Q_D(QtMaterialLoadingIndicator);
    d->indeterminate = value;
    update();
}

bool QtMaterialLoadingIndicator::isIndeterminate() const
{
    Q_D(const QtMaterialLoadingIndicator);
    return d->indeterminate;
}

void QtMaterialLoadingIndicator::setAutoStart(bool value)
{
    Q_D(QtMaterialLoadingIndicator);
    d->autoStart = value;
}

bool QtMaterialLoadingIndicator::autoStart() const
{
    Q_D(const QtMaterialLoadingIndicator);
    return d->autoStart;
}

void QtMaterialLoadingIndicator::start()
{
    Q_D(QtMaterialLoadingIndicator);
    d->running = true;
    if (d->dashOffsetAnimation) {
        d->dashOffsetAnimation->start();
    }
    update();
}

void QtMaterialLoadingIndicator::stop()
{
    Q_D(QtMaterialLoadingIndicator);
    d->running = false;
    if (d->dashOffsetAnimation) {
        d->dashOffsetAnimation->stop();
    }
    update();
}

void QtMaterialLoadingIndicator::paintEvent(QPaintEvent *)
{
    Q_D(QtMaterialLoadingIndicator);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const QRectF r = rect().adjusted(d->lineWidth, d->lineWidth, -d->lineWidth, -d->lineWidth);

    QPen trackPen(trackColor(), d->lineWidth, Qt::SolidLine, Qt::RoundCap);
    painter.setPen(trackPen);
    painter.drawArc(r, 0, 360 * 16);

    QPen arcPen(indicatorColor(), d->lineWidth, Qt::SolidLine, Qt::RoundCap);
    painter.setPen(arcPen);

    const int startAngle = d->running ? 40 * 16 : 90 * 16;
    const int spanAngle = d->indeterminate ? -110 * 16 : -270 * 16;
    painter.drawArc(r, startAngle, spanAngle);
}

void QtMaterialLoadingIndicator::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    Q_D(QtMaterialLoadingIndicator);
    if (d->autoStart && !d->running) {
        start();
    }
}

QSize QtMaterialLoadingIndicator::sizeHint() const
{
    Q_D(const QtMaterialLoadingIndicator);
    return QSize(d->size, d->size);
}
