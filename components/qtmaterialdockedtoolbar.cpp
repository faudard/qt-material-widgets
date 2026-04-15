#include "qtmaterialdockedtoolbar.h"
#include "qtmaterialdockedtoolbar_p.h"

#include <QPainter>

QtMaterialDockedToolBarPrivate::QtMaterialDockedToolBarPrivate(QtMaterialDockedToolBar *q)
    : q_ptr(q), useThemeColors(true), showDivider(true), contentPadding(16), layout(0)
{
}

QtMaterialDockedToolBarPrivate::~QtMaterialDockedToolBarPrivate()
{
}

void QtMaterialDockedToolBarPrivate::init()
{
    Q_Q(QtMaterialDockedToolBar);

    layout = new QHBoxLayout;
    layout->setContentsMargins(contentPadding, 0, contentPadding, 0);
    layout->setSpacing(8);
    q->setLayout(layout);
    q->setMinimumHeight(56);
}

QtMaterialDockedToolBar::QtMaterialDockedToolBar(QWidget *parent)
    : QWidget(parent), d_ptr(new QtMaterialDockedToolBarPrivate(this))
{
    Q_D(QtMaterialDockedToolBar);
    d->init();
}

QtMaterialDockedToolBar::~QtMaterialDockedToolBar()
{
}

void QtMaterialDockedToolBar::setUseThemeColors(bool value)
{
    Q_D(QtMaterialDockedToolBar);
    d->useThemeColors = value;
    update();
}

bool QtMaterialDockedToolBar::useThemeColors() const
{
    Q_D(const QtMaterialDockedToolBar);
    return d->useThemeColors;
}

void QtMaterialDockedToolBar::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialDockedToolBar);
    d->backgroundColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialDockedToolBar::backgroundColor() const
{
    Q_D(const QtMaterialDockedToolBar);
    return d->backgroundColor;
}

void QtMaterialDockedToolBar::setTextColor(const QColor &color)
{
    Q_D(QtMaterialDockedToolBar);
    d->textColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialDockedToolBar::textColor() const
{
    Q_D(const QtMaterialDockedToolBar);
    return d->textColor;
}

void QtMaterialDockedToolBar::setDividerColor(const QColor &color)
{
    Q_D(QtMaterialDockedToolBar);
    d->dividerColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialDockedToolBar::dividerColor() const
{
    Q_D(const QtMaterialDockedToolBar);
    return d->dividerColor;
}

void QtMaterialDockedToolBar::setShowDivider(bool value)
{
    Q_D(QtMaterialDockedToolBar);
    d->showDivider = value;
    update();
}

bool QtMaterialDockedToolBar::showDivider() const
{
    Q_D(const QtMaterialDockedToolBar);
    return d->showDivider;
}

void QtMaterialDockedToolBar::setContentPadding(int value)
{
    Q_D(QtMaterialDockedToolBar);
    d->contentPadding = value;
    if (d->layout) {
        d->layout->setContentsMargins(value, 0, value, 0);
    }
    updateGeometry();
}

int QtMaterialDockedToolBar::contentPadding() const
{
    Q_D(const QtMaterialDockedToolBar);
    return d->contentPadding;
}

void QtMaterialDockedToolBar::paintEvent(QPaintEvent *)
{
    Q_D(QtMaterialDockedToolBar);
    QPainter painter(this);
    painter.fillRect(rect(), d->backgroundColor.isValid() ? d->backgroundColor : QColor(250, 250, 250));
    if (d->showDivider) {
        painter.setPen(d->dividerColor.isValid() ? d->dividerColor : QColor(220, 220, 220));
        painter.drawLine(rect().bottomLeft(), rect().bottomRight());
    }
}

QSize QtMaterialDockedToolBar::sizeHint() const
{
    return QSize(360, 64);
}
