#include "qtmaterialtooltip.h"
#include "qtmaterialtooltip_p.h"
#include "lib/qtmaterialstyle.h"

#include <QEvent>
#include <QFont>
#include <QFontMetrics>
#include <QPainter>
#include <QTimerEvent>
#include <QWidget>

QtMaterialTooltipPrivate::QtMaterialTooltipPrivate(QtMaterialTooltip *q)
    : q_ptr(q),
      fontSize(10),
      padding(12),
      autoHideDuration(2500),
      useThemeColors(true),
      visible(false)
{
}

void QtMaterialTooltipPrivate::init()
{
}

QRect QtMaterialTooltipPrivate::tooltipRect() const
{
    Q_Q(const QtMaterialTooltip);

    QFont font(q->font());
    font.setPointSizeF(fontSize);
    QFontMetrics fm(font);
    QSize size = fm.size(Qt::TextSingleLine, text);
    size.rwidth() += padding * 2;
    size.rheight() += padding;

    if (target) {
        QRect r = target->geometry();
        QPoint center = r.center();
        int x = center.x() - size.width() / 2;
        int y = r.top() - size.height() - 8;
        return QRect(x, y, size.width(), size.height());
    }

    return QRect(0, 0, size.width(), size.height());
}

QtMaterialTooltip::QtMaterialTooltip(QWidget *parent)
    : QtMaterialOverlayWidget(parent),
      d_ptr(new QtMaterialTooltipPrivate(this))
{
    Q_D(QtMaterialTooltip);
    d->init();
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setVisible(false);
}

QtMaterialTooltip::~QtMaterialTooltip()
{
}

void QtMaterialTooltip::setText(const QString &text)
{
    Q_D(QtMaterialTooltip);
    d->text = text;
    update();
}

QString QtMaterialTooltip::text() const
{
    Q_D(const QtMaterialTooltip);
    return d->text;
}

void QtMaterialTooltip::setTarget(QWidget *widget)
{
    Q_D(QtMaterialTooltip);

    if (d->target) {
        d->target->removeEventFilter(this);
    }

    d->target = widget;

    if (d->target) {
        d->target->installEventFilter(this);
    }

    update();
}

QWidget *QtMaterialTooltip::target() const
{
    Q_D(const QtMaterialTooltip);
    return d->target;
}

void QtMaterialTooltip::setUseThemeColors(bool value)
{
    Q_D(QtMaterialTooltip);
    d->useThemeColors = value;
    update();
}

bool QtMaterialTooltip::useThemeColors() const
{
    Q_D(const QtMaterialTooltip);
    return d->useThemeColors;
}

void QtMaterialTooltip::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialTooltip);
    d->backgroundColor = color;
    setUseThemeColors(false);
}

QColor QtMaterialTooltip::backgroundColor() const
{
    Q_D(const QtMaterialTooltip);
    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("text");
    }
    return d->backgroundColor;
}

void QtMaterialTooltip::setTextColor(const QColor &color)
{
    Q_D(QtMaterialTooltip);
    d->textColor = color;
    setUseThemeColors(false);
}

QColor QtMaterialTooltip::textColor() const
{
    Q_D(const QtMaterialTooltip);
    if (d->useThemeColors || !d->textColor.isValid()) {
        return Qt::white;
    }
    return d->textColor;
}

void QtMaterialTooltip::setFontSize(qreal size)
{
    Q_D(QtMaterialTooltip);
    d->fontSize = size;
    update();
}

qreal QtMaterialTooltip::fontSize() const
{
    Q_D(const QtMaterialTooltip);
    return d->fontSize;
}

void QtMaterialTooltip::setPadding(int value)
{
    Q_D(QtMaterialTooltip);
    d->padding = value;
    update();
}

int QtMaterialTooltip::padding() const
{
    Q_D(const QtMaterialTooltip);
    return d->padding;
}

void QtMaterialTooltip::setAutoHideDuration(int msec)
{
    Q_D(QtMaterialTooltip);
    d->autoHideDuration = msec;
}

int QtMaterialTooltip::autoHideDuration() const
{
    Q_D(const QtMaterialTooltip);
    return d->autoHideDuration;
}

void QtMaterialTooltip::showTooltip()
{
    Q_D(QtMaterialTooltip);
    d->visible = true;
    setVisible(true);
    raise();
    update();
    if (d->autoHideDuration > 0) {
        d->hideTimer.start(d->autoHideDuration, this);
    }
}

void QtMaterialTooltip::hideTooltip()
{
    Q_D(QtMaterialTooltip);
    d->visible = false;
    d->hideTimer.stop();
    setVisible(false);
}

bool QtMaterialTooltip::eventFilter(QObject *obj, QEvent *event)
{
    Q_D(QtMaterialTooltip);

    if (obj == d->target) {
        switch (event->type()) {
        case QEvent::Enter:
            showTooltip();
            break;
        case QEvent::Leave:
        case QEvent::MouseButtonPress:
        case QEvent::Hide:
            hideTooltip();
            break;
        default:
            break;
        }
    }

    return QtMaterialOverlayWidget::eventFilter(obj, event);
}

QRect QtMaterialTooltip::overlayGeometry() const
{
    return rect();
}

void QtMaterialTooltip::paintEvent(QPaintEvent *)
{
    Q_D(QtMaterialTooltip);

    if (!d->visible || d->text.isEmpty()) {
        return;
    }

    QRect r = d->tooltipRect();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(backgroundColor());
    painter.drawRoundedRect(r, 3, 3);

    QFont font(this->font());
    font.setPointSizeF(d->fontSize);
    painter.setFont(font);
    painter.setPen(textColor());
    painter.drawText(r, Qt::AlignCenter, d->text);
}

void QtMaterialTooltip::timerEvent(QTimerEvent *event)
{
    Q_D(QtMaterialTooltip);
    if (event->timerId() == d->hideTimer.timerId()) {
        hideTooltip();
        return;
    }
    QtMaterialOverlayWidget::timerEvent(event);
}
