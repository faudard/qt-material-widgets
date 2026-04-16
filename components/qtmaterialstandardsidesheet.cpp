#include "qtmaterialstandardsidesheet.h"
#include "qtmaterialstandardsidesheet_p.h"

#include <QLayout>
#include <QPainter>

QtMaterialStandardSideSheetPrivate::QtMaterialStandardSideSheetPrivate(QtMaterialStandardSideSheet *q)
    : q_ptr(q), useThemeColors(true), width(280), expanded(true), layout(0)
{
}

void QtMaterialStandardSideSheetPrivate::init()
{
    Q_Q(QtMaterialStandardSideSheet);
    layout = new QVBoxLayout(q);
    layout->setContentsMargins(24, 24, 24, 24);
    layout->setSpacing(16);
    q->setMinimumWidth(width);
    q->setMaximumWidth(width);
}

QColor QtMaterialStandardSideSheetPrivate::resolvedBackgroundColor() const
{
    return backgroundColor.isValid() ? backgroundColor : QColor(248, 248, 248);
}

QtMaterialStandardSideSheet::QtMaterialStandardSideSheet(QWidget *parent)
    : QWidget(parent), d_ptr(new QtMaterialStandardSideSheetPrivate(this))
{
    Q_D(QtMaterialStandardSideSheet);
    d->init();
}

QtMaterialStandardSideSheet::~QtMaterialStandardSideSheet()
{
}

void QtMaterialStandardSideSheet::setUseThemeColors(bool value)
{
    Q_D(QtMaterialStandardSideSheet);
    d->useThemeColors = value;
    update();
}

bool QtMaterialStandardSideSheet::useThemeColors() const
{
    Q_D(const QtMaterialStandardSideSheet);
    return d->useThemeColors;
}

void QtMaterialStandardSideSheet::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialStandardSideSheet);
    d->backgroundColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialStandardSideSheet::backgroundColor() const
{
    Q_D(const QtMaterialStandardSideSheet);
    return d->backgroundColor;
}

void QtMaterialStandardSideSheet::setSheetWidth(int width)
{
    Q_D(QtMaterialStandardSideSheet);
    d->width = qMax(160, width);
    setMinimumWidth(d->width);
    setMaximumWidth(d->width);
    updateGeometry();
}

int QtMaterialStandardSideSheet::sheetWidth() const
{
    Q_D(const QtMaterialStandardSideSheet);
    return d->width;
}

void QtMaterialStandardSideSheet::setExpanded(bool value)
{
    Q_D(QtMaterialStandardSideSheet);
    if (d->expanded == value) {
        return;
    }
    d->expanded = value;
    setVisible(value);
    emit expandedChanged(value);
}

bool QtMaterialStandardSideSheet::isExpanded() const
{
    Q_D(const QtMaterialStandardSideSheet);
    return d->expanded;
}

void QtMaterialStandardSideSheet::setContentLayout(QLayout *layout)
{
    Q_D(QtMaterialStandardSideSheet);
    if (!layout) {
        return;
    }
    delete d->layout;
    d->layout = new QVBoxLayout(this);
    d->layout->setContentsMargins(24, 24, 24, 24);
    d->layout->addLayout(layout);
}

QLayout *QtMaterialStandardSideSheet::contentLayout() const
{
    Q_D(const QtMaterialStandardSideSheet);
    return d->layout;
}

void QtMaterialStandardSideSheet::paintEvent(QPaintEvent *)
{
    Q_D(QtMaterialStandardSideSheet);
    QPainter painter(this);
    painter.fillRect(rect(), d->resolvedBackgroundColor());
}

QSize QtMaterialStandardSideSheet::sizeHint() const
{
    Q_D(const QtMaterialStandardSideSheet);
    return QSize(d->width, 400);
}
