#ifndef QTMATERIALGRIDLISTITEM_H
#define QTMATERIALGRIDLISTITEM_H

#include <QPixmap>
#include <QStandardItem>

class QtMaterialGridListItemPrivate;

class QtMaterialGridListItem : public QStandardItem
{
public:
    QtMaterialGridListItem();
    explicit QtMaterialGridListItem(const QString &text);
    ~QtMaterialGridListItem();

    QtMaterialGridListItem *clone() const Q_DECL_OVERRIDE;

    void setSecondaryText(const QString &text);
    QString secondaryText() const;

    void setPixmap(const QPixmap &pixmap);
    QPixmap pixmap() const;

    void setOverlayTextEnabled(bool value);
    bool overlayTextEnabled() const;

private:
    QScopedPointer<QtMaterialGridListItemPrivate> d_ptr;
};

#endif // QTMATERIALGRIDLISTITEM_H
