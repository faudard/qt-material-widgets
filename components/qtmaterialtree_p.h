#ifndef QTMATERIALTREE_P_H
#define QTMATERIALTREE_P_H

#include <QColor>
#include <QModelIndex>

class QtMaterialTree;

class QtMaterialTreePrivate
{
    Q_DISABLE_COPY(QtMaterialTreePrivate)
    Q_DECLARE_PUBLIC(QtMaterialTree)

public:
    QtMaterialTreePrivate(QtMaterialTree *q);
    ~QtMaterialTreePrivate();

    void init();
    QModelIndex hoveredIndex() const;

    QtMaterialTree *const q_ptr;

    QColor textColor;
    QColor secondaryTextColor;
    QColor backgroundColor;
    QColor dividerColor;
    QColor selectedColor;
    QColor hoverColor;
    QColor branchColor;
    bool useThemeColors;
    bool dense;
    bool showDivider;
};

#endif // QTMATERIALTREE_P_H
