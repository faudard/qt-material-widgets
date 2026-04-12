#ifndef QTMATERIALLISTITEM_H
#define QTMATERIALLISTITEM_H

#include <QColor>
#include <QIcon>
#include <QPixmap>
#include <QStandardItem>

class QtMaterialListItemPrivate;

class QtMaterialListItem : public QStandardItem
{
public:
    QtMaterialListItem();
    explicit QtMaterialListItem(const QString &text,
                                const QString &secondaryText = QString());
    QtMaterialListItem(const QIcon &icon,
                       const QString &text,
                       const QString &secondaryText = QString());
    ~QtMaterialListItem();

    QStandardItem *clone() const Q_DECL_OVERRIDE;

    void setPrimaryText(const QString &text);
    QString primaryText() const;

    void setSecondaryText(const QString &text);
    QString secondaryText() const;

    void setTrailingText(const QString &text);
    QString trailingText() const;

    void setDivider(bool value);
    bool divider() const;

    void setFullWidthDivider(bool value);
    bool fullWidthDivider() const;

    void setAvatarText(const QString &text);
    QString avatarText() const;

    void setAvatarColor(const QColor &color);
    QColor avatarColor() const;

    void setAvatarPixmap(const QPixmap &pixmap);
    QPixmap avatarPixmap() const;

    void setAvatar(const QString &text, const QColor &color);
    void clearAvatar();

private:
    void init();
};

#endif // QTMATERIALLISTITEM_H
