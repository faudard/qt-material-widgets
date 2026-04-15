#ifndef QTMATERIALCONNECTEDBUTTONGROUP_P_H
#define QTMATERIALCONNECTEDBUTTONGROUP_P_H

#include <QtGlobal>
#include <QColor>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QList>

class QtMaterialConnectedButtonGroup;
class QtMaterialFlatButton;

class QtMaterialConnectedButtonGroupPrivate
{
    Q_DISABLE_COPY(QtMaterialConnectedButtonGroupPrivate)
    Q_DECLARE_PUBLIC(QtMaterialConnectedButtonGroup)

public:
    QtMaterialConnectedButtonGroupPrivate(QtMaterialConnectedButtonGroup *q);
    ~QtMaterialConnectedButtonGroupPrivate();

    void init();
    void applyStyle();

    QtMaterialConnectedButtonGroup *const q_ptr;
    QButtonGroup *group;
    QHBoxLayout *layout;
    QList<QtMaterialFlatButton *> buttons;

    bool useThemeColors;
    bool exclusive;
    QColor backgroundColor;
    QColor selectedColor;
    QColor textColor;
    QColor selectedTextColor;
    QColor outlineColor;
    int spacing;
};

#endif  // QTMATERIALCONNECTEDBUTTONGROUP_P_H
