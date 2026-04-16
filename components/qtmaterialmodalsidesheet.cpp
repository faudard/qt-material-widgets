#include "qtmaterialmodalsidesheet.h"
#include "qtmaterialmodalsidesheet_p.h"

#include <QLayout>
#include <QMouseEvent>
#include <QPainter>

QtMaterialModalSideSheetPrivate::QtMaterialModalSideSheetPrivate(QtMaterialModalSideSheet *q)
    : q_ptr(q), useThemeColors(true), width(320), side(QtMaterialModalSideSheet::LeftSide),
      dismissOnOverlayClick(true), sheetWidget(0), sheetLayout(0)
{
}

void QtMaterialModalSideSheetPrivate::init()
{
    Q_Q(QtMaterialModalSideSheet);

    q->setAttribute(Qt::WA_NoSystemBackground, false);
    q->setAttribute(Qt::WA_StyledBackground, false);
    q->setVisible(false);

    sheetWidget = new QWidget(q);
    sheetLayout = new QVBoxLayout(sheetWidget);
    sheetLayout->setContentsMargins(24, 24, 24, 24);
    sheetLayout->setSpacing(16);
}

QRect QtMaterialModalSideSheetPrivate::sheetRect() const
{
    Q_Q(const QtMaterialModalSideSheet);
    if (side == QtMaterialModalSideSheet::LeftSide) {
        return QRect(0, 0, width, q->height());
    }
    return QRect(q->width() - width, 0, width, q->height());
}

QColor QtMaterialModalSideSheetPrivate::resolvedBackgroundColor() const
{
    return backgroundColor.isValid() ? backgroundColor : QColor(250, 250, 250);
}

QColor QtMaterialModalSideSheetPrivate::resolvedOverlayColor() const
{
    return overlayColor.isValid() ? overlayColor : QColor(0, 0, 0, 110);
}

QtMaterialModalSideSheet::QtMaterialModalSideSheet(QWidget *parent)
    : QWidget(parent), d_ptr(new QtMaterialModalSideSheetPrivate(this))
{
    Q_D(QtMaterialModalSideSheet);
    d->init();
}

QtMaterialModalSideSheet::~QtMaterialModalSideSheet()
{
}

void QtMaterialModalSideSheet::setUseThemeColors(bool value)
{
    Q_D(QtMaterialModalSideSheet);
    d->useThemeColors = value;
    update();
}

bool QtMaterialModalSideSheet::useThemeColors() const
{
    Q_D(const QtMaterialModalSideSheet);
    return d->useThemeColors;
}

void QtMaterialModalSideSheet::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialModalSideSheet);
    d->backgroundColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialModalSideSheet::backgroundColor() const
{
    Q_D(const QtMaterialModalSideSheet);
    return d->backgroundColor;
}

void QtMaterialModalSideSheet::setOverlayColor(const QColor &color)
{
    Q_D(QtMaterialModalSideSheet);
    d->overlayColor = color;
    update();
}

QColor QtMaterialModalSideSheet::overlayColor() const
{
    Q_D(const QtMaterialModalSideSheet);
    return d->overlayColor;
}

void QtMaterialModalSideSheet::setSheetWidth(int width)
{
    Q_D(QtMaterialModalSideSheet);
    d->width = qMax(160, width);
    updateGeometry();
    update();
}

int QtMaterialModalSideSheet::sheetWidth() const
{
    Q_D(const QtMaterialModalSideSheet);
    return d->width;
}

void QtMaterialModalSideSheet::setSide(Side side)
{
    Q_D(QtMaterialModalSideSheet);
    d->side = side;
    update();
}

QtMaterialModalSideSheet::Side QtMaterialModalSideSheet::side() const
{
    Q_D(const QtMaterialModalSideSheet);
    return d->side;
}

void QtMaterialModalSideSheet::setDismissOnOverlayClick(bool value)
{
    Q_D(QtMaterialModalSideSheet);
    d->dismissOnOverlayClick = value;
}

bool QtMaterialModalSideSheet::dismissOnOverlayClick() const
{
    Q_D(const QtMaterialModalSideSheet);
    return d->dismissOnOverlayClick;
}

void QtMaterialModalSideSheet::setContentLayout(QLayout *layout)
{
    Q_D(QtMaterialModalSideSheet);
    if (!layout) {
        return;
    }
    delete d->sheetLayout;
    d->sheetLayout = new QVBoxLayout(d->sheetWidget);
    d->sheetLayout->setContentsMargins(24, 24, 24, 24);
    d->sheetLayout->addLayout(layout);
}

QLayout *QtMaterialModalSideSheet::contentLayout() const
{
    Q_D(const QtMaterialModalSideSheet);
    return d->sheetLayout;
}

void QtMaterialModalSideSheet::open()
{
    setVisible(true);
    raise();
    emit opened();
}

void QtMaterialModalSideSheet::closeSheet()
{
    setVisible(false);
    emit closed();
}

void QtMaterialModalSideSheet::paintEvent(QPaintEvent *)
{
    Q_D(QtMaterialModalSideSheet);
    QPainter painter(this);
    painter.fillRect(rect(), d->resolvedOverlayColor());
    painter.fillRect(d->sheetRect(), d->resolvedBackgroundColor());
}

void QtMaterialModalSideSheet::resizeEvent(QResizeEvent *)
{
    Q_D(QtMaterialModalSideSheet);
    d->sheetWidget->setGeometry(d->sheetRect());
}

void QtMaterialModalSideSheet::mousePressEvent(QMouseEvent *event)
{
    Q_D(QtMaterialModalSideSheet);
    if (!d->sheetRect().contains(event->pos()) && d->dismissOnOverlayClick) {
        closeSheet();
    }
    QWidget::mousePressEvent(event);
}
