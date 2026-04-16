#include "qtmaterialbadge.h"
#include "qtmaterialbadge_p.h"

#include <QPainter>
#include <QMouseEvent>
#include <QFontMetrics>

QtMaterialBadgePrivate::QtMaterialBadgePrivate(QtMaterialBadge *q)
    : q_ptr(q),
      useThemeColors(true),
      count(0),
      countMode(false),
      visibleWhenZero(false),
      outlined(false)
{
}

void QtMaterialBadgePrivate::init()
{
}

QtMaterialBadge::QtMaterialBadge(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialBadgePrivate(this))
{
    Q_D(QtMaterialBadge);
    d->init();
    setAttribute(Qt::WA_Hover);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
}

QtMaterialBadge::~QtMaterialBadge()
{
}

void QtMaterialBadge::setUseThemeColors(bool value) { Q_D(QtMaterialBadge); d->useThemeColors = value; update(); }
bool QtMaterialBadge::useThemeColors() const { Q_D(const QtMaterialBadge); return d->useThemeColors; }

void QtMaterialBadge::setText(const QString &text) { Q_D(QtMaterialBadge); d->text = text; updateGeometry(); update(); }
QString QtMaterialBadge::text() const { Q_D(const QtMaterialBadge); return d->text; }

void QtMaterialBadge::setCount(int value) { Q_D(QtMaterialBadge); d->count = value; updateGeometry(); update(); }
int QtMaterialBadge::count() const { Q_D(const QtMaterialBadge); return d->count; }

void QtMaterialBadge::setCountMode(bool value) { Q_D(QtMaterialBadge); d->countMode = value; updateGeometry(); update(); }
bool QtMaterialBadge::countMode() const { Q_D(const QtMaterialBadge); return d->countMode; }

void QtMaterialBadge::setVisibleWhenZero(bool value) { Q_D(QtMaterialBadge); d->visibleWhenZero = value; update(); }
bool QtMaterialBadge::visibleWhenZero() const { Q_D(const QtMaterialBadge); return d->visibleWhenZero; }

void QtMaterialBadge::setOutlined(bool value) { Q_D(QtMaterialBadge); d->outlined = value; update(); }
bool QtMaterialBadge::isOutlined() const { Q_D(const QtMaterialBadge); return d->outlined; }

void QtMaterialBadge::setBackgroundColor(const QColor &color) { Q_D(QtMaterialBadge); d->backgroundColor = color; d->useThemeColors = false; update(); }
QColor QtMaterialBadge::backgroundColor() const { Q_D(const QtMaterialBadge); return d->backgroundColor.isValid() ? d->backgroundColor : QColor(198, 40, 40); }

void QtMaterialBadge::setTextColor(const QColor &color) { Q_D(QtMaterialBadge); d->textColor = color; d->useThemeColors = false; update(); }
QColor QtMaterialBadge::textColor() const { Q_D(const QtMaterialBadge); return d->textColor.isValid() ? d->textColor : QColor(Qt::white); }

void QtMaterialBadge::setBorderColor(const QColor &color) { Q_D(QtMaterialBadge); d->borderColor = color; d->useThemeColors = false; update(); }
QColor QtMaterialBadge::borderColor() const { Q_D(const QtMaterialBadge); return d->borderColor.isValid() ? d->borderColor : QColor(Qt::transparent); }

QSize QtMaterialBadge::sizeHint() const
{
    Q_D(const QtMaterialBadge);
    const QString label = d->countMode ? QString::number(d->count) : d->text;
    QFontMetrics fm(font());
    int w = qMax(20, fm.horizontalAdvance(label) + 12);
    return QSize(w, 20);
}

QSize QtMaterialBadge::minimumSizeHint() const
{
    return sizeHint();
}

void QtMaterialBadge::paintEvent(QPaintEvent *)
{
    Q_D(QtMaterialBadge);
    if (d->countMode && d->count == 0 && !d->visibleWhenZero) {
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QRect r = rect().adjusted(1, 1, -1, -1);

    painter.setBrush(backgroundColor());
    painter.setPen(d->outlined ? QPen(borderColor(), 1) : Qt::NoPen);
    painter.drawRoundedRect(r, r.height() / 2.0, r.height() / 2.0);

    painter.setPen(textColor());
    const QString label = d->countMode ? QString::number(d->count) : d->text;
    painter.drawText(r, Qt::AlignCenter, label);
}

void QtMaterialBadge::mouseReleaseEvent(QMouseEvent *event)
{
    if (rect().contains(event->pos()) && event->button() == Qt::LeftButton) {
        emit clicked();
    }
    QWidget::mouseReleaseEvent(event);
}
