#include "qtmaterialskeleton.h"
#include "qtmaterialskeleton_p.h"
#include "lib/qtmaterialstyle.h"

#include <QColor>
#include <QLinearGradient>
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>
#include <QSizePolicy>
#include <QTimerEvent>

QtMaterialSkeletonPrivate::QtMaterialSkeletonPrivate(QtMaterialSkeleton *q)
    : q_ptr(q),
      useThemeColors(true),
      backgroundColor(0),
      highlightColor(0),
      animationEnabled(true),
      cornerRadius(4),
      lineCount(3),
      circular(false),
      displayMode(QtMaterialSkeleton::SingleBlock),
      shimmerOffset(0),
      timerId(-1)
{
}

QtMaterialSkeletonPrivate::~QtMaterialSkeletonPrivate()
{
    delete backgroundColor;
    delete highlightColor;
}

void QtMaterialSkeletonPrivate::init()
{
    Q_Q(QtMaterialSkeleton);

    q->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    q->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    if (animationEnabled) {
        timerId = q->startTimer(30);
    }
}

QtMaterialSkeleton::QtMaterialSkeleton(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialSkeletonPrivate(this))
{
    d_func()->init();
}

QtMaterialSkeleton::~QtMaterialSkeleton()
{
}

QSize QtMaterialSkeleton::sizeHint() const
{
    Q_D(const QtMaterialSkeleton);
    if (d->circular) {
        return QSize(40, 40);
    }
    return d->displayMode == TextLines ? QSize(240, 56 + (d->lineCount - 1) * 16) : QSize(240, 24);
}

QSize QtMaterialSkeleton::minimumSizeHint() const
{
    Q_D(const QtMaterialSkeleton);
    if (d->circular) {
        return QSize(24, 24);
    }
    return d->displayMode == TextLines ? QSize(120, 40) : QSize(80, 16);
}

void QtMaterialSkeleton::setUseThemeColors(bool value)
{
    Q_D(QtMaterialSkeleton);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool QtMaterialSkeleton::useThemeColors() const
{
    Q_D(const QtMaterialSkeleton);
    return d->useThemeColors;
}

void QtMaterialSkeleton::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialSkeleton);

    if (!d->backgroundColor) {
        d->backgroundColor = new QColor(color);
    } else if (*d->backgroundColor == color) {
        return;
    } else {
        *d->backgroundColor = color;
    }

    d->useThemeColors = false;
    update();
}

QColor QtMaterialSkeleton::backgroundColor() const
{
    Q_D(const QtMaterialSkeleton);

    if (d->useThemeColors || !d->backgroundColor) {
        QColor surface = QtMaterialStyle::instance().themeColor("canvas");
        return surface.darker(106);
    }
    return *d->backgroundColor;
}

void QtMaterialSkeleton::setHighlightColor(const QColor &color)
{
    Q_D(QtMaterialSkeleton);

    if (!d->highlightColor) {
        d->highlightColor = new QColor(color);
    } else if (*d->highlightColor == color) {
        return;
    } else {
        *d->highlightColor = color;
    }

    d->useThemeColors = false;
    update();
}

QColor QtMaterialSkeleton::highlightColor() const
{
    Q_D(const QtMaterialSkeleton);

    if (d->useThemeColors || !d->highlightColor) {
        return backgroundColor().lighter(116);
    }
    return *d->highlightColor;
}

void QtMaterialSkeleton::setAnimationEnabled(bool value)
{
    Q_D(QtMaterialSkeleton);

    if (d->animationEnabled == value) {
        return;
    }

    d->animationEnabled = value;

    if (d->timerId != -1) {
        killTimer(d->timerId);
        d->timerId = -1;
    }

    if (d->animationEnabled) {
        d->timerId = startTimer(30);
    }

    update();
}

bool QtMaterialSkeleton::animationEnabled() const
{
    Q_D(const QtMaterialSkeleton);
    return d->animationEnabled;
}

void QtMaterialSkeleton::setCornerRadius(int value)
{
    Q_D(QtMaterialSkeleton);

    value = qMax(0, value);
    if (d->cornerRadius == value) {
        return;
    }

    d->cornerRadius = value;
    update();
}

int QtMaterialSkeleton::cornerRadius() const
{
    Q_D(const QtMaterialSkeleton);
    return d->cornerRadius;
}

void QtMaterialSkeleton::setLineCount(int value)
{
    Q_D(QtMaterialSkeleton);

    value = qMax(1, value);
    if (d->lineCount == value) {
        return;
    }

    d->lineCount = value;
    updateGeometry();
    update();
}

int QtMaterialSkeleton::lineCount() const
{
    Q_D(const QtMaterialSkeleton);
    return d->lineCount;
}

void QtMaterialSkeleton::setCircular(bool value)
{
    Q_D(QtMaterialSkeleton);

    if (d->circular == value) {
        return;
    }

    d->circular = value;
    updateGeometry();
    update();
}

bool QtMaterialSkeleton::isCircular() const
{
    Q_D(const QtMaterialSkeleton);
    return d->circular;
}

void QtMaterialSkeleton::setDisplayMode(DisplayMode mode)
{
    Q_D(QtMaterialSkeleton);

    if (d->displayMode == mode) {
        return;
    }

    d->displayMode = mode;
    updateGeometry();
    update();
}

QtMaterialSkeleton::DisplayMode QtMaterialSkeleton::displayMode() const
{
    Q_D(const QtMaterialSkeleton);
    return d->displayMode;
}

void QtMaterialSkeleton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialSkeleton);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QLinearGradient gradient(0, 0, width(), 0);
    if (d->animationEnabled) {
        const qreal start = qBound(0.0, (qreal)d->shimmerOffset / qMax(1, width()), 1.0);
        gradient.setColorAt(qMax(0.0, start - 0.20), backgroundColor());
        gradient.setColorAt(start, highlightColor());
        gradient.setColorAt(qMin(1.0, start + 0.20), backgroundColor());
    } else {
        gradient.setColorAt(0.0, backgroundColor());
        gradient.setColorAt(1.0, backgroundColor());
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(gradient);

    if (d->circular) {
        painter.drawEllipse(rect().adjusted(1, 1, -1, -1));
        return;
    }

    if (d->displayMode == SingleBlock) {
        painter.drawRoundedRect(rect().adjusted(0, 0, -1, -1), d->cornerRadius, d->cornerRadius);
        return;
    }

    const int left = 0;
    const int lineHeight = 12;
    const int spacing = 10;
    int top = 0;

    for (int i = 0; i < d->lineCount; ++i) {
        int lineWidth = width();
        if (i == d->lineCount - 1 && d->lineCount > 1) {
            lineWidth = width() * 0.68;
        }
        QRect lineRect(left, top, lineWidth - 1, lineHeight);
        painter.drawRoundedRect(lineRect, d->cornerRadius, d->cornerRadius);
        top += lineHeight + spacing;
    }
}

void QtMaterialSkeleton::timerEvent(QTimerEvent *event)
{
    Q_D(QtMaterialSkeleton);

    if (event->timerId() != d->timerId) {
        QWidget::timerEvent(event);
        return;
    }

    d->shimmerOffset += 12;
    if (d->shimmerOffset > width() + 80) {
        d->shimmerOffset = -80;
    }
    update();
}
