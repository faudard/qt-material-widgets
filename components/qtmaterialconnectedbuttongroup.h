#ifndef QTMATERIALCONNECTEDBUTTONGROUP_H
#define QTMATERIALCONNECTEDBUTTONGROUP_H

#include <QWidget>
#include <QColor>
#include <qicon.h>

class QtMaterialConnectedButtonGroupPrivate;
class QtMaterialFlatButton;

class QtMaterialConnectedButtonGroup : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(bool exclusive READ isExclusive WRITE setExclusive)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor selectedColor READ selectedColor WRITE setSelectedColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor selectedTextColor READ selectedTextColor WRITE setSelectedTextColor)
    Q_PROPERTY(QColor outlineColor READ outlineColor WRITE setOutlineColor)
    Q_PROPERTY(int spacing READ spacing WRITE setSpacing)

public:
    explicit QtMaterialConnectedButtonGroup(QWidget *parent = 0);
    ~QtMaterialConnectedButtonGroup();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setExclusive(bool value);
    bool isExclusive() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setSelectedColor(const QColor &color);
    QColor selectedColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setSelectedTextColor(const QColor &color);
    QColor selectedTextColor() const;

    void setOutlineColor(const QColor &color);
    QColor outlineColor() const;

    void setSpacing(int value);
    int spacing() const;

    QtMaterialFlatButton *addButton(const QString &text, const QIcon &icon = QIcon());
    int count() const;
    QtMaterialFlatButton *buttonAt(int index) const;
    int checkedIndex() const;
    QList<int> checkedIndexes() const;

public slots:
    void setCheckedIndex(int index);
    void clearSelection();

signals:
    void buttonClicked(int index);
    void selectionChanged();
    void checkedIndexChanged(int index);

protected:
    const QScopedPointer<QtMaterialConnectedButtonGroupPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialConnectedButtonGroup)
    Q_DECLARE_PRIVATE(QtMaterialConnectedButtonGroup)
};

#endif  // QTMATERIALCONNECTEDBUTTONGROUP_H
