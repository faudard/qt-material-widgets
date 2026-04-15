#include "qtmaterialcarousel.h"
#include "qtmaterialcarousel_p.h"

#include <QPainter>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QStackedLayout>
#include <QWidget>

#include "lib/qtmaterialstyle.h"

QtMaterialCarouselPrivate::QtMaterialCarouselPrivate(QtMaterialCarousel *q)
    : q_ptr(q),
      stack(0),
      useThemeColors(true),
      autoPlay(false),
      autoPlayInterval(3500),
      showIndicators(true),
      wrap(true),
      indicatorDiameter(8),
      indicatorSpacing(12),
      bottomPadding(20)
{
}

QtMaterialCarouselPrivate::~QtMaterialCarouselPrivate()
{
}

void QtMaterialCarouselPrivate::init()
{
    Q_Q(QtMaterialCarousel);

    stack = new QStackedLayout;
    stack->setContentsMargins(0, 0, 0, 32);
    stack->setSpacing(0);

    q->setLayout(stack);
    q->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    q->setAttribute(Qt::WA_Hover);
}

void QtMaterialCarouselPrivate::updateAutoPlay()
{
    Q_Q(QtMaterialCarousel);

    if (autoPlay && stack && stack->count() > 1 && autoPlayInterval > 0) {
        if (!timer.isActive()) {
            timer.start(autoPlayInterval, q);
        }
    } else {
        timer.stop();
    }
}

QRect QtMaterialCarouselPrivate::indicatorRect(int index, const QSize &size) const
{
    const int count = stack ? stack->count() : 0;
    const int totalWidth = count > 0
        ? count * indicatorDiameter + (count - 1) * indicatorSpacing
        : 0;
    const int startX = (size.width() - totalWidth) / 2;
    const int y = size.height() - bottomPadding;
    const int x = startX + index * (indicatorDiameter + indicatorSpacing);
    return QRect(x, y, indicatorDiameter, indicatorDiameter);
}

QtMaterialCarousel::QtMaterialCarousel(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialCarouselPrivate(this))
{
    d_func()->init();
}

QtMaterialCarousel::~QtMaterialCarousel()
{
}

void QtMaterialCarousel::setUseThemeColors(bool value)
{
    Q_D(QtMaterialCarousel);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool QtMaterialCarousel::useThemeColors() const
{
    Q_D(const QtMaterialCarousel);
    return d->useThemeColors;
}

void QtMaterialCarousel::setAutoPlay(bool value)
{
    Q_D(QtMaterialCarousel);
    d->autoPlay = value;
    d->updateAutoPlay();
}

bool QtMaterialCarousel::autoPlay() const
{
    Q_D(const QtMaterialCarousel);
    return d->autoPlay;
}

void QtMaterialCarousel::setAutoPlayInterval(int msec)
{
    Q_D(QtMaterialCarousel);
    d->autoPlayInterval = qMax(0, msec);
    d->updateAutoPlay();
}

int QtMaterialCarousel::autoPlayInterval() const
{
    Q_D(const QtMaterialCarousel);
    return d->autoPlayInterval;
}

void QtMaterialCarousel::setShowIndicators(bool value)
{
    Q_D(QtMaterialCarousel);
    d->showIndicators = value;
    update();
}

bool QtMaterialCarousel::showIndicators() const
{
    Q_D(const QtMaterialCarousel);
    return d->showIndicators;
}

void QtMaterialCarousel::setWrap(bool value)
{
    Q_D(QtMaterialCarousel);
    d->wrap = value;
}

bool QtMaterialCarousel::wrap() const
{
    Q_D(const QtMaterialCarousel);
    return d->wrap;
}

void QtMaterialCarousel::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialCarousel);
    d->backgroundColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialCarousel::backgroundColor() const
{
    Q_D(const QtMaterialCarousel);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("canvas");
    }
    return d->backgroundColor;
}

