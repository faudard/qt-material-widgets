#include "qtmaterialstandardbottomsheet.h"
#include "qtmaterialstandardbottomsheet_p.h"

#include <QLayout>
#include <QPainter>
#include <QVBoxLayout>

QtMaterialStandardBottomSheetPrivate::QtMaterialStandardBottomSheetPrivate(QtMaterialStandardBottomSheet *q)
    : q_ptr(q)
{
}

QtMaterialStandardBottomSheetPrivate::~QtMaterialStandardBottomSheetPrivate()
{
}

void QtMaterialStandardBottomSheetPrivate::init()
{
    Q_Q(QtMaterialStandardBottomSheet);

    useThemeColors = true;
    expanded = true;
    sheetHeight = 200;
    dividerColor = QColor(0, 0, 0, 40);

    layout = new QVBoxLayout(q);
    layout->setContentsMargins(24, 16, 24, 24);
    layout->setSpacing(16);

    updateGeometry();
}

void QtMaterialStandardBottomSheetPrivate::updateGeometry()
{
    Q_Q(QtMaterialStandardBottomSheet);
    q->setMinimumHeight(expanded ? sheetHeight : 56);
    q->setMaximumHeight(expanded ? sheetHeight : 56);
    q->update();
}

QtMaterialStandardBottomSheet::QtMaterialStandardBottomSheet(QWidget *parent)
    : QWidget(parent), d_ptr(new QtMaterialStandardBottomSheetPrivate(this))
{
    Q_D(QtMaterialStandardBottomSheet);
    d->init();
}

QtMaterialStandardBottomSheet::~QtMaterialStandardBottomSheet()
{
}

void QtMaterialStandardBottomSheet::setUseThemeColors(bool value)
{
    Q_D(QtMaterialStandardBottomSheet);
    d->useThemeColors = value;
    update();
}

bool QtMaterialStandardBottomSheet::useThemeColors() const
{
    Q_D(const QtMaterialStandardBottomSheet);
    return d->useThemeColors;
}

void QtMaterialStandardBottomSheet::setSheetHeight(int value)
{
    Q_D(QtMaterialStandardBottomSheet);
    d->sheetHeight = qMax(120, value);
    d->updateGeometry();
}

int QtMaterialStandardBottomSheet::sheetHeight() const
{
    Q_D(const QtMaterialStandardBottomSheet);
    return d->sheetHeight;
}

void QtMaterialStandardBottomSheet::setExpanded(bool value)
{
    Q_D(QtMaterialStandardBottomSheet);
    if (d->expanded == value) {
        return;
    }
    d->expanded = value;
    d->updateGeometry();
    emit expandedChanged(value);
}

bool QtMaterialStandardBottomSheet::isExpanded() const
{
    Q_D(const QtMaterialStandardBottomSheet);
    return d->expanded;
}

void QtMaterialStandardBottomSheet::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialStandardBottomSheet);
    d->backgroundColor = color;
    update();
}

QColor QtMaterialStandardBottomSheet::backgroundColor() const
{
    Q_D(const QtMaterialStandardBottomSheet);
    return d->useThemeColors ? QColor(Qt::white) : d->backgroundColor;
}

void QtMaterialStandardBottomSheet::setDividerColor(const QColor &color)
{
    Q_D(QtMaterialStandardBottomSheet);
    d->dividerColor = color;
    update();
}

QColor QtMaterialStandardBottomSheet::dividerColor() const
{
    Q_D(const QtMaterialStandardBottomSheet);
    return d->dividerColor;
}

void QtMaterialStandardBottomSheet::setContentLayout(QLayout *layout)
{
    if (!layout) {
        return;
    }
    delete this->layout();
    QWidget::setLayout(layout);
}

QLayout *QtMaterialStandardBottomSheet::contentLayout() const
{
    return layout();
}

void QtMaterialStandardBottomSheet::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    Q_D(const QtMaterialStandardBottomSheet);

    QPainter painter(this);
    painter.fillRect(rect(), backgroundColor());
    painter.setPen(d->dividerColor);
    painter.drawLine(rect().topLeft(), rect().topRight());
}
