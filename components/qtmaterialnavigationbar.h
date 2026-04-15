#ifndef QTMATERIALNAVIGATIONBAR_H
#define QTMATERIALNAVIGATIONBAR_H

#include <QColor>
#include <QIcon>
#include <QList>
#include <QScopedPointer>
#include <QWidget>
#include <qvariant.h>

class QtMaterialNavigationBarPrivate;

class QtMaterialNavigationBar : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
    Q_PROPERTY(QColor selectedColor WRITE setSelectedColor READ selectedColor)
    Q_PROPERTY(QColor rippleColor WRITE setRippleColor READ rippleColor)
    Q_PROPERTY(bool shifting WRITE setShifting READ isShifting)
    Q_PROPERTY(bool labelsVisible WRITE setLabelsVisible READ labelsVisible)
    Q_PROPERTY(int currentIndex WRITE setCurrentIndex READ currentIndex)

public:
    explicit QtMaterialNavigationBar(QWidget *parent = 0);
    ~QtMaterialNavigationBar();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setSelectedColor(const QColor &color);
    QColor selectedColor() const;

    void setRippleColor(const QColor &color);
    QColor rippleColor() const;

    void setShifting(bool value);
    bool isShifting() const;

    void setLabelsVisible(bool value);
    bool labelsVisible() const;

    int addItem(const QString &text, const QIcon &icon = QIcon(), const QVariant &data = QVariant());
    int count() const;

    void setCurrentIndex(int index);
    int currentIndex() const;

    QVariant itemData(int index) const;
    void setItemEnabled(int index, bool value);
    bool isItemEnabled(int index) const;

signals:
    void currentChanged(int index);
    void itemTriggered(int index);

protected:
    QSize sizeHint() const Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    const QScopedPointer<QtMaterialNavigationBarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialNavigationBar)
    Q_DECLARE_PRIVATE(QtMaterialNavigationBar)
};

#endif // QTMATERIALNAVIGATIONBAR_H
