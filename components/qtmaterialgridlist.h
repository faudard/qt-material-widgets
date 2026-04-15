#ifndef QTMATERIALGRIDLIST_H
#define QTMATERIALGRIDLIST_H

#include <QColor>
#include <QListView>
#include <QScopedPointer>

class QtMaterialGridListPrivate;

class QtMaterialGridList : public QListView
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(int cellWidth READ cellWidth WRITE setCellWidth)
    Q_PROPERTY(int cellHeight READ cellHeight WRITE setCellHeight)
    Q_PROPERTY(int spacing READ spacing WRITE setSpacing)
    Q_PROPERTY(bool showOverlayText READ showOverlayText WRITE setShowOverlayText)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor secondaryTextColor READ secondaryTextColor WRITE setSecondaryTextColor)
    Q_PROPERTY(QColor selectedColor READ selectedColor WRITE setSelectedColor)
    Q_PROPERTY(QColor hoverColor READ hoverColor WRITE setHoverColor)

public:
    enum MaterialGridItemRole {
        SecondaryTextRole = Qt::UserRole + 1,
        PixmapRole,
        OverlayTextRole
    };

    explicit QtMaterialGridList(QWidget *parent = 0);
    ~QtMaterialGridList();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setCellWidth(int value);
    int cellWidth() const;

    void setCellHeight(int value);
    int cellHeight() const;

    void setSpacing(int value);
    int spacing() const;

    void setShowOverlayText(bool value);
    bool showOverlayText() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setSecondaryTextColor(const QColor &color);
    QColor secondaryTextColor() const;

    void setSelectedColor(const QColor &color);
    QColor selectedColor() const;

    void setHoverColor(const QColor &color);
    QColor hoverColor() const;

protected:
    const QScopedPointer<QtMaterialGridListPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialGridList)
    Q_DECLARE_PRIVATE(QtMaterialGridList)
};

#endif // QTMATERIALGRIDLIST_H
