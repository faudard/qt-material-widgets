#ifndef QTMATERIALTOGGLEICONBUTTON_P_H
#define QTMATERIALTOGGLEICONBUTTON_P_H

#include "qtmaterialiconbutton_p.h"
#include <QIcon>

class QtMaterialToggleIconButton;

class QtMaterialToggleIconButtonPrivate : public QtMaterialIconButtonPrivate
{
    Q_DISABLE_COPY(QtMaterialToggleIconButtonPrivate)
    Q_DECLARE_PUBLIC(QtMaterialToggleIconButton)

public:
    QtMaterialToggleIconButtonPrivate(QtMaterialToggleIconButton *q);
    ~QtMaterialToggleIconButtonPrivate();

    void init();

    QIcon selectedIcon;
    QColor selectedColor;
    QColor selectedDisabledColor;

protected:
    QtMaterialToggleIconButton *const q_ptr;
};

#endif // QTMATERIALTOGGLEICONBUTTON_P_H
