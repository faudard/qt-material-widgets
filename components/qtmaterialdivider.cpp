#include "qtmaterialdivider.h"
#include "qtmaterialdivider_p.h"

#include <QPainter>
#include <QSizePolicy>

#include "lib/qtmaterialstyle.h"

/*!
 * \class QtMaterialDividerPrivate
 * \internal
 */
QtMaterialDividerPrivate::QtMaterialDividerPrivate(QtMaterialDivider *q)
    : q_ptr(q)
{
}

QtMaterialDividerPrivate::~QtMaterialDividerPrivate()
{
}

void QtMaterialDividerPrivate::init()
{
    Q_Q(QtMaterialDivider);

    thickness      = 1;
    insetStart     = 0;
    insetEnd       = 0;
    useThemeColors = true;

    q->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    q->setAttribute(Qt::WA_TransparentForMouseEvents);
    updateSizePolicy();
}

void QtMaterialDividerPrivate::updateSizePolicy()
{
    Q_Q(QtMaterialDivider);

    const int h = qMax(1, thickness);
    q->setMinimumHeight(h);
    q->setMaximumHeight(h);
    q->updateGeometry();
}

/*!
 * \class QtMaterialDivider
 */
QtMaterialDivider::QtMaterialDivider(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialDividerPrivate(this))
{
    d_func()->init();
}

QtMaterialDivider::~QtMaterialDivider()
{
}

void QtMaterialDivider::setUseThemeColors(bool state)
{
    Q_D(QtMaterialDivider);

    if (d->useThemeColors == state) {
        return;
    }

    d->useThemeColors = state;
    update();
}

bool QtMaterialDivider::useThemeColors() const
{
    Q_D(const QtMaterialDivider);

    return d->useThemeColors;
}

void QtMaterialDivider::setColor(const QColor &color)
{
    Q_D(QtMaterialDivider);

    d->color = color;
    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialDivider::color() const
{
    Q_D(const QtMaterialDivider);

    if (d->useThemeColors || !d->color.isValid()) {
        return QtMaterialStyle::instance().themeColor("border");
    } else {
        return d->color;
    }
}

void QtMaterialDivider::setThickness(int thickness)
{
    Q_D(QtMaterialDivider);

    thickness = qMax(1, thickness);

    if (d->thickness == thickness) {
        return;
    }

    d->thickness = thickness;
    d->updateSizePolicy();
    update();
}

int QtMaterialDivider::thickness() const
{
    Q_D(const QtMaterialDivider);

    return d->thickness;
}

void QtMaterialDivider::setInsetStart(int inset)
{
    Q_D(QtMaterialDivider);

    inset = qMax(0, inset);

    if (d->insetStart == inset) {
        return;
    }

    d->insetStart = inset;
    update();
}

int QtMaterialDivider::insetStart() const
{
    Q_D(const QtMaterialDivider);

    return d->insetStart;
}

void QtMaterialDivider::setInsetEnd(int inset)
{
    Q_D(QtMaterialDivider);

    inset = qMax(0, inset);

    if (d->insetEnd == inset) {
        return;
    }

    d->insetEnd = inset;
    update();
}

int QtMaterialDivider::insetEnd() const
{
    Q_D(const QtMaterialDivider);

    return d->insetEnd;
}

QSize QtMaterialDivider::sizeHint() const
{
    Q_D(const QtMaterialDivider);

    return QSize(64, qMax(1, d->thickness));
}

QSize QtMaterialDivider::minimumSizeHint() const
{
    Q_D(const QtMaterialDivider);

    return QSize(1, qMax(1, d->thickness));
}

void QtMaterialDivider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialDivider);

    const int totalWidth = width();
    if (totalWidth <= 0 || height() <= 0) {
        return;
    }

    const bool leftToRight = (layoutDirection() != Qt::RightToLeft);
    int leftInset = leftToRight ? d->insetStart : d->insetEnd;
    int rightInset = leftToRight ? d->insetEnd : d->insetStart;

    leftInset = qBound(0, leftInset, totalWidth);
    rightInset = qBound(0, rightInset, totalWidth);

    const int lineWidth = totalWidth - leftInset - rightInset;
    if (lineWidth <= 0) {
        return;
    }

    const int lineHeight = qMax(1, d->thickness);
    const int y = (height() - lineHeight) / 2;

    QRect lineRect(leftInset, y, lineWidth, lineHeight);

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(isEnabled()
        ? color()
        : QtMaterialStyle::instance().themeColor("disabled"));
    painter.drawRect(lineRect);
}
