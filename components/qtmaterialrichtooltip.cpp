#include "qtmaterialrichtooltip.h"
#include "qtmaterialrichtooltip_p.h"
#include "lib/qtmaterialstyle.h"
#include "lib/qtmaterialtheme.h"

#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QStyleOption>

QtMaterialRichTooltipPrivate::QtMaterialRichTooltipPrivate(QtMaterialRichTooltip *q)
    : QtMaterialTooltipPrivate(q),
      showIcon(false),
      maximumTextWidth(240),
      q_ptr(q)
{
}

QtMaterialRichTooltipPrivate::~QtMaterialRichTooltipPrivate()
{
}

void QtMaterialRichTooltipPrivate::init()
{
    Q_Q(QtMaterialRichTooltip);

    title = QStringLiteral("Rich tooltip title");
    supportingText = QStringLiteral("Supporting text can span multiple lines and include a concise explanation.");
    primaryActionText = QStringLiteral("OK");
    secondaryActionText = QString();
    icon = QIcon();
    surfaceColor = QColor();
    titleColor = QColor();
    supportingTextColor = QColor();
    actionColor = QColor();

    q->setPadding(16);
    q->setFontSize(12);
    q->setAutoHideDuration(0);
    q->setFixedHeight(120);
}

QtMaterialRichTooltip::QtMaterialRichTooltip(QWidget *parent)
    : QtMaterialTooltip(parent),
      d_ptr(new QtMaterialRichTooltipPrivate(this))
{
    Q_D(QtMaterialRichTooltip);
    d->init();
}

QtMaterialRichTooltip::~QtMaterialRichTooltip()
{
}

void QtMaterialRichTooltip::setTitle(const QString &title)
{
    Q_D(QtMaterialRichTooltip);
    d->title = title;
    update();
}

QString QtMaterialRichTooltip::title() const
{
    Q_D(const QtMaterialRichTooltip);
    return d->title;
}

void QtMaterialRichTooltip::setSupportingText(const QString &text)
{
    Q_D(QtMaterialRichTooltip);
    d->supportingText = text;
    updateGeometry();
    update();
}

QString QtMaterialRichTooltip::supportingText() const
{
    Q_D(const QtMaterialRichTooltip);
    return d->supportingText;
}

void QtMaterialRichTooltip::setPrimaryActionText(const QString &text)
{
    Q_D(QtMaterialRichTooltip);
    d->primaryActionText = text;
    update();
}

QString QtMaterialRichTooltip::primaryActionText() const
{
    Q_D(const QtMaterialRichTooltip);
    return d->primaryActionText;
}

void QtMaterialRichTooltip::setSecondaryActionText(const QString &text)
{
    Q_D(QtMaterialRichTooltip);
    d->secondaryActionText = text;
    update();
}

QString QtMaterialRichTooltip::secondaryActionText() const
{
    Q_D(const QtMaterialRichTooltip);
    return d->secondaryActionText;
}

void QtMaterialRichTooltip::setIcon(const QIcon &icon)
{
    Q_D(QtMaterialRichTooltip);
    d->icon = icon;
    update();
}

QIcon QtMaterialRichTooltip::icon() const
{
    Q_D(const QtMaterialRichTooltip);
    return d->icon;
}

void QtMaterialRichTooltip::setShowIcon(bool value)
{
    Q_D(QtMaterialRichTooltip);
    d->showIcon = value;
    update();
}

bool QtMaterialRichTooltip::showIcon() const
{
    Q_D(const QtMaterialRichTooltip);
    return d->showIcon;
}

void QtMaterialRichTooltip::setMaximumTextWidth(int value)
{
    Q_D(QtMaterialRichTooltip);
    d->maximumTextWidth = qMax(160, value);
    updateGeometry();
    update();
}

int QtMaterialRichTooltip::maximumTextWidth() const
{
    Q_D(const QtMaterialRichTooltip);
    return d->maximumTextWidth;
}

void QtMaterialRichTooltip::setSurfaceColor(const QColor &color)
{
    Q_D(QtMaterialRichTooltip);
    d->surfaceColor = color;
    update();
}

