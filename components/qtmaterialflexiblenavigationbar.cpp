#include "qtmaterialflexiblenavigationbar.h"
#include "qtmaterialflexiblenavigationbar_p.h"
#include <QPainter>
#include <QMouseEvent>

QtMaterialFlexibleNavigationBarPrivate::QtMaterialFlexibleNavigationBarPrivate(QtMaterialFlexibleNavigationBar *q)
    : q_ptr(q),
      useThemeColors(true),
      showLabels(true),
      showActiveIndicator(true),
      iconSize(24),
      currentIndex(-1)
{
}

QtMaterialFlexibleNavigationBarPrivate::~QtMaterialFlexibleNavigationBarPrivate()
{
}

void QtMaterialFlexibleNavigationBarPrivate::init()
{
}

void QtMaterialFlexibleNavigationBarPrivate::layoutItems()
{
    Q_Q(QtMaterialFlexibleNavigationBar);
    if (items.isEmpty()) {
        return;
    }
    const int w = q->width() / items.size();
    for (int i = 0; i < items.size(); ++i) {
        items[i].rect = QRect(i * w, 0, w, q->height());
    }
}

QtMaterialFlexibleNavigationBar::QtMaterialFlexibleNavigationBar(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialFlexibleNavigationBarPrivate(this))
{
    Q_D(QtMaterialFlexibleNavigationBar);
    d->init();
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setMinimumHeight(64);
}

QtMaterialFlexibleNavigationBar::~QtMaterialFlexibleNavigationBar()
{
}

void QtMaterialFlexibleNavigationBar::setUseThemeColors(bool value)
{
    Q_D(QtMaterialFlexibleNavigationBar);
    d->useThemeColors = value;
    update();
}

bool QtMaterialFlexibleNavigationBar::useThemeColors() const
{
    Q_D(const QtMaterialFlexibleNavigationBar);
    return d->useThemeColors;
}

void QtMaterialFlexibleNavigationBar::setShowLabels(bool value)
{
    Q_D(QtMaterialFlexibleNavigationBar);
    d->showLabels = value;
    update();
}

bool QtMaterialFlexibleNavigationBar::showLabels() const
{
    Q_D(const QtMaterialFlexibleNavigationBar);
    return d->showLabels;
}

void QtMaterialFlexibleNavigationBar::setShowActiveIndicator(bool value)
{
    Q_D(QtMaterialFlexibleNavigationBar);
    d->showActiveIndicator = value;
    update();
}

bool QtMaterialFlexibleNavigationBar::showActiveIndicator() const
{
    Q_D(const QtMaterialFlexibleNavigationBar);
    return d->showActiveIndicator;
}

void QtMaterialFlexibleNavigationBar::setIconSize(int value)
{
    Q_D(QtMaterialFlexibleNavigationBar);
    d->iconSize = value;
    update();
}

int QtMaterialFlexibleNavigationBar::iconSize() const
{
    Q_D(const QtMaterialFlexibleNavigationBar);
    return d->iconSize;
}

void QtMaterialFlexibleNavigationBar::setCurrentIndex(int value)
{
    Q_D(QtMaterialFlexibleNavigationBar);
    if (d->currentIndex == value) {
        return;
    }
    d->currentIndex = value;
    update();
    emit currentChanged(value);
}

int QtMaterialFlexibleNavigationBar::currentIndex() const
{
    Q_D(const QtMaterialFlexibleNavigationBar);
    return d->currentIndex;
}

void QtMaterialFlexibleNavigationBar::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialFlexibleNavigationBar);
    d->backgroundColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialFlexibleNavigationBar::backgroundColor() const
{
    Q_D(const QtMaterialFlexibleNavigationBar);
    return d->backgroundColor;
}

void QtMaterialFlexibleNavigationBar::setForegroundColor(const QColor &color)
{
    Q_D(QtMaterialFlexibleNavigationBar);
    d->foregroundColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialFlexibleNavigationBar::foregroundColor() const
{
    Q_D(const QtMaterialFlexibleNavigationBar);
    return d->foregroundColor;
}

void QtMaterialFlexibleNavigationBar::setSelectedColor(const QColor &color)
{
    Q_D(QtMaterialFlexibleNavigationBar);
    d->selectedColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialFlexibleNavigationBar::selectedColor() const
{
    Q_D(const QtMaterialFlexibleNavigationBar);
    return d->selectedColor;
}

void QtMaterialFlexibleNavigationBar::setIndicatorColor(const QColor &color)
{
    Q_D(QtMaterialFlexibleNavigationBar);
    d->indicatorColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialFlexibleNavigationBar::indicatorColor() const
{
    Q_D(const QtMaterialFlexibleNavigationBar);
    return d->indicatorColor;
}

int QtMaterialFlexibleNavigationBar::addItem(const QIcon &icon, const QString &text)
{
    Q_D(QtMaterialFlexibleNavigationBar);
    QtMaterialFlexibleNavigationBarPrivate::Item item;
    item.icon = icon;
    item.text = text;
    d->items.push_back(item);
    if (d->currentIndex < 0) {
        d->currentIndex = 0;
    }
    d->layoutItems();
    update();
    return d->items.size() - 1;
}

int QtMaterialFlexibleNavigationBar::count() const
{
    Q_D(const QtMaterialFlexibleNavigationBar);
    return d->items.size();
}

void QtMaterialFlexibleNavigationBar::paintEvent(QPaintEvent *)
{
    Q_D(QtMaterialFlexibleNavigationBar);
    QPainter painter(this);
    painter.fillRect(rect(), d->backgroundColor.isValid() ? d->backgroundColor : QColor(250, 250, 250));

    for (int i = 0; i < d->items.size(); ++i) {
        const auto &item = d->items.at(i);
        const bool selected = (i == d->currentIndex);
        if (selected && d->showActiveIndicator) {
            painter.setPen(Qt::NoPen);
            painter.setBrush(d->indicatorColor.isValid() ? d->indicatorColor : QColor(220, 230, 255));
            painter.drawRoundedRect(item.rect.adjusted(8, 8, -8, -8), 16, 16);
        }

        const QRect iconRect(item.rect.center().x() - d->iconSize / 2, item.rect.top() + 10, d->iconSize, d->iconSize);
        item.icon.paint(&painter, iconRect);

        if (d->showLabels) {
            painter.setPen(selected && d->selectedColor.isValid() ? d->selectedColor : QColor(33, 33, 33));
            painter.drawText(item.rect.adjusted(4, d->iconSize + 18, -4, -6), Qt::AlignHCenter | Qt::AlignTop, item.text);
        }
    }
}

void QtMaterialFlexibleNavigationBar::resizeEvent(QResizeEvent *)
{
    Q_D(QtMaterialFlexibleNavigationBar);
    d->layoutItems();
}

void QtMaterialFlexibleNavigationBar::mousePressEvent(QMouseEvent *event)
{
    Q_D(QtMaterialFlexibleNavigationBar);
    for (int i = 0; i < d->items.size(); ++i) {
        if (d->items.at(i).rect.contains(event->pos())) {
            setCurrentIndex(i);
            break;
        }
    }
}

QSize QtMaterialFlexibleNavigationBar::sizeHint() const
{
    return QSize(420, 80);
}

QSize QtMaterialFlexibleNavigationBar::minimumSizeHint() const
{
    return QSize(240, 64);
}
