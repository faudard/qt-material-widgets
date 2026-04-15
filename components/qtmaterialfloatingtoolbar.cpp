#include "qtmaterialfloatingtoolbar.h"
#include "qtmaterialfloatingtoolbar_p.h"

#include <QPainter>
#include <QPainterPath>

QtMaterialFloatingToolBarPrivate::QtMaterialFloatingToolBarPrivate(QtMaterialFloatingToolBar *q)
    : q_ptr(q), useThemeColors(true), radius(20), contentPadding(16), layout(0)
{
}

QtMaterialFloatingToolBarPrivate::~QtMaterialFloatingToolBarPrivate()
{
}

void QtMaterialFloatingToolBarPrivate::init()
{
    Q_Q(QtMaterialFloatingToolBar);

    layout = new QHBoxLayout;
    layout->setContentsMargins(contentPadding, 0, contentPadding, 0);
    layout->setSpacing(8);
    q->setLayout(layout);
    q->setMinimumHeight(56);
    q->setAttribute(Qt::WA_TranslucentBackground);
}

QtMaterialFloatingToolBar::QtMaterialFloatingToolBar(QWidget *parent)
    : QWidget(parent), d_ptr(new QtMaterialFloatingToolBarPrivate(this))
{
    Q_D(QtMaterialFloatingToolBar);
    d->init();
}

QtMaterialFloatingToolBar::~QtMaterialFloatingToolBar()
{
}

void QtMaterialFloatingToolBar::setUseThemeColors(bool value)
{
    Q_D(QtMaterialFloatingToolBar);
    d->useThemeColors = value;
    update();
}

bool QtMaterialFloatingToolBar::useThemeColors() const
{
    Q_D(const QtMaterialFloatingToolBar);
    return d->useThemeColors;
}

void QtMaterialFloatingToolBar::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialFloatingToolBar);
    d->backgroundColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialFloatingToolBar::backgroundColor() const
{
    Q_D(const QtMaterialFloatingToolBar);
    return d->backgroundColor;
}

void QtMaterialFloatingToolBar::setTextColor(const QColor &color)
{
    Q_D(QtMaterialFloatingToolBar);
    d->textColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialFloatingToolBar::textColor() const
{
    Q_D(const QtMaterialFloatingToolBar);
    return d->textColor;
}

void QtMaterialFloatingToolBar::setRadius(int value)
{
    Q_D(QtMaterialFloatingToolBar);
    d->radius = value;
    update();
}

int QtMaterialFloatingToolBar::radius() const
{
    Q_D(const QtMaterialFloatingToolBar);
    return d->radius;
}

void QtMaterialFloatingToolBar::setContentPadding(int value)
{
    Q_D(QtMaterialFloatingToolBar);
    d->contentPadding = value;
    if (d->layout) {
        d->layout->setContentsMargins(value, 0, value, 0);
    }
    updateGeometry();
}

int QtMaterialFloatingToolBar::contentPadding() const
{
    Q_D(const QtMaterialFloatingToolBar);
    return d->contentPadding;
}

void QtMaterialFloatingToolBar::paintEvent(QPaintEvent *)
{
    Q_D(QtMaterialFloatingToolBar);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRectF r = rect().adjusted(1, 1, -1, -1);
    QPainterPath path;
    path.addRoundedRect(r, d->radius, d->radius);
    painter.fillPath(path, d->backgroundColor.isValid() ? d->backgroundColor : QColor(250, 250, 250));
    painter.setPen(QColor(0, 0, 0, 25));
    painter.drawPath(path);
}

QSize QtMaterialFloatingToolBar::sizeHint() const
{
    return QSize(300, 64);
}
