#ifndef QTMATERIALNAVIGATIONBADGEINTEGRATION_H
#define QTMATERIALNAVIGATIONBADGEINTEGRATION_H

#include <QObject>
#include <QColor>
#include <QHash>
#include <QString>

class QWidget;
class QtMaterialBadge;
class QtMaterialNavigationBadgeIntegrationPrivate;

class QtMaterialNavigationBadgeIntegration : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(int maxCount READ maxCount WRITE setMaxCount)

public:
    explicit QtMaterialNavigationBadgeIntegration(QObject *parent = 0);
    ~QtMaterialNavigationBadgeIntegration();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setMaxCount(int value);
    int maxCount() const;

    void attachTo(QWidget *navigationWidget);
    QWidget *navigationWidget() const;

    void setBadgeCount(int index, int count);
    int badgeCount(int index) const;

    void setBadgeText(int index, const QString &text);
    QString badgeText(int index) const;

    void setBadgeVisible(int index, bool value);
    bool isBadgeVisible(int index) const;

    void clearBadge(int index);
    void clear();

signals:
    void badgeChanged(int index);
    void navigationWidgetChanged(QWidget *widget);

protected:
    const QScopedPointer<QtMaterialNavigationBadgeIntegrationPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialNavigationBadgeIntegration)
    Q_DECLARE_PRIVATE(QtMaterialNavigationBadgeIntegration)
};

#endif // QTMATERIALNAVIGATIONBADGEINTEGRATION_H
