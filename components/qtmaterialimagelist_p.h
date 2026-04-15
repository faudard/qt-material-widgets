#ifndef QTMATERIALIMAGELIST_P_H
#define QTMATERIALIMAGELIST_P_H

#include "qtmaterialimagelist.h"
#include <QStyledItemDelegate>
#include <QScopedPointer>

class QtMaterialImageListDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit QtMaterialImageListDelegate(QtMaterialImageList *parent);

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE;

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE;

private:
    QtMaterialImageList *const m_list;
};

class QtMaterialImageListPrivate
{
    Q_DISABLE_COPY(QtMaterialImageListPrivate)
    Q_DECLARE_PUBLIC(QtMaterialImageList)

public:
    explicit QtMaterialImageListPrivate(QtMaterialImageList *q);
    ~QtMaterialImageListPrivate();

    void init();

    QtMaterialImageList *const q_ptr;
    QtMaterialImageListDelegate *delegate;

    bool useThemeColors;
    bool masonryMode;
    bool showOverlayText;
    int columnWidth;
    int itemSpacing;

    QColor backgroundColor;
    QColor textColor;
    QColor secondaryTextColor;
    QColor overlayColor;
    QColor selectedColor;
    QColor hoverColor;
};

#endif // QTMATERIALIMAGELIST_P_H
