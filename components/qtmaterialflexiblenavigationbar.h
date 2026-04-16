#ifndef QTMATERIALFLEXIBLENAVIGATIONBAR_H
#define QTMATERIALFLEXIBLENAVIGATIONBAR_H

#include <QWidget>
#include <QColor>
#include <QIcon>

class QtMaterialFlexibleNavigationBarPrivate;

class QtMaterialFlexibleNavigationBar : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(bool showLabels READ showLabels WRITE setShowLabels)
    Q_PROPERTY(bool showActiveIndicator READ showActiveIndicator WRITE setShowActiveIndicator)
    Q_PROPERTY(int iconSize READ iconSize WRITE setIconSize)
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor)
    Q_PROPERTY(QColor selectedColor READ selectedColor WRITE setSelectedColor)
    Q_PROPERTY(QColor indicatorColor READ indicatorColor WRITE setIndicatorColor)

public:
    explicit QtMaterialFlexibleNavigationBar(QWidget *parent = 0);
    ~QtMaterialFlexibleNavigationBar();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setShowLabels(bool value);
    bool showLabels() const;

    void setShowActiveIndicator(bool value);
    bool showActiveIndicator() const;

    void setIconSize(int value);
    int iconSize() const;

    void setCurrentIndex(int value);
    int currentIndex() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setForegroundColor(const QColor &color);
    QColor foregroundColor() const;

    void setSelectedColor(const QColor &color);
    QColor selectedColor() const;

    void setIndicatorColor(const QColor &color);
    QColor indicatorColor() const;

    int addItem(const QIcon &icon, const QString &text);
    int count() const;

signals:
    void currentChanged(int index);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

protected:
    const QScopedPointer<QtMaterialFlexibleNavigationBarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialFlexibleNavigationBar)
    Q_DECLARE_PRIVATE(QtMaterialFlexibleNavigationBar)
};

#endif // QTMATERIALFLEXIBLENAVIGATIONBAR_H
