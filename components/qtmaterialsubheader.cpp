#include "qtmaterialsubheader.h"
#include "qtmaterialsubheader_p.h"
#include "lib/qtmaterialstyle.h"

#include <QColor>
#include <QPainter>
#include <QPaintEvent>
#include <QPen>

QtMaterialSubheaderPrivate::QtMaterialSubheaderPrivate(QtMaterialSubheader *q)
    : q_ptr(q),
      useThemeColors(true),
      textColor(0),
      inset(16),
      divider(false),
      dense(false),
      alignment(Qt::AlignLeft | Qt::AlignVCenter)
{
}

QtMaterialSubheaderPrivate::~QtMaterialSubheaderPrivate()
{
    delete textColor;
}

void QtMaterialSubheaderPrivate::init()
{
    Q_Q(QtMaterialSubheader);

    q->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    q->setAttribute(Qt::WA_Hover, false);
}

QtMaterialSubheader::QtMaterialSubheader(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialSubheaderPrivate(this))
{
    d_func()->init();
}

QtMaterialSubheader::~QtMaterialSubheader()
{
}

QSize QtMaterialSubheader::sizeHint() const
{
    return QSize(160, d_func()->dense ? 40 : 48);
}

QSize QtMaterialSubheader::minimumSizeHint() const
{
    return QSize(72, d_func()->dense ? 32 : 40);
}

void QtMaterialSubheader::setUseThemeColors(bool value)
{
    Q_D(QtMaterialSubheader);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool QtMaterialSubheader::useThemeColors() const
{
    Q_D(const QtMaterialSubheader);

    return d->useThemeColors;
}

void QtMaterialSubheader::setText(const QString &text)
{
    Q_D(QtMaterialSubheader);

    if (d->text == text) {
        return;
    }

    d->text = text;
    update();
}

QString QtMaterialSubheader::text() const
{
    Q_D(const QtMaterialSubheader);

    return d->text;
}

void QtMaterialSubheader::setTextColor(const QColor &color)
{
    Q_D(QtMaterialSubheader);

    if (!d->textColor) {
        d->textColor = new QColor(color);
    } else if (*d->textColor == color) {
        return;
    } else {
        *d->textColor = color;
    }

    d->useThemeColors = false;
    update();
}

QColor QtMaterialSubheader::textColor() const
{
    Q_D(const QtMaterialSubheader);

    if (d->useThemeColors || !d->textColor) {
        return QtMaterialStyle::instance().themeColor("text").darker(115);
    }

    return *d->textColor;
}

void QtMaterialSubheader::setInset(int value)
{
    Q_D(QtMaterialSubheader);

    value = qMax(0, value);
    if (d->inset == value) {
        return;
    }

    d->inset = value;
    updateGeometry();
    update();
}

int QtMaterialSubheader::inset() const
{
    Q_D(const QtMaterialSubheader);

    return d->inset;
}

void QtMaterialSubheader::setShowDivider(bool value)
{
    Q_D(QtMaterialSubheader);

    if (d->divider == value) {
        return;
    }

    d->divider = value;
    update();
}

bool QtMaterialSubheader::showDivider() const
{
    Q_D(const QtMaterialSubheader);

    return d->divider;
}

void QtMaterialSubheader::setDense(bool value)
{
    Q_D(QtMaterialSubheader);

    if (d->dense == value) {
        return;
    }

    d->dense = value;
    updateGeometry();
    update();
}

bool QtMaterialSubheader::isDense() const
{
    Q_D(const QtMaterialSubheader);

    return d->dense;
}

void QtMaterialSubheader::setAlignment(Qt::Alignment alignment)
{
    Q_D(QtMaterialSubheader);

    if (d->alignment == alignment) {
        return;
    }

    d->alignment = alignment;
    update();
}

Qt::Alignment QtMaterialSubheader::alignment() const
{
    Q_D(const QtMaterialSubheader);

    return d->alignment;
}

void QtMaterialSubheader::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialSubheader);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);

    QFont f(font());
    f.setBold(true);
    f.setPointSizeF(d->dense ? 9.0 : 10.0);
    painter.setFont(f);
    painter.setPen(textColor());

    QRect textRect = rect().adjusted(d->inset, 0, -d->inset, d->divider ? -1 : 0);
    painter.drawText(textRect, d->alignment | Qt::TextSingleLine, d->text);

    if (d->divider) {
        QColor divider = QtMaterialStyle::instance().themeColor("border");
        painter.setPen(QPen(divider, 1));
        painter.drawLine(d->inset, height() - 1, width() - d->inset, height() - 1);
    }
}
