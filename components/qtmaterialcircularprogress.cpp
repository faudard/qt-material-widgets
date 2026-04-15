#include "qtmaterialcircularprogress.h"
#include "qtmaterialcircularprogress_p.h"

#include <QPainter>
#include <QPropertyAnimation>
#include <QtMath>

#include "qtmaterialcircularprogress_internal.h"
#include "lib/qtmaterialstyle.h"

QtMaterialCircularProgressPrivate::QtMaterialCircularProgressPrivate(QtMaterialCircularProgress *q)
    : q_ptr(q)
{
}

QtMaterialCircularProgressPrivate::~QtMaterialCircularProgressPrivate()
{
}

void QtMaterialCircularProgressPrivate::init()
{
    Q_Q(QtMaterialCircularProgress);

    delegate = new QtMaterialCircularProgressDelegate(q);
    progressType = Material::IndeterminateProgress;
    useThemeColors = true;
    lineWidth = 6;
    size = 64;
    showPercentage = false;
    roundedCaps = true;

    QPropertyAnimation *animation = new QPropertyAnimation(q);
    animation->setPropertyName("dashOffset");
    animation->setTargetObject(delegate);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setDuration(1200);
    animation->setLoopCount(-1);
    animation->start();
}

QtMaterialCircularProgress::QtMaterialCircularProgress(QWidget *parent)
    : QProgressBar(parent), d_ptr(new QtMaterialCircularProgressPrivate(this))
{
    d_func()->init();
}

QtMaterialCircularProgress::~QtMaterialCircularProgress()
{
}

void QtMaterialCircularProgress::setProgressType(Material::ProgressType type)
{
    Q_D(QtMaterialCircularProgress);
    d->progressType = type;
    update();
}

Material::ProgressType QtMaterialCircularProgress::progressType() const
{
    Q_D(const QtMaterialCircularProgress);
    return d->progressType;
}

void QtMaterialCircularProgress::setUseThemeColors(bool value)
{
    Q_D(QtMaterialCircularProgress);
    if (d->useThemeColors == value) {
        return;
    }
    d->useThemeColors = value;
    update();
}

bool QtMaterialCircularProgress::useThemeColors() const
{
    Q_D(const QtMaterialCircularProgress);
    return d->useThemeColors;
}

void QtMaterialCircularProgress::setLineWidth(qreal width)
{
    Q_D(QtMaterialCircularProgress);
    d->lineWidth = qMax<qreal>(1.5, width);
    updateGeometry();
    update();
}

qreal QtMaterialCircularProgress::lineWidth() const
{
    Q_D(const QtMaterialCircularProgress);
    return d->lineWidth;
}

void QtMaterialCircularProgress::setSize(int size)
{
    Q_D(QtMaterialCircularProgress);
    d->size = qMax(16, size);
    updateGeometry();
    update();
}

int QtMaterialCircularProgress::size() const
{
    Q_D(const QtMaterialCircularProgress);
    return d->size;
}

void QtMaterialCircularProgress::setColor(const QColor &color)
{
    Q_D(QtMaterialCircularProgress);
    d->color = color;
    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialCircularProgress::color() const
{
    Q_D(const QtMaterialCircularProgress);
    if (d->useThemeColors || !d->color.isValid()) {
        return QtMaterialStyle::instance().themeColor("primary1");
    }
    return d->color;
}

void QtMaterialCircularProgress::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialCircularProgress);
    d->backgroundColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialCircularProgress::backgroundColor() const
{
    Q_D(const QtMaterialCircularProgress);
    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("border");
    }
    return d->backgroundColor;
}

void QtMaterialCircularProgress::setShowPercentage(bool value)
{
    Q_D(QtMaterialCircularProgress);
    d->showPercentage = value;
    update();
}

bool QtMaterialCircularProgress::showPercentage() const
{
    Q_D(const QtMaterialCircularProgress);
    return d->showPercentage;
}

void QtMaterialCircularProgress::setRoundedCaps(bool value)
{
    Q_D(QtMaterialCircularProgress);
    d->roundedCaps = value;
    update();
}

bool QtMaterialCircularProgress::hasRoundedCaps() const
{
    Q_D(const QtMaterialCircularProgress);
    return d->roundedCaps;
}

QSize QtMaterialCircularProgress::sizeHint() const
{
    Q_D(const QtMaterialCircularProgress);
    const int padding = d->showPercentage ? 8 : 2;
    return QSize(d->size + padding, d->size + padding);
}

void QtMaterialCircularProgress::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    Q_D(QtMaterialCircularProgress);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const QRectF arcRect((width() - d->size) / 2.0,
                         (height() - d->size) / 2.0,
                         d->size,
                         d->size);

    QPen pen;
    pen.setWidthF(d->lineWidth);
    pen.setCapStyle(d->roundedCaps ? Qt::RoundCap : Qt::FlatCap);

    pen.setColor(isEnabled() ? backgroundColor()
                             : QtMaterialStyle::instance().themeColor("disabled"));
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawArc(arcRect, 0, 360 * 16);

    if (isEnabled()) {
        pen.setColor(color());
        painter.setPen(pen);

        if (Material::IndeterminateProgress == d->progressType) {
            const int start = static_cast<int>(d->delegate->dashOffset() * 360.0 * 16.0);
            painter.drawArc(arcRect, start, 110 * 16);
        } else {
            const qreal range = maximum() - minimum();
            const qreal ratio = (range <= 0)
                ? 0
                : (value() - minimum()) / range;
            painter.drawArc(arcRect, 90 * 16, static_cast<int>(-ratio * 360.0 * 16.0));
        }
    }

    if (d->showPercentage && Material::DeterminateProgress == d->progressType) {
        const qreal range = maximum() - minimum();
        const int percentage = (range <= 0)
            ? 0
            : qRound(100.0 * (value() - minimum()) / range);
        painter.setPen(color());
        painter.drawText(rect(), Qt::AlignCenter, QString::number(percentage) + QLatin1Char('%'));
    }
}
