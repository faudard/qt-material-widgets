#include "qtmaterialnavigationrail.h"
#include "qtmaterialnavigationrail_p.h"

#include "lib/qtmaterialstyle.h"

#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>

QtMaterialNavigationRailPrivate::QtMaterialNavigationRailPrivate(QtMaterialNavigationRail *q)
    : q_ptr(q),
      currentIndex(0),
      useThemeColors(true),
      showLabels(true),
      compact(false),
      itemSpacing(8),
      iconSize(24, 24)
{
}

QtMaterialNavigationRailPrivate::~QtMaterialNavigationRailPrivate()
{
}

void QtMaterialNavigationRailPrivate::init()
{
    Q_Q(QtMaterialNavigationRail);

    q->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    q->setAttribute(Qt::WA_Hover);
    q->setMinimumWidth(80);
}

void QtMaterialNavigationRailPrivate::updateLayout()
{
    Q_Q(QtMaterialNavigationRail);

    const int topMargin = compact ? 12 : 20;
    const int sideMargin = 8;
    const int itemHeight = compact ? 56 : 72;
    int y = topMargin;

    for (int i = 0; i < items.count(); ++i) {
        items[i].geometry = QRect(sideMargin, y, q->width() - 2 * sideMargin, itemHeight);
        y += itemHeight + itemSpacing;
    }

    q->update();
}

QRect QtMaterialNavigationRailPrivate::itemRect(int index) const
{
    if (index < 0 || index >= items.count()) {
        return QRect();
    }
    return items.at(index).geometry;
}

QColor QtMaterialNavigationRailPrivate::resolvedBackgroundColor() const
{
    if (useThemeColors || !backgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("canvas");
    }
    return backgroundColor;
}

QColor QtMaterialNavigationRailPrivate::resolvedForegroundColor() const
{
    if (useThemeColors || !foregroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("text");
    }
    return foregroundColor;
}

QColor QtMaterialNavigationRailPrivate::resolvedAccentColor() const
{
    if (useThemeColors || !accentColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("primary1");
    }
    return accentColor;
}

QtMaterialNavigationRail::QtMaterialNavigationRail(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialNavigationRailPrivate(this))
{
    d_func()->init();
}

QtMaterialNavigationRail::~QtMaterialNavigationRail()
{
}

QSize QtMaterialNavigationRail::sizeHint() const
{
    return QSize(96, 320);
}

QSize QtMaterialNavigationRail::minimumSizeHint() const
{
    return QSize(72, 160);
}

int QtMaterialNavigationRail::addItem(const QIcon &icon, const QString &text)
{
    Q_D(QtMaterialNavigationRail);

    QtMaterialNavigationRailPrivate::RailItem item;
    item.icon = icon;
    item.text = text;
    d->items.append(item);
    d->updateLayout();
    return d->items.count() - 1;
}

void QtMaterialNavigationRail::insertItem(int index, const QIcon &icon, const QString &text)
{
    Q_D(QtMaterialNavigationRail);

    QtMaterialNavigationRailPrivate::RailItem item;
    item.icon = icon;
    item.text = text;
    index = qBound(0, index, d->items.count());
    d->items.insert(index, item);

    if (d->currentIndex >= index) {
        d->currentIndex++;
    }

    d->updateLayout();
}

void QtMaterialNavigationRail::removeItem(int index)
{
    Q_D(QtMaterialNavigationRail);

    if (index < 0 || index >= d->items.count()) {
        return;
    }

    d->items.removeAt(index);
    d->currentIndex = qMin(d->currentIndex, d->items.count() - 1);
    if (d->currentIndex < 0) {
        d->currentIndex = 0;
    }
    d->updateLayout();
}

int QtMaterialNavigationRail::count() const
{
    Q_D(const QtMaterialNavigationRail);
    return d->items.count();
}

void QtMaterialNavigationRail::setCurrentIndex(int index)
{
    Q_D(QtMaterialNavigationRail);

    if (index < 0 || index >= d->items.count() || d->currentIndex == index) {
        return;
    }

    d->currentIndex = index;
    update();
    emit currentIndexChanged(index);
}

int QtMaterialNavigationRail::currentIndex() const
{
    Q_D(const QtMaterialNavigationRail);
    return d->currentIndex;
}

void QtMaterialNavigationRail::setUseThemeColors(bool value)
{
    Q_D(QtMaterialNavigationRail);
    if (d->useThemeColors == value) {
        return;
    }
    d->useThemeColors = value;
    update();
}

