#include "qtmaterialgridlistitem.h"
#include "qtmaterialgridlistitem_p.h"
#include "qtmaterialgridlist.h"

QtMaterialGridListItem::QtMaterialGridListItem()
    : QStandardItem(),
      d_ptr(new QtMaterialGridListItemPrivate)
{
}

QtMaterialGridListItem::QtMaterialGridListItem(const QString &text)
    : QStandardItem(text),
      d_ptr(new QtMaterialGridListItemPrivate)
{
}

QtMaterialGridListItem::~QtMaterialGridListItem()
{
}

QtMaterialGridListItem *QtMaterialGridListItem::clone() const
{
    QtMaterialGridListItem *item = new QtMaterialGridListItem(text());
    item->setSecondaryText(secondaryText());
    item->setPixmap(pixmap());
    item->setOverlayTextEnabled(overlayTextEnabled());
    item->setToolTip(toolTip());
    item->setStatusTip(statusTip());
    item->setWhatsThis(whatsThis());
    item->setEditable(isEditable());
    item->setCheckable(isCheckable());
    item->setCheckState(checkState());
    item->setEnabled(isEnabled());
    item->setSelectable(isSelectable());
    return item;
}

void QtMaterialGridListItem::setSecondaryText(const QString &text)
{
    setData(text, QtMaterialGridList::SecondaryTextRole);
}

QString QtMaterialGridListItem::secondaryText() const
{
    return data(QtMaterialGridList::SecondaryTextRole).toString();
}

void QtMaterialGridListItem::setPixmap(const QPixmap &pixmap)
{
    setData(pixmap, QtMaterialGridList::PixmapRole);
}

QPixmap QtMaterialGridListItem::pixmap() const
{
    return qvariant_cast<QPixmap>(data(QtMaterialGridList::PixmapRole));
}

void QtMaterialGridListItem::setOverlayTextEnabled(bool value)
{
    setData(value, QtMaterialGridList::OverlayTextRole);
}

bool QtMaterialGridListItem::overlayTextEnabled() const
{
    return data(QtMaterialGridList::OverlayTextRole).toBool();
}