QColor QtMaterialRichTooltip::surfaceColor() const
{
    Q_D(const QtMaterialRichTooltip);

    if (d->surfaceColor.isValid()) {
        return d->surfaceColor;
    }

    if (useThemeColors()) {
        return QtMaterialStyle::instance().themeColor("canvas");
    }

    return backgroundColor();
}

void QtMaterialRichTooltip::setTitleColor(const QColor &color)
{
    Q_D(QtMaterialRichTooltip);
    d->titleColor = color;
    update();
}

QColor QtMaterialRichTooltip::titleColor() const
{
    Q_D(const QtMaterialRichTooltip);

    if (d->titleColor.isValid()) {
        return d->titleColor;
    }

    if (useThemeColors()) {
        return QtMaterialStyle::instance().themeColor("primary1");
    }

    return textColor();
}

void QtMaterialRichTooltip::setSupportingTextColor(const QColor &color)
{
    Q_D(QtMaterialRichTooltip);
    d->supportingTextColor = color;
    update();
}

QColor QtMaterialRichTooltip::supportingTextColor() const
{
    Q_D(const QtMaterialRichTooltip);

    if (d->supportingTextColor.isValid()) {
        return d->supportingTextColor;
    }

    if (useThemeColors()) {
        return QtMaterialStyle::instance().themeColor("text");
    }

    return textColor();
}

void QtMaterialRichTooltip::setActionColor(const QColor &color)
{
    Q_D(QtMaterialRichTooltip);
    d->actionColor = color;
    update();
}

QColor QtMaterialRichTooltip::actionColor() const
{
    Q_D(const QtMaterialRichTooltip);

    if (d->actionColor.isValid()) {
        return d->actionColor;
    }

    if (useThemeColors()) {
        return QtMaterialStyle::instance().themeColor("accent1");
    }

    return textColor();
}

QSize QtMaterialRichTooltip::sizeHint() const
{
    Q_D(const QtMaterialRichTooltip);
    return QSize(d->maximumTextWidth + 32, 120);
}

void QtMaterialRichTooltip::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialRichTooltip);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect r = rect().adjusted(1, 1, -1, -1);
    painter.setPen(Qt::NoPen);
    painter.setBrush(surfaceColor());
    painter.drawRoundedRect(r, 8, 8);

    const int pad = padding();
    int x = pad;
    int y = pad;

    if (d->showIcon && !d->icon.isNull()) {
        QRect iconRect(x, y, 24, 24);
        d->icon.paint(&painter, iconRect);
        x += 24 + 12;
    }

    painter.setPen(titleColor());
    QFont f = font();
    f.setBold(true);
    f.setPointSizeF(fontSize() + 1);
    painter.setFont(f);
    QRect titleRect(x, y, width() - x - pad, 20);
    painter.drawText(titleRect, Qt::AlignLeft | Qt::AlignVCenter, d->title);

    painter.setPen(supportingTextColor());
    f = font();
    f.setBold(false);
    f.setPointSizeF(fontSize());
    painter.setFont(f);
    QRect textRect(pad, y + 28, width() - 2 * pad, 42);
    painter.drawText(textRect, Qt::TextWordWrap | Qt::AlignLeft | Qt::AlignTop, d->supportingText);

    painter.setPen(actionColor());
    f.setBold(true);
    painter.setFont(f);

    const int actionY = height() - pad - 20;
    d->secondaryActionRect = QRect(width() - pad - 150, actionY, 64, 20);
    d->primaryActionRect = QRect(width() - pad - 72, actionY, 64, 20);

    if (!d->secondaryActionText.isEmpty()) {
        painter.drawText(d->secondaryActionRect, Qt::AlignCenter, d->secondaryActionText.toUpper());
    }

    if (!d->primaryActionText.isEmpty()) {
        painter.drawText(d->primaryActionRect, Qt::AlignCenter, d->primaryActionText.toUpper());
    }
}

void QtMaterialRichTooltip::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(QtMaterialRichTooltip);

    if (d->primaryActionRect.contains(event->pos()) && !d->primaryActionText.isEmpty()) {
        emit primaryActionTriggered();
        return;
    }

    if (d->secondaryActionRect.contains(event->pos()) && !d->secondaryActionText.isEmpty()) {
        emit secondaryActionTriggered();
        return;
    }

    QtMaterialTooltip::mouseReleaseEvent(event);
}