void QtMaterialCarousel::setIndicatorColor(const QColor &color)
{
    Q_D(QtMaterialCarousel);
    d->indicatorColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialCarousel::indicatorColor() const
{
    Q_D(const QtMaterialCarousel);

    if (d->useThemeColors || !d->indicatorColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("border");
    }
    return d->indicatorColor;
}

void QtMaterialCarousel::setActiveIndicatorColor(const QColor &color)
{
    Q_D(QtMaterialCarousel);
    d->activeIndicatorColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialCarousel::activeIndicatorColor() const
{
    Q_D(const QtMaterialCarousel);

    if (d->useThemeColors || !d->activeIndicatorColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("primary1");
    }
    return d->activeIndicatorColor;
}

void QtMaterialCarousel::addSlide(QWidget *widget)
{
    Q_D(QtMaterialCarousel);

    if (!widget) {
        return;
    }

    d->stack->addWidget(widget);
    d->updateAutoPlay();
    update();
}

int QtMaterialCarousel::count() const
{
    Q_D(const QtMaterialCarousel);
    return d->stack->count();
}

int QtMaterialCarousel::currentIndex() const
{
    Q_D(const QtMaterialCarousel);
    return d->stack->currentIndex();
}

QWidget *QtMaterialCarousel::currentWidget() const
{
    Q_D(const QtMaterialCarousel);
    return d->stack->currentWidget();
}

void QtMaterialCarousel::setCurrentIndex(int index)
{
    Q_D(QtMaterialCarousel);

    if (d->stack->count() == 0) {
        return;
    }

    if (index < 0 || index >= d->stack->count()) {
        return;
    }

    if (d->stack->currentIndex() == index) {
        return;
    }

    d->stack->setCurrentIndex(index);
    update();
    emit currentIndexChanged(index);
}

void QtMaterialCarousel::next()
{
    Q_D(QtMaterialCarousel);

    if (d->stack->count() < 2) {
        return;
    }

    int index = d->stack->currentIndex() + 1;
    if (index >= d->stack->count()) {
        index = d->wrap ? 0 : d->stack->count() - 1;
    }
    setCurrentIndex(index);
}

void QtMaterialCarousel::previous()
{
    Q_D(QtMaterialCarousel);

    if (d->stack->count() < 2) {
        return;
    }

    int index = d->stack->currentIndex() - 1;
    if (index < 0) {
        index = d->wrap ? d->stack->count() - 1 : 0;
    }
    setCurrentIndex(index);
}

void QtMaterialCarousel::paintEvent(QPaintEvent *event)
{
    Q_D(QtMaterialCarousel);
    Q_UNUSED(event)

    QPainter painter(this);
    painter.fillRect(rect(), backgroundColor());

    if (!d->showIndicators || d->stack->count() < 2) {
        return;
    }

    painter.setRenderHint(QPainter::Antialiasing, true);

    for (int i = 0; i < d->stack->count(); ++i) {
        const QRect dot = d->indicatorRect(i, size());
        painter.setBrush(i == d->stack->currentIndex()
                             ? activeIndicatorColor()
                             : indicatorColor());
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(dot);
    }
}

void QtMaterialCarousel::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    update();
}

void QtMaterialCarousel::mousePressEvent(QMouseEvent *event)
{
    Q_D(QtMaterialCarousel);

    if (d->showIndicators && d->stack->count() > 1) {
        for (int i = 0; i < d->stack->count(); ++i) {
            if (d->indicatorRect(i, size()).contains(event->pos())) {
                setCurrentIndex(i);
                return;
            }
        }
    }

    QWidget::mousePressEvent(event);
}

void QtMaterialCarousel::timerEvent(QTimerEvent *event)
{
    Q_D(QtMaterialCarousel);

    if (event->timerId() == d->timer.timerId()) {
        next();
        return;
    }

    QWidget::timerEvent(event);
}