bool QtMaterialNavigationRail::useThemeColors() const
{
    Q_D(const QtMaterialNavigationRail);
    return d->useThemeColors;
}

void QtMaterialNavigationRail::setShowLabels(bool value)
{
    Q_D(QtMaterialNavigationRail);
    if (d->showLabels == value) {
        return;
    }
    d->showLabels = value;
    d->updateLayout();
}

bool QtMaterialNavigationRail::showLabels() const
{
    Q_D(const QtMaterialNavigationRail);
    return d->showLabels;
}

void QtMaterialNavigationRail::setCompact(bool value)
{
    Q_D(QtMaterialNavigationRail);
    if (d->compact == value) {
        return;
    }
    d->compact = value;
    d->updateLayout();
}

bool QtMaterialNavigationRail::isCompact() const
{
    Q_D(const QtMaterialNavigationRail);
    return d->compact;
}

void QtMaterialNavigationRail::setItemSpacing(int value)
{
    Q_D(QtMaterialNavigationRail);
    value = qMax(0, value);
    if (d->itemSpacing == value) {
        return;
    }
    d->itemSpacing = value;
    d->updateLayout();
}

int QtMaterialNavigationRail::itemSpacing() const
{
    Q_D(const QtMaterialNavigationRail);
    return d->itemSpacing;
}

void QtMaterialNavigationRail::setIconSize(const QSize &size)
{
    Q_D(QtMaterialNavigationRail);
    if (d->iconSize == size) {
        return;
    }
    d->iconSize = size;
    update();
}

QSize QtMaterialNavigationRail::iconSize() const
{
    Q_D(const QtMaterialNavigationRail);
    return d->iconSize;
}

void QtMaterialNavigationRail::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialNavigationRail);
    d->backgroundColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialNavigationRail::backgroundColor() const
{
    Q_D(const QtMaterialNavigationRail);
    return d->backgroundColor;
}

void QtMaterialNavigationRail::setForegroundColor(const QColor &color)
{
    Q_D(QtMaterialNavigationRail);
    d->foregroundColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialNavigationRail::foregroundColor() const
{
    Q_D(const QtMaterialNavigationRail);
    return d->foregroundColor;
}

void QtMaterialNavigationRail::setAccentColor(const QColor &color)
{
    Q_D(QtMaterialNavigationRail);
    d->accentColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialNavigationRail::accentColor() const
{
    Q_D(const QtMaterialNavigationRail);
    return d->accentColor;
}

void QtMaterialNavigationRail::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialNavigationRail);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), d->resolvedBackgroundColor());

    const QColor textColor = d->resolvedForegroundColor();
    const QColor accent = d->resolvedAccentColor();

    for (int i = 0; i < d->items.count(); ++i) {
        const auto &item = d->items.at(i);
        const QRect itemRect = item.geometry;
        const bool selected = (i == d->currentIndex);

        if (selected) {
            painter.setPen(Qt::NoPen);
            painter.setBrush(accent.lighter(180));
            painter.drawRoundedRect(itemRect.adjusted(6, 4, -6, -4), 16, 16);
        }

        const QRect iconRect(itemRect.center().x() - d->iconSize.width() / 2,
                             itemRect.top() + 10,
                             d->iconSize.width(),
                             d->iconSize.height());

        painter.setPen(selected ? accent : textColor);
        item.icon.paint(&painter, iconRect, Qt::AlignCenter,
                        isEnabled() ? QIcon::Normal : QIcon::Disabled);

        if (d->showLabels) {
            QRect textRect = itemRect.adjusted(8, d->iconSize.height() + 18, -8, -8);
            painter.setPen(selected ? accent : textColor);
            QFont font = this->font();
            font.setPointSizeF(d->compact ? 8.5 : 9.0);
            font.setBold(selected);
            painter.setFont(font);
            painter.drawText(textRect, Qt::AlignHCenter | Qt::AlignTop | Qt::TextWordWrap, item.text);
        }
    }
}

void QtMaterialNavigationRail::mousePressEvent(QMouseEvent *event)
{
    Q_D(QtMaterialNavigationRail);

    for (int i = 0; i < d->items.count(); ++i) {
        if (d->items.at(i).geometry.contains(event->pos())) {
            setCurrentIndex(i);
            emit itemTriggered(i);
            break;
        }
    }

    QWidget::mousePressEvent(event);
}

void QtMaterialNavigationRail::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    d_func()->updateLayout();
}
