#ifndef QTMATERIALBUTTONGROUP_H
#define QTMATERIALBUTTONGROUP_H

#include <QColor>
#include <QList>
#include <QScopedPointer>
#include <QWidget>

class QAbstractButton;
class QButtonGroup;
class QHBoxLayout;

class QtMaterialButtonGroupPrivate;

class QtMaterialButtonGroup : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(bool exclusive READ isExclusive WRITE setExclusive)
    Q_PROPERTY(int spacing READ spacing WRITE setSpacing)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor selectedColor READ selectedColor WRITE setSelectedColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor selectedTextColor READ selectedTextColor WRITE setSelectedTextColor)

public:
    explicit QtMaterialButtonGroup(QWidget *parent = 0);
    ~QtMaterialButtonGroup();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setExclusive(bool value);
    bool isExclusive() const;

    void setSpacing(int value);
    int spacing() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setSelectedColor(const QColor &color);
    QColor selectedColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setSelectedTextColor(const QColor &color);
    QColor selectedTextColor() const;

    void addButton(QAbstractButton *button);
    void removeButton(QAbstractButton *button);
    QList<QAbstractButton *> buttons() const;

    int checkedIndex() const;
    void setCheckedIndex(int index);

signals:
    void buttonClicked(int index);
    void checkedIndexChanged(int index);

protected slots:
    void updateButtonStyles();
    void handleButtonClicked(QAbstractButton *button);
    void handleButtonToggled(QAbstractButton *button, bool checked);

protected:
    void updateGeometryForButtons();

    const QScopedPointer<QtMaterialButtonGroupPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialButtonGroup)
    Q_DECLARE_PRIVATE(QtMaterialButtonGroup)
};

#endif // QTMATERIALBUTTONGROUP_H
