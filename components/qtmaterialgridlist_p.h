#ifndef QTMATERIALGRIDLIST_P_H
#define QTMATERIALGRIDLIST_P_H

#include <QColor>
#include <QPersistentModelIndex>

class QtMaterialGridList;
class QStyledItemDelegate;

class QtMaterialGridListPrivate
{
    Q_DISABLE_COPY(QtMaterialGridListPrivate)
    Q_DECLARE_PUBLIC(QtMaterialGridList)

public:
    explicit QtMaterialGridListPrivate(QtMaterialGridList *q);
    ~QtMaterialGridListPrivate();

    void init();
    void updateMetrics();

    QtMaterialGridList *const q_ptr;
    QStyledItemDelegate *delegate;
    bool useThemeColors;
    bool showOverlayText;
    int cellWidth;
    int cellHeight;
    int itemSpacing;
    QColor backgroundColor;
    QColor textColor;
    QColor secondaryTextColor;
    QColor selectedColor;
    QColor hoverColor;
};

#endif // QTMATERIALGRIDLIST_P_H
