#include "qtmaterialtreeitem.h"
#include "qtmaterialtreeitem_p.h"

#include "qtmaterialtree.h"

QtMaterialTreeItem::QtMaterialTreeItem()
    : QStandardItem()
{
    init();
}

QtMaterialTreeItem::QtMaterialTreeItem(const QString &text,
                                       const QString &secondaryText)
    : QStandardItem(text)
{
    init();
    setSecondaryText(secondaryText);
}

QtMaterialTreeItem::QtMaterialTreeItem(const QIcon &icon,
                                       const QString &text,
                                       const QString &secondaryText)
    : QStandardItem(icon, text)
{
    init();
    setSecondaryText(secondaryText);
}

QtMaterialTreeItem::~QtMaterialTreeItem()
{
}

QStandardItem *QtMaterialTreeItem::clone() const
{
    return new QtMaterialTreeItem(*this);
}

void QtMaterialTreeItem::setPrimaryText(const QString &text)
{
    setText(text);
}

QString QtMaterialTreeItem::primaryText() const
{
    return text();
}

void QtMaterialTreeItem::setSecondaryText(const QString &text)
{
    setData(text, QtMaterialTree::SecondaryTextRole);
}

QString QtMaterialTreeItem::secondaryText() const
{
    return data(QtMaterialTree::SecondaryTextRole).toString();
}

void QtMaterialTreeItem::setTrailingText(const QString &text)
{
    setData(text, QtMaterialTree::TrailingTextRole);
}

QString QtMaterialTreeItem::trailingText() const
{
    return data(QtMaterialTree::TrailingTextRole).toString();
}

void QtMaterialTreeItem::setDivider(bool value)
{
    setData(value, QtMaterialTree::DividerRole);
}

bool QtMaterialTreeItem::divider() const
{
    return data(QtMaterialTree::DividerRole).toBool();
}

void QtMaterialTreeItem::setFullWidthDivider(bool value)
{
    setData(value, QtMaterialTree::FullWidthDividerRole);
}

bool QtMaterialTreeItem::fullWidthDivider() const
{
    return data(QtMaterialTree::FullWidthDividerRole).toBool();
}

void QtMaterialTreeItem::setAvatarText(const QString &text)
{
    setData(text.left(2).toUpper(), QtMaterialTree::AvatarTextRole);
}

QString QtMaterialTreeItem::avatarText() const
{
    return data(QtMaterialTree::AvatarTextRole).toString();
}

void QtMaterialTreeItem::setAvatarColor(const QColor &color)
{
    setData(color, QtMaterialTree::AvatarColorRole);
}

QColor QtMaterialTreeItem::avatarColor() const
{
    return data(QtMaterialTree::AvatarColorRole).value<QColor>();
}

void QtMaterialTreeItem::setAvatarPixmap(const QPixmap &pixmap)
{
    setData(pixmap, QtMaterialTree::AvatarPixmapRole);
}

QPixmap QtMaterialTreeItem::avatarPixmap() const
{
    return qvariant_cast<QPixmap>(data(QtMaterialTree::AvatarPixmapRole));
}

void QtMaterialTreeItem::setAvatar(const QString &text, const QColor &color)
{
    setAvatarText(text);
    setAvatarColor(color);
}

void QtMaterialTreeItem::clearAvatar()
{
    setData(QVariant(), QtMaterialTree::AvatarTextRole);
    setData(QVariant(), QtMaterialTree::AvatarColorRole);
    setData(QVariant(), QtMaterialTree::AvatarPixmapRole);
}

void QtMaterialTreeItem::init()
{
    setEditable(false);
    setSelectable(true);
    setEnabled(true);
}
