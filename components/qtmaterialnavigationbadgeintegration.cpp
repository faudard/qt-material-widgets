#include "qtmaterialnavigationbadgeintegration.h"
#include "qtmaterialnavigationbadgeintegration_p.h"

#include <QWidget>

QtMaterialNavigationBadgeIntegrationPrivate::QtMaterialNavigationBadgeIntegrationPrivate(QtMaterialNavigationBadgeIntegration *q)
    : q_ptr(q),
      navigationWidget(0),
      useThemeColors(true),
      maxCount(99)
{
}

QtMaterialNavigationBadgeIntegrationPrivate::~QtMaterialNavigationBadgeIntegrationPrivate()
{
}

void QtMaterialNavigationBadgeIntegrationPrivate::init()
{
}

QString QtMaterialNavigationBadgeIntegrationPrivate::displayTextForIndex(int index) const
{
    const QtMaterialNavigationBadgeData data = badges.value(index);
    if (!data.text.isEmpty()) {
        return data.text;
    }
    if (data.count > maxCount) {
        return QString::number(maxCount) + QLatin1Char('+');
    }
    if (data.count > 0) {
        return QString::number(data.count);
    }
    return QString();
}

QtMaterialNavigationBadgeIntegration::QtMaterialNavigationBadgeIntegration(QObject *parent)
    : QObject(parent),
      d_ptr(new QtMaterialNavigationBadgeIntegrationPrivate(this))
{
    d_func()->init();
}

QtMaterialNavigationBadgeIntegration::~QtMaterialNavigationBadgeIntegration()
{
}

void QtMaterialNavigationBadgeIntegration::setUseThemeColors(bool value)
{
    Q_D(QtMaterialNavigationBadgeIntegration);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
}

bool QtMaterialNavigationBadgeIntegration::useThemeColors() const
{
    Q_D(const QtMaterialNavigationBadgeIntegration);

    return d->useThemeColors;
}

void QtMaterialNavigationBadgeIntegration::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialNavigationBadgeIntegration);

    d->backgroundColor = color;
    d->useThemeColors = false;
}

QColor QtMaterialNavigationBadgeIntegration::backgroundColor() const
{
    Q_D(const QtMaterialNavigationBadgeIntegration);

    return d->backgroundColor;
}

void QtMaterialNavigationBadgeIntegration::setTextColor(const QColor &color)
{
    Q_D(QtMaterialNavigationBadgeIntegration);

    d->textColor = color;
    d->useThemeColors = false;
}

QColor QtMaterialNavigationBadgeIntegration::textColor() const
{
    Q_D(const QtMaterialNavigationBadgeIntegration);

    return d->textColor;
}

void QtMaterialNavigationBadgeIntegration::setMaxCount(int value)
{
    Q_D(QtMaterialNavigationBadgeIntegration);

    d->maxCount = qMax(1, value);
}

int QtMaterialNavigationBadgeIntegration::maxCount() const
{
    Q_D(const QtMaterialNavigationBadgeIntegration);

    return d->maxCount;
}

void QtMaterialNavigationBadgeIntegration::attachTo(QWidget *navigationWidget)
{
    Q_D(QtMaterialNavigationBadgeIntegration);

    if (d->navigationWidget == navigationWidget) {
        return;
    }

    d->navigationWidget = navigationWidget;
    emit navigationWidgetChanged(navigationWidget);
}

QWidget *QtMaterialNavigationBadgeIntegration::navigationWidget() const
{
    Q_D(const QtMaterialNavigationBadgeIntegration);

    return d->navigationWidget;
}

void QtMaterialNavigationBadgeIntegration::setBadgeCount(int index, int count)
{
    Q_D(QtMaterialNavigationBadgeIntegration);

    QtMaterialNavigationBadgeData data = d->badges.value(index);
    data.count = qMax(0, count);
    data.visible = true;
    d->badges.insert(index, data);
    emit badgeChanged(index);
}

int QtMaterialNavigationBadgeIntegration::badgeCount(int index) const
{
    Q_D(const QtMaterialNavigationBadgeIntegration);

    return d->badges.value(index).count;
}

void QtMaterialNavigationBadgeIntegration::setBadgeText(int index, const QString &text)
{
    Q_D(QtMaterialNavigationBadgeIntegration);

    QtMaterialNavigationBadgeData data = d->badges.value(index);
    data.text = text;
    data.visible = true;
    d->badges.insert(index, data);
    emit badgeChanged(index);
}

QString QtMaterialNavigationBadgeIntegration::badgeText(int index) const
{
    Q_D(const QtMaterialNavigationBadgeIntegration);

    return d->badges.value(index).text;
}

void QtMaterialNavigationBadgeIntegration::setBadgeVisible(int index, bool value)
{
    Q_D(QtMaterialNavigationBadgeIntegration);

    QtMaterialNavigationBadgeData data = d->badges.value(index);
    data.visible = value;
    d->badges.insert(index, data);
    emit badgeChanged(index);
}

bool QtMaterialNavigationBadgeIntegration::isBadgeVisible(int index) const
{
    Q_D(const QtMaterialNavigationBadgeIntegration);

    return d->badges.value(index).visible;
}

void QtMaterialNavigationBadgeIntegration::clearBadge(int index)
{
    Q_D(QtMaterialNavigationBadgeIntegration);

    if (!d->badges.contains(index)) {
        return;
    }

    d->badges.remove(index);
    emit badgeChanged(index);
}

void QtMaterialNavigationBadgeIntegration::clear()
{
    Q_D(QtMaterialNavigationBadgeIntegration);

    const QList<int> keys = d->badges.keys();
    d->badges.clear();

    foreach (const int index, keys) {
        emit badgeChanged(index);
    }
}
