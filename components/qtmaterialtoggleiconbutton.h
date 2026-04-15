#ifndef QTMATERIALTOGGLEICONBUTTON_H
#define QTMATERIALTOGGLEICONBUTTON_H

#include "qtmaterialiconbutton.h"

class QtMaterialToggleIconButtonPrivate;

class QtMaterialToggleIconButton : public QtMaterialIconButton
{
    Q_OBJECT

    Q_PROPERTY(QIcon selectedIcon READ selectedIcon WRITE setSelectedIcon)
    Q_PROPERTY(QColor selectedColor READ selectedColor WRITE setSelectedColor)
    Q_PROPERTY(QColor selectedDisabledColor READ selectedDisabledColor WRITE setSelectedDisabledColor)

public:
    explicit QtMaterialToggleIconButton(const QIcon &icon = QIcon(), QWidget *parent = 0);
    ~QtMaterialToggleIconButton();

    void setSelectedIcon(const QIcon &icon);
    QIcon selectedIcon() const;

    void setSelectedColor(const QColor &color);
    QColor selectedColor() const;

    void setSelectedDisabledColor(const QColor &color);
    QColor selectedDisabledColor() const;

protected:
    QtMaterialToggleIconButton(QtMaterialToggleIconButtonPrivate &d, const QIcon &icon, QWidget *parent = 0);

    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialToggleIconButtonPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialToggleIconButton)
    Q_DECLARE_PRIVATE(QtMaterialToggleIconButton)
};

#endif // QTMATERIALTOGGLEICONBUTTON_H
