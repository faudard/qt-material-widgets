#ifndef QTMATERIALNAVIGATIONBAR_P_H
#define QTMATERIALNAVIGATIONBAR_P_H

#include <QAbstractButton>
#include <QBoxLayout>
#include <QColor>
#include <QIcon>
#include <QList>
#include <QVariant>

class QtMaterialNavigationBar;

class QtMaterialNavigationItem : public QAbstractButton
{
    Q_OBJECT

public:
    explicit QtMaterialNavigationItem(QWidget *parent = 0);
    ~QtMaterialNavigationItem();

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

    void setItemIndex(int value);
    int itemIndex() const;

    void setItemData(const QVariant &value);
    QVariant itemData() const;

    void setIcon(const QIcon &icon);
    QIcon icon() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    QColor m_textColor;
    QColor m_selectedColor;
    QColor m_rippleColor;
    bool   m_shifting;
    bool   m_labelsVisible;
    int    m_itemIndex;
    QVariant m_itemData;
    QIcon  m_icon;
};

class QtMaterialNavigationBarPrivate
{
    Q_DISABLE_COPY(QtMaterialNavigationBarPrivate)
    Q_DECLARE_PUBLIC(QtMaterialNavigationBar)

public:
    QtMaterialNavigationBarPrivate(QtMaterialNavigationBar *q);
    ~QtMaterialNavigationBarPrivate();

    void init();
    void setupItems();
    void updateItemStyles();

    QtMaterialNavigationBar *const q_ptr;
    QHBoxLayout *layout;
    QList<QtMaterialNavigationItem *> items;
    bool useThemeColors;
    bool shifting;
    bool labelsVisible;
    int currentIndex;
    QColor backgroundColor;
    QColor textColor;
    QColor selectedColor;
    QColor rippleColor;
};

#endif // QTMATERIALNAVIGATIONBAR_P_H
