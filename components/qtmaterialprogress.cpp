#include "qtmaterialprogress.h"
#include "qtmaterialprogress_p.h"

#include <QPainter>
#include <QPropertyAnimation>
#include <QtMath>

#include "qtmaterialprogress_internal.h"
#include "lib/qtmaterialstyle.h"

QtMaterialProgressPrivate::QtMaterialProgressPrivate(QtMaterialProgress *q)
    : q_ptr(q)
{
}

QtMaterialProgressPrivate::~QtMaterialProgressPrivate()
{
}

void QtMaterialProgressPrivate::init()
{
    Q_Q(QtMaterialProgress);

    delegate = new QtMaterialProgressDelegate(q);
    progressType = Material::IndeterminateProgress;
    useThemeColors = true;
    trackThickness = 6;
    roundedCaps = true;
    showPercentage = false;

    QPropertyAnimation *animation = new QPropertyAnimation(q);
    animation->setPropertyName("offset");
    animation->setTargetObject(delegate);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setDuration(1000);
    animation->setLoopCount(-1);
    animation->start();

    q->setTextVisible(false);
}

QtMaterialProgress::QtMaterialProgress(QWidget *parent)
    : QProgressBar(parent), d_ptr(new QtMaterialProgressPrivate(this))
{
    d_func()->init();
}

QtMaterialProgress::~QtMaterialProgress()
{
}

void QtMaterialProgress::setProgressType(Material::ProgressType type)
{
    Q_D(QtMaterialProgress);
    d->progressType = type;
    update();
}

Material::ProgressType QtMaterialProgress::progressType() const
{
    Q_D(const QtMaterialProgress);
    return d->progressType;
}

void QtMaterialProgress::setUseThemeColors(bool state)
{
    Q_D(QtMaterialProgress);

    if (d->useThemeColors == state) {
        return;
    }

    d->useThemeColors = state;
    update();
}

bool QtMaterialProgress::useThemeColors() const
{
    Q_D(const QtMaterialProgress);
    return d->useThemeColors;
}

void QtMaterialProgress::setProgressColor(const QColor &color)
{
    Q_D(QtMaterialProgress);
    d->progressColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialProgress::progressColor() const
{
    Q_D(const QtMaterialProgress);

    if (d->useThemeColors || !d->progressColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("primary1");
    }

    return d->progressColor;
}

void QtMaterialProgress::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialProgress);
    d->backgroundColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialProgress::backgroundColor() const
{
    Q_D(const QtMaterialProgress);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("border");
    }

    return d->backgroundColor;
}

void QtMaterialProgress::setTextColor(const QColor &color)
{
    Q_D(QtMaterialProgress);
    d->textColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialProgress::textColor() const
{
    Q_D(const QtMaterialProgress);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("text");
    }

    return d->textColor;
}

void QtMaterialProgress::setTrackThickness(qreal value)
{
    Q_D(QtMaterialProgress);
    d->trackThickness = qMax<qreal>(2, value);
    updateGeometry();
    update();
}

qreal QtMaterialProgress::trackThickness() const
{
    Q_D(const QtMaterialProgress);
    return d->trackThickness;
}

void QtMaterialProgress::setRoundedCaps(bool value)
{
    Q_D(QtMaterialProgress);
    d->roundedCaps = value;
    update();
}

bool QtMaterialProgress::hasRoundedCaps() const
{
    Q_D(const QtMaterialProgress);
    return d->roundedCaps;
}

void QtMaterialProgress::setShowPercentage(bool value)
{
    Q_D(QtMaterialProgress);
    d->showPercentage = value;
    update();
}

bool QtMaterialProgress::showPercentage() const
{
    Q_D(const QtMaterialProgress);
    return d->showPercentage;
}

void QtMaterialProgress::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialProgress);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const qreal thickness = qMin<qreal>(height() - (d->showPercentage ? 18 : 0), d->trackThickness);
    const QRectF trackRect(0,
                           d->showPercentage ? 14 : (height() - thickness) / 2.0,
                           width(),
                           thickness);

    const qreal radius = d->roundedCaps ? thickness / 2.0 : 0;

    painter.setPen(Qt::NoPen);
    painter.setBrush(isEnabled() ? backgroundColor()
                                 : QtMaterialStyle::instance().themeColor("disabled"));
    painter.drawRoundedRect(trackRect, radius, radius);

    if (isEnabled()) {
        painter.setBrush(progressColor());

        if (Material::IndeterminateProgress == d->progressType) {
            const qreal movingWidth = width() * 0.5;
            const qreal x = d->delegate->offset() * (width() + movingWidth) - movingWidth;
            const QRectF progressRect(x, trackRect.y(), movingWidth, thickness);
            painter.drawRoundedRect(progressRect, radius, radius);
        } else {
            const qreal range = maximum() - minimum();
            const qreal p = (range <= 0)
                ? 0
                : (width() * (value() - minimum()) / range);
            const QRectF progressRect(0, trackRect.y(), p, thickness);
            painter.drawRoundedRect(progressRect, radius, radius);
        }
    }

    if (d->showPercentage && Material::DeterminateProgress == d->progressType) {
        painter.setPen(textColor());
        const qreal range = maximum() - minimum();
        const int percentage = (range <= 0)
            ? 0
            : qRound(100.0 * (value() - minimum()) / range);
        painter.drawText(QRect(0, 0, width(), 14), Qt::AlignRight | Qt::AlignVCenter,
                         QString::number(percentage) + QLatin1Char('%'));
    }
}
