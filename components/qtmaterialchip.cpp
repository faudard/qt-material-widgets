#include "qtmaterialchip.h"
#include "qtmaterialchip_p.h"
#include "lib/qtmaterialstyle.h"

#include <QCursor>
#include <QEvent>
#include <QFontMetrics>
#include <QHoverEvent>
#include <QMouseEvent>
#include <QPainter>

namespace {
static const int kChipHeight = 32;
static const int kRadius = 16;
static const int kPaddingH = 12;
static const int kSpacing = 8;
static const int kIconSize = 18;
static const int kCloseHit = 24;
}

QtMaterialChipPrivate::QtMaterialChipPrivate(QtMaterialChip *q)
    : q_ptr(q)
    , useThemeColors(true)
    , showLeadingIcon(false)
    , showTrailingIcon(false)
    , closable(false)
    , hovered(false)
    , closeHovered(false)
    , closePressed(false)
{
}

QtMaterialChipPrivate::~QtMaterialChipPrivate()
{
}

void QtMaterialChipPrivate::init()
{
    Q_Q(QtMaterialChip);
    q->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    q->setMinimumHeight(kChipHeight);
    q->setCursor(Qt::PointingHandCursor);
    q->setAttribute(Qt::WA_Hover, true);
    q->setMouseTracking(true);
}

bool QtMaterialChipPrivate::hasLeadingVisual() const
{
    return showLeadingIcon && !leadingIcon.isNull();
}

bool QtMaterialChipPrivate::hasTrailingVisual() const
{
    return closable || (showTrailingIcon && !trailingIcon.isNull());
}

QRect QtMaterialChipPrivate::leadingIconRect() const
{
    Q_Q(const QtMaterialChip);
    const int y = (q->height() - kIconSize) / 2;
    return QRect(kPaddingH, y, kIconSize, kIconSize);
}

QRect QtMaterialChipPrivate::trailingHitRect() const
{
    Q_Q(const QtMaterialChip);
    const int y = (q->height() - kCloseHit) / 2;
    return QRect(q->width() - kPaddingH - kCloseHit, y, kCloseHit, kCloseHit);
}

QRect QtMaterialChipPrivate::trailingIconRect() const
{
    const QRect hit = trailingHitRect();
    const int x = hit.x() + (hit.width() - kIconSize) / 2;
    const int y = hit.y() + (hit.height() - kIconSize) / 2;
    return QRect(x, y, kIconSize, kIconSize);
}

QColor QtMaterialChipPrivate::resolvedBackgroundColor() const
{
    Q_Q(const QtMaterialChip);

    if (!q->isEnabled()) {
        return disabledColor.isValid()
                ? disabledColor
                : QtMaterialStyle::instance().themeColor("disabled3");
    }

    if (q->isCheckable() && q->isChecked()) {
        return selectedColor.isValid()
                ? selectedColor
                : QtMaterialStyle::instance().themeColor("accent1");
    }

    return backgroundColor.isValid()
            ? backgroundColor
            : QtMaterialStyle::instance().themeColor("accent2");
}

QColor QtMaterialChipPrivate::resolvedForegroundColor() const
{
    Q_Q(const QtMaterialChip);

    if (!q->isEnabled()) {
        return QtMaterialStyle::instance().themeColor("disabled");
    }

    if (textColor.isValid()) {
        return textColor;
    }

    if (q->isCheckable() && q->isChecked()) {
        return QtMaterialStyle::instance().themeColor("alternateText");
    }

    return QtMaterialStyle::instance().themeColor("text");
}

QColor QtMaterialChipPrivate::resolvedOutlineColor() const
{
    Q_Q(const QtMaterialChip);

    if (!q->isEnabled()) {
        return QtMaterialStyle::instance().themeColor("disabled3");
    }

    if (q->isCheckable() && q->isChecked()) {
        return selectedColor.isValid()
                ? selectedColor
                : QtMaterialStyle::instance().themeColor("accent1");
    }

    return QtMaterialStyle::instance().themeColor("border");
}

QtMaterialChip::QtMaterialChip(QWidget *parent)
    : QAbstractButton(parent)
    , d_ptr(new QtMaterialChipPrivate(this))
{
    Q_D(QtMaterialChip);
    d->init();
}

