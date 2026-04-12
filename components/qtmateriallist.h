#ifndef QTMATERIALLIST_H
#define QTMATERIALLIST_H

#include <QColor>
#include <QListView>
#include <QScopedPointer>

class QtMaterialListPrivate;

class QtMaterialList : public QListView
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors WRITE setUseThemeColors READ useThemeColors)
    Q_PROPERTY(bool dense WRITE setDense READ isDense)
    Q_PROPERTY(bool showDivider WRITE setShowDivider READ showDivider)
    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
    Q_PROPERTY(QColor secondaryTextColor WRITE setSecondaryTextColor READ secondaryTextColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor dividerColor WRITE setDividerColor READ dividerColor)
    Q_PROPERTY(QColor selectedColor WRITE setSelectedColor READ selectedColor)
    Q_PROPERTY(QColor hoverColor WRITE setHoverColor READ hoverColor)

public:
    enum ItemDataRole {
        SecondaryTextRole = Qt::UserRole + 1200,
        DividerRole,
        FullWidthDividerRole,
        TrailingTextRole,
        AvatarTextRole,
        AvatarColorRole,
        AvatarPixmapRole
    };

    explicit QtMaterialList(QWidget *parent = 0);
    ~QtMaterialList();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setDense(bool value);
    bool isDense() const;

    void setShowDivider(bool value);
    bool showDivider() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setSecondaryTextColor(const QColor &color);
    QColor secondaryTextColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setDividerColor(const QColor &color);
    QColor dividerColor() const;

    void setSelectedColor(const QColor &color);
    QColor selectedColor() const;

    void setHoverColor(const QColor &color);
    QColor hoverColor() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialListPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialList)
    Q_DECLARE_PRIVATE(QtMaterialList)
};

#endif // QTMATERIALLIST_H
