#include "qtmaterialpaper.h"
#include "qtmaterialpaper_p.h"

#include <QPainter>
#include <QPainterPath>

#include "lib/qtmaterialstyle.h"

QtMaterialPaperPrivate::QtMaterialPaperPrivate(QtMaterialPaper *q)
    : q_ptr(q),
      shadowEffect(0),
      cornerRadius(2),
      elevation(2),
      useThemeColors(true)
{
}

QtMaterialPaperPrivate::~QtMaterialPaperPrivate()
{
}

void QtMaterialPaperPrivate::init()
{
    Q_Q(QtMaterialPaper);

    shadowEffect = new QGraphicsDropShadowEffect(q);
    q->setGraphicsEffect(shadowEffect);
    q->setAttribute(Qt::WA_TranslucentBackground);
    q->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    q->setContentsMargins(frameMargin(), frameMargin(), frameMargin(), frameMargin());

    updateDropShadow();
}

void QtMaterialPaperPrivate::updateDropShadow()
{
    Q_Q(QtMaterialPaper);

    const int margin = frameMargin();
    q->setContentsMargins(margin, margin, margin, margin);

    if (!shadowEffect) {
        return;
    }

    shadowEffect->setColor(QColor(0, 0, 0, 80 + elevation * 12));
    shadowEffect->setBlurRadius(8 + elevation * 6);
    shadowEffect->setOffset(0, qMax(1, elevation));
}

int QtMaterialPaperPrivate::frameMargin() const
{
    return qMax(6, 8 + elevation * 2);
}

QtMaterialPaper::QtMaterialPaper(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialPaperPrivate(this))
{
    d_func()->init();
}

QtMaterialPaper::~QtMaterialPaper()
{
}

void QtMaterialPaper::setUseThemeColors(bool value)
{
    Q_D(QtMaterialPaper);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool QtMaterialPaper::useThemeColors() const
{
    Q_D(const QtMaterialPaper);

    return d->useThemeColors;
}

void QtMaterialPaper::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialPaper);

    d->backgroundColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialPaper::backgroundColor() const
{
    Q_D(const QtMaterialPaper);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return QColor(255, 255, 255);
    }

    return d->backgroundColor;
}

void QtMaterialPaper::setOutlineColor(const QColor &color)
{
    Q_D(QtMaterialPaper);

    d->outlineColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialPaper::outlineColor() const
{
    Q_D(const QtMaterialPaper);

    if (d->useThemeColors || !d->outlineColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("border");
    }

    return d->outlineColor;
}

void QtMaterialPaper::setCornerRadius(qreal radius)
{
    Q_D(QtMaterialPaper);

    d->cornerRadius = qMax(static_cast<qreal>(0), radius);
    update();
}

qreal QtMaterialPaper::cornerRadius() const
{
    Q_D(const QtMaterialPaper);

    return d->cornerRadius;
}

void QtMaterialPaper::setElevation(int value)
{
    Q_D(QtMaterialPaper);

    const int elevation = qMax(0, value);
    if (d->elevation == elevation) {
        return;
    }

    d->elevation = elevation;
    d->updateDropShadow();
    updateGeometry();
    update();
}

int QtMaterialPaper::elevation() const
{
    Q_D(const QtMaterialPaper);

    return d->elevation;
}

QSize QtMaterialPaper::sizeHint() const
{
    return QSize(240, 160);
}

QSize QtMaterialPaper::minimumSizeHint() const
{
    Q_D(const QtMaterialPaper);

    const int margin = d->frameMargin();
    return QSize(96 + margin * 2, 72 + margin * 2);
}

void QtMaterialPaper::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialPaper);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const QRectF frame = rect().adjusted(d->frameMargin() / 2.0,
                                         d->frameMargin() / 2.0,
                                         -d->frameMargin() / 2.0,
                                         -d->frameMargin() / 2.0);

    QPainterPath path;
    path.addRoundedRect(frame, d->cornerRadius, d->cornerRadius);

    painter.fillPath(path, backgroundColor());

    QPen pen(outlineColor());
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawPath(path);
}
