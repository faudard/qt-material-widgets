#ifndef QTMATERIALNAVIGATIONRAIL_H
#define QTMATERIALNAVIGATIONRAIL_H

#include <QColor>
#include <QIcon>
#include <QScopedPointer>
#include <QWidget>

class QtMaterialNavigationRailPrivate;

class QtMaterialNavigationRail : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor foregroundColor WRITE setForegroundColor READ foregroundColor)
    Q_PROPERTY(QColor accentColor WRITE setAccentColor READ accentColor)
    Q_PROPERTY(bool showLabels WRITE setShowLabels READ showLabels)
    Q_PROPERTY(bool useThemeColors WRITE setUseThemeColors READ useThemeColors)

public:
    explicit QtMaterialNavigationRail(QWidget *parent = 0);
    ~QtMaterialNavigationRail();

    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

    int addItem(const QIcon &icon, const QString &text);
    void insertItem(int index, const QIcon &icon, const QString &text);
    void removeItem(int index);
    int count() const;

    void setCurrentIndex(int index);
    int currentIndex() const;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setShowLabels(bool value);
    bool showLabels() const;

    void setCompact(bool value);
    bool isCompact() const;

    void setItemSpacing(int value);
    int itemSpacing() const;

    void setIconSize(const QSize &size);
    QSize iconSize() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setForegroundColor(const QColor &color);
    QColor foregroundColor() const;

    void setAccentColor(const QColor &color);
    QColor accentColor() const;

signals:
    void currentIndexChanged(int index);
    void itemTriggered(int index);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialNavigationRailPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialNavigationRail)
    Q_DECLARE_PRIVATE(QtMaterialNavigationRail)
};

#endif // QTMATERIALNAVIGATIONRAIL_H
