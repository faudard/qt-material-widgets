#ifndef QTMATERIALLIST_P_H
#define QTMATERIALLIST_P_H

#include <QColor>
#include <QListView>
#include <QScopedPointer>

class QtMaterialList;

class QtMaterialListPrivate
{
    Q_DISABLE_COPY(QtMaterialListPrivate)
    Q_DECLARE_PUBLIC(QtMaterialList)

public:
    QtMaterialListPrivate(QtMaterialList *q);
    ~QtMaterialListPrivate();

    void init();

    QtMaterialList *const q_ptr;
    bool useThemeColors;
    bool dense;
    bool showDivider;
    QColor textColor;
    QColor secondaryTextColor;
    QColor backgroundColor;
    QColor dividerColor;
    QColor selectedColor;
    QColor hoverColor;
};

#endif // QTMATERIALLIST_P_H
