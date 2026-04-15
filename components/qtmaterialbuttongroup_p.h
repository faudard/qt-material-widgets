#ifndef QTMATERIALBUTTONGROUP_P_H
#define QTMATERIALBUTTONGROUP_P_H

#include <QColor>
#include <QList>

class QAbstractButton;
class QButtonGroup;
class QHBoxLayout;
class QtMaterialButtonGroup;

class QtMaterialButtonGroupPrivate
{
    Q_DISABLE_COPY(QtMaterialButtonGroupPrivate)
    Q_DECLARE_PUBLIC(QtMaterialButtonGroup)

public:
    QtMaterialButtonGroupPrivate(QtMaterialButtonGroup *q);
    ~QtMaterialButtonGroupPrivate();

    void init();

    QtMaterialButtonGroup *const q_ptr;
    QHBoxLayout *layout;
    QButtonGroup *group;
    QList<QAbstractButton *> buttons;

    bool useThemeColors;
    bool exclusive;
    int spacing;

    QColor backgroundColor;
    QColor selectedColor;
    QColor textColor;
    QColor selectedTextColor;
};

#endif // QTMATERIALBUTTONGROUP_P_H
