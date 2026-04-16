#include "qtmaterialappbarstatelayer.h"
#include "qtmaterialappbarstatelayer_p.h"

#include <QPainter>
#include <QPaintEvent>
#include <QColor>

QtMaterialAppBarStateLayerPrivate::QtMaterialAppBarStateLayerPrivate(QtMaterialAppBarStateLayer *q)
    : q_ptr(q),
      useThemeColors(true),
      liftOnScroll(true),
      baseColor(Qt::white),
      scrolledColor(QColor(245, 245, 245)),
      scrollProgress(0.0)
{
}

QtMaterialAppBarStateLayerPrivate::~QtMaterialAppBarStateLayerPrivate()
{
}

void QtMaterialAppBarStateLayerPrivate::init()
{
    Q_Q(QtMaterialAppBarStateLayer);

    q->setAttribute(Qt::WA_TransparentForMouseEvents);
    q->setAutoFillBackground(false);
}

QtMaterialAppBarStateLayer::QtMaterialAppBarStateLayer(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialAppBarStateLayerPrivate(this))
{
    d_func()->init();
}

QtMaterialAppBarStateLayer::~QtMaterialAppBarStateLayer()
{
}

void QtMaterialAppBarStateLayer::setUseThemeColors(bool value)
{
    Q_D(QtMaterialAppBarStateLayer);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool QtMaterialAppBarStateLayer::useThemeColors() const
{
    Q_D(const QtMaterialAppBarStateLayer);
    return d->useThemeColors;
}

void QtMaterialAppBarStateLayer::setBaseColor(const QColor &color)
{
    Q_D(QtMaterialAppBarStateLayer);
    d->baseColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialAppBarStateLayer::baseColor() const
{
    Q_D(const QtMaterialAppBarStateLayer);
    return d->baseColor;
}

void QtMaterialAppBarStateLayer::setScrolledColor(const QColor &color)
{
    Q_D(QtMaterialAppBarStateLayer);
    d->scrolledColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialAppBarStateLayer::scrolledColor() const
{
    Q_D(const QtMaterialAppBarStateLayer);
    return d->scrolledColor;
}

void QtMaterialAppBarStateLayer::setScrollProgress(qreal value)
{
    Q_D(QtMaterialAppBarStateLayer);

    value = qBound<qreal>(0.0, value, 1.0);

    if (qFuzzyCompare(d->scrollProgress, value)) {
        return;
    }

    d->scrollProgress = value;
    update();
}

qreal QtMaterialAppBarStateLayer::scrollProgress() const
{
    Q_D(const QtMaterialAppBarStateLayer);
    return d->scrollProgress;
}

void QtMaterialAppBarStateLayer::setLiftOnScroll(bool value)
{
    Q_D(QtMaterialAppBarStateLayer);

    if (d->liftOnScroll == value) {
        return;
    }

    d->liftOnScroll = value;
    update();
}

bool QtMaterialAppBarStateLayer::liftOnScroll() const
{
    Q_D(const QtMaterialAppBarStateLayer);
    return d->liftOnScroll;
}

void QtMaterialAppBarStateLayer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialAppBarStateLayer);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);

    const QColor from = d->baseColor;
    const QColor to = d->liftOnScroll ? d->scrolledColor : d->baseColor;

    QColor mixed(
        from.red()   + (to.red()   - from.red())   * d->scrollProgress,
        from.green() + (to.green() - from.green()) * d->scrollProgress,
        from.blue()  + (to.blue()  - from.blue())  * d->scrollProgress,
        255);

    painter.fillRect(rect(), mixed);

    if (d->liftOnScroll && d->scrollProgress > 0.0) {
        QColor shadow(0, 0, 0, int(24 * d->scrollProgress));
        painter.fillRect(QRect(0, height() - 1, width(), 1), shadow);
    }
}
