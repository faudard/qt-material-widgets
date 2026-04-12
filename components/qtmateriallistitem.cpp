#include "qtmateriallistitem.h"
#include "qtmateriallistitem_p.h"

#include "qtmateriallist.h"

QtMaterialListItem::QtMaterialListItem()
    : QStandardItem()
{
    init();
}

QtMaterialListItem::QtMaterialListItem(const QString &text,
                                       const QString &secondaryText)
    : QStandardItem(text)
{
    init();
    setSecondaryText(secondaryText);
}

QtMaterialListItem::QtMaterialListItem(const QIcon &icon,
                                       const QString &text,
                                       const QString &secondaryText)
    : QStandardItem(icon, text)
{
    init();
    setSecondaryText(secondaryText);
}

QtMaterialListItem::~QtMaterialListItem()
{
}

QStandardItem *QtMaterialListItem::clone() const
{
    return new QtMaterialListItem(*this);
}

void QtMaterialListItem::setPrimaryText(const QString &text)
{
    setText(text);
}

QString QtMaterialListItem::primaryText() const
{
    return text();
}

void QtMaterialListItem::setSecondaryText(const QString &text)
{
    setData(text, QtMaterialList::SecondaryTextRole);
}

QString QtMaterialListItem::secondaryText() const
{
    return data(QtMaterialList::SecondaryTextRole).toString();
}

void QtMaterialListItem::setTrailingText(const QString &text)
{
    setData(text, QtMaterialList::TrailingTextRole);
}

QString QtMaterialListItem::trailingText() const
{
    return data(QtMaterialList::TrailingTextRole).toString();
}

void QtMaterialListItem::setDivider(bool value)
{
    setData(value, QtMaterialList::DividerRole);
}

bool QtMaterialListItem::divider() const
{
    return data(QtMaterialList::DividerRole).toBool();
}

void QtMaterialListItem::setFullWidthDivider(bool value)
{
    setData(value, QtMaterialList::FullWidthDividerRole);
}

bool QtMaterialListItem::fullWidthDivider() const
{
    return data(QtMaterialList::FullWidthDividerRole).toBool();
}

void QtMaterialListItem::setAvatarText(const QString &text)
{
    setData(text.left(2).toUpper(), QtMaterialList::AvatarTextRole);
}

QString QtMaterialListItem::avatarText() const
{
    return data(QtMaterialList::AvatarTextRole).toString();
}

void QtMaterialListItem::setAvatarColor(const QColor &color)
{
    setData(color, QtMaterialList::AvatarColorRole);
}

QColor QtMaterialListItem::avatarColor() const
{
    return data(QtMaterialList::AvatarColorRole).value<QColor>();
}

void QtMaterialListItem::setAvatarPixmap(const QPixmap &pixmap)
{
    setData(pixmap, QtMaterialList::AvatarPixmapRole);
}

QPixmap QtMaterialListItem::avatarPixmap() const
{
    return qvariant_cast<QPixmap>(data(QtMaterialList::AvatarPixmapRole));
}

void QtMaterialListItem::setAvatar(const QString &text, const QColor &color)
{
    setAvatarText(text);
    setAvatarColor(color);
}

void QtMaterialListItem::clearAvatar()
{
    setData(QVariant(), QtMaterialList::AvatarTextRole);
    setData(QVariant(), QtMaterialList::AvatarColorRole);
    setData(QVariant(), QtMaterialList::AvatarPixmapRole);
}

void QtMaterialListItem::init()
{
    setEditable(false);
    setSelectable(true);
    setEnabled(true);
}
