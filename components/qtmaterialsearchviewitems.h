#ifndef QTMATERIALSEARCHVIEWITEMS_H
#define QTMATERIALSEARCHVIEWITEMS_H

#include <QStyledItemDelegate>
#include <QColor>

class QtMaterialSearchViewItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit QtMaterialSearchViewItemDelegate(QObject *parent = 0);

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setSecondaryTextColor(const QColor &color);
    QColor secondaryTextColor() const;

    void setDividerColor(const QColor &color);
    QColor dividerColor() const;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE;
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE;

private:
    QColor m_textColor;
    QColor m_secondaryTextColor;
    QColor m_dividerColor;
};

#endif // QTMATERIALSEARCHVIEWITEMS_H
