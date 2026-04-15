#include "qtmaterialsearchappbar.h"
#include "qtmaterialsearchappbar_p.h"

#include <QPainter>
#include <QHBoxLayout>
#include <QWidget>

QtMaterialSearchAppBarPrivate::QtMaterialSearchAppBarPrivate()
    : useThemeColors(true),
      active(false),
      showDivider(true),
      searchBar(0),
      leadingContainer(0),
      trailingContainer(0),
      layout(0)
{
}

QtMaterialSearchAppBar::QtMaterialSearchAppBar(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialSearchAppBarPrivate)
{
    Q_D(QtMaterialSearchAppBar);

    d->layout = new QHBoxLayout;
    d->layout->setContentsMargins(16, 8, 16, 8);
    d->layout->setSpacing(12);

    d->leadingContainer = new QWidget(this);
    d->trailingContainer = new QWidget(this);
    d->searchBar = 0; // Wired in real implementation.

    d->layout->addWidget(d->leadingContainer);
    d->layout->addStretch(1);
    d->layout->addWidget(d->trailingContainer);
    setLayout(d->layout);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

QtMaterialSearchAppBar::~QtMaterialSearchAppBar()
{
}

QSize QtMaterialSearchAppBar::sizeHint() const
{
    return QSize(360, 64);
}

void QtMaterialSearchAppBar::setUseThemeColors(bool value)
{
    Q_D(QtMaterialSearchAppBar);
    d->useThemeColors = value;
    update();
}

bool QtMaterialSearchAppBar::useThemeColors() const
{
    Q_D(const QtMaterialSearchAppBar);
    return d->useThemeColors;
}

void QtMaterialSearchAppBar::setForegroundColor(const QColor &color)
{
    Q_D(QtMaterialSearchAppBar);
    d->foregroundColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialSearchAppBar::foregroundColor() const
{
    Q_D(const QtMaterialSearchAppBar);
    return d->foregroundColor.isValid() ? d->foregroundColor : QColor("#212121");
}

void QtMaterialSearchAppBar::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialSearchAppBar);
    d->backgroundColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialSearchAppBar::backgroundColor() const
{
    Q_D(const QtMaterialSearchAppBar);
    return d->backgroundColor.isValid() ? d->backgroundColor : QColor("#fafafa");
}

void QtMaterialSearchAppBar::setDividerColor(const QColor &color)
{
    Q_D(QtMaterialSearchAppBar);
    d->dividerColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialSearchAppBar::dividerColor() const
{
    Q_D(const QtMaterialSearchAppBar);
    return d->dividerColor.isValid() ? d->dividerColor : QColor("#d0d0d0");
}

void QtMaterialSearchAppBar::setActive(bool value)
{
    Q_D(QtMaterialSearchAppBar);
    if (d->active == value) {
        return;
    }
    d->active = value;
    emit activeChanged(value);
    update();
}

bool QtMaterialSearchAppBar::isActive() const
{
    Q_D(const QtMaterialSearchAppBar);
    return d->active;
}

void QtMaterialSearchAppBar::setShowDivider(bool value)
{
    Q_D(QtMaterialSearchAppBar);
    d->showDivider = value;
    update();
}

bool QtMaterialSearchAppBar::showDivider() const
{
    Q_D(const QtMaterialSearchAppBar);
    return d->showDivider;
}

QtMaterialSearchBar *QtMaterialSearchAppBar::searchBar() const
{
    Q_D(const QtMaterialSearchAppBar);
    return d->searchBar;
}

QWidget *QtMaterialSearchAppBar::leadingContainer() const
{
    Q_D(const QtMaterialSearchAppBar);
    return d->leadingContainer;
}

QWidget *QtMaterialSearchAppBar::trailingContainer() const
{
    Q_D(const QtMaterialSearchAppBar);
    return d->trailingContainer;
}

void QtMaterialSearchAppBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.fillRect(rect(), backgroundColor());

    if (showDivider()) {
        painter.fillRect(QRect(0, height()-1, width(), 1), dividerColor());
    }
}