QtMaterialChip::QtMaterialChip(const QString &text, QWidget *parent)
    : QAbstractButton(parent)
    , d_ptr(new QtMaterialChipPrivate(this))
{
    Q_D(QtMaterialChip);
    d->init();
    setText(text);
}

QtMaterialChip::~QtMaterialChip()
{
}

void QtMaterialChip::setUseThemeColors(bool value)
{
    Q_D(QtMaterialChip);
    if (d->useThemeColors == value) {
        return;
    }
    d->useThemeColors = value;
    update();
}

bool QtMaterialChip::useThemeColors() const
{
    Q_D(const QtMaterialChip);
    return d->useThemeColors;
}

void QtMaterialChip::setTextColor(const QColor &color)
{
    Q_D(QtMaterialChip);
    d->textColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialChip::textColor() const
{
    Q_D(const QtMaterialChip);
    return d->useThemeColors ? d->resolvedForegroundColor() : d->textColor;
}

void QtMaterialChip::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialChip);
    d->backgroundColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialChip::backgroundColor() const
{
    Q_D(const QtMaterialChip);
    return d->useThemeColors ? d->resolvedBackgroundColor() : d->backgroundColor;
}

void QtMaterialChip::setSelectedColor(const QColor &color)
{
    Q_D(QtMaterialChip);
    d->selectedColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialChip::selectedColor() const
{
    Q_D(const QtMaterialChip);
    return d->useThemeColors
            ? QtMaterialStyle::instance().themeColor("accent1")
            : d->selectedColor;
}

void QtMaterialChip::setDisabledColor(const QColor &color)
{
    Q_D(QtMaterialChip);
    d->disabledColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialChip::disabledColor() const
{
    Q_D(const QtMaterialChip);
    return d->useThemeColors
            ? QtMaterialStyle::instance().themeColor("disabled3")
            : d->disabledColor;
}

void QtMaterialChip::setShowLeadingIcon(bool value)
{
    Q_D(QtMaterialChip);
    if (d->showLeadingIcon == value) {
        return;
    }
    d->showLeadingIcon = value;
    updateGeometry();
    update();
}

bool QtMaterialChip::showLeadingIcon() const
{
    Q_D(const QtMaterialChip);
    return d->showLeadingIcon;
}

void QtMaterialChip::setLeadingIcon(const QIcon &icon)
{
    Q_D(QtMaterialChip);
    d->leadingIcon = icon;
    updateGeometry();
    update();
}

QIcon QtMaterialChip::leadingIcon() const
{
    Q_D(const QtMaterialChip);
    return d->leadingIcon;
}

void QtMaterialChip::setShowTrailingIcon(bool value)
{
    Q_D(QtMaterialChip);
    if (d->showTrailingIcon == value) {
        return;
    }
    d->showTrailingIcon = value;
    updateGeometry();
    update();
}

bool QtMaterialChip::showTrailingIcon() const
{
    Q_D(const QtMaterialChip);
    return d->showTrailingIcon;
}

void QtMaterialChip::setTrailingIcon(const QIcon &icon)
{
    Q_D(QtMaterialChip);
    d->trailingIcon = icon;
    updateGeometry();
    update();
}

QIcon QtMaterialChip::trailingIcon() const
{
    Q_D(const QtMaterialChip);
    return d->trailingIcon;
}

void QtMaterialChip::setClosable(bool value)
{
    Q_D(QtMaterialChip);
    if (d->closable == value) {
        return;
    }
    d->closable = value;
    updateGeometry();
    update();
}

bool QtMaterialChip::isClosable() const
{
    Q_D(const QtMaterialChip);
    return d->closable;
}

QSize QtMaterialChip::sizeHint() const
{
    Q_D(const QtMaterialChip);

    QFontMetrics fm(font());
    int width = 2 * kPaddingH + qMax(0, fm.horizontalAdvance(text()));

    if (d->hasLeadingVisual()) {
        width += kIconSize + kSpacing;
    }
    if (d->hasTrailingVisual()) {
        width += kSpacing + kCloseHit;
    }

    return QSize(qMax(width, 56), kChipHeight);
}

bool QtMaterialChip::event(QEvent *event)
{
    Q_D(QtMaterialChip);

    switch (event->type()) {
    case QEvent::HoverEnter:
    case QEvent::Enter:
        d->hovered = true;
        d->closeHovered = d->closable && d->trailingHitRect().contains(mapFromGlobal(QCursor::pos()));
        update();
        break;
    case QEvent::HoverMove: {
        d->hovered = true;
        const QPoint pos = static_cast<QHoverEvent *>(event)->pos();
        const bool closeHovered = d->closable && d->trailingHitRect().contains(pos);
        if (d->closeHovered != closeHovered) {
            d->closeHovered = closeHovered;
            update();
        }
        break;
    }
    case QEvent::HoverLeave:
    case QEvent::Leave:
        d->hovered = false;
        d->closeHovered = false;
        update();
        break;
    default:
        break;
    }

    return QAbstractButton::event(event);
}

void QtMaterialChip::mousePressEvent(QMouseEvent *event)
{
    Q_D(QtMaterialChip);

    if (isEnabled() &&
        d->closable &&
        event->button() == Qt::LeftButton &&
        d->trailingHitRect().contains(event->pos())) {
        d->closePressed = true;
        setDown(true);
        update();
        event->accept();
        return;
    }

    d->closePressed = false;
    QAbstractButton::mousePressEvent(event);
}

void QtMaterialChip::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(QtMaterialChip);

    if (d->closePressed) {
        const bool inside = d->trailingHitRect().contains(event->pos());
        d->closePressed = false;
        setDown(false);
        update();

        if (inside && isEnabled()) {
            emit closeClicked();
        }

        event->accept();
        return;
    }

    QAbstractButton::mouseReleaseEvent(event);
}

void QtMaterialChip::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialChip);

    const QColor background = d->useThemeColors ? d->resolvedBackgroundColor() : backgroundColor();
    const QColor foreground = d->useThemeColors ? d->resolvedForegroundColor() : textColor();
    const QColor outline = d->useThemeColors ? d->resolvedOutlineColor() : background.darker(108);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const QRectF r = rect().adjusted(0.5, 0.5, -0.5, -0.5);

    painter.setPen(QPen(outline, 1));
    painter.setBrush(background);
    painter.drawRoundedRect(r, kRadius, kRadius);

    if (isDown()) {
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(0, 0, 0, 38));
        painter.drawRoundedRect(r, kRadius, kRadius);
    } else if (d->hovered) {
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(0, 0, 0, 20));
        painter.drawRoundedRect(r, kRadius, kRadius);
    }

    int textLeft = kPaddingH;
    int textRight = width() - kPaddingH;

    auto paintTintedIcon = [&](const QIcon &icon, const QRect &target, const QColor &color) {
        QPixmap pixmap = icon.pixmap(QSize(target.width(), target.height()));
        if (pixmap.isNull()) {
            return;
        }
        QPainter iconPainter(&pixmap);
        if (!iconPainter.isActive()) {
            return;
        }
        iconPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        iconPainter.fillRect(pixmap.rect(), color);
        iconPainter.end();
        painter.drawPixmap(target, pixmap);
    };

    if (d->hasLeadingVisual()) {
        const QRect iconRect = d->leadingIconRect();
        paintTintedIcon(d->leadingIcon, iconRect, foreground);
        textLeft = iconRect.right() + 1 + kSpacing;
    }

    if (d->hasTrailingVisual()) {
        const QRect hitRect = d->trailingHitRect();
        const QRect iconRect = d->trailingIconRect();

        if (d->closeHovered || d->closePressed) {
            painter.setPen(Qt::NoPen);
            painter.setBrush(QColor(0, 0, 0, d->closePressed ? 42 : 24));
            painter.drawEllipse(hitRect.adjusted(2, 2, -2, -2));
        }

        if (d->closable && d->trailingIcon.isNull()) {
            QPen pen(foreground);
            pen.setWidthF(1.8);
            pen.setCapStyle(Qt::RoundCap);
            painter.setPen(pen);
            painter.drawLine(iconRect.topLeft(), iconRect.bottomRight());
            painter.drawLine(iconRect.topRight(), iconRect.bottomLeft());
        } else {
            paintTintedIcon(d->trailingIcon, iconRect, foreground);
        }

        textRight = hitRect.left() - kSpacing;
    }

    painter.setPen(foreground);
    painter.drawText(QRect(textLeft, 0, qMax(0, textRight - textLeft), height()),
                     Qt::AlignVCenter | Qt::AlignLeft,
                     text());
}
