#ifndef QTMATERIALIMAGELIST_H
#define QTMATERIALIMAGELIST_H

#include <QListView>
#include <QColor>
#include <QPixmap>
#include <qstandarditemmodel.h>

class QtMaterialImageListPrivate;

class QtMaterialImageList : public QListView
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(bool masonryMode READ masonryMode WRITE setMasonryMode)
    Q_PROPERTY(bool showOverlayText READ showOverlayText WRITE setShowOverlayText)
    Q_PROPERTY(int columnWidth READ columnWidth WRITE setColumnWidth)
    Q_PROPERTY(int itemSpacing READ itemSpacing WRITE setItemSpacing)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor secondaryTextColor READ secondaryTextColor WRITE setSecondaryTextColor)
    Q_PROPERTY(QColor overlayColor READ overlayColor WRITE setOverlayColor)
    Q_PROPERTY(QColor selectedColor READ selectedColor WRITE setSelectedColor)
    Q_PROPERTY(QColor hoverColor READ hoverColor WRITE setHoverColor)

public:
    explicit QtMaterialImageList(QWidget *parent = 0);
    ~QtMaterialImageList();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setMasonryMode(bool value);
    bool masonryMode() const;

    void setShowOverlayText(bool value);
    bool showOverlayText() const;

    void setColumnWidth(int value);
    int columnWidth() const;

    void setItemSpacing(int value);
    int itemSpacing() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setSecondaryTextColor(const QColor &color);
    QColor secondaryTextColor() const;

    void setOverlayColor(const QColor &color);
    QColor overlayColor() const;

    void setSelectedColor(const QColor &color);
    QColor selectedColor() const;

    void setHoverColor(const QColor &color);
    QColor hoverColor() const;

protected:
    QSize viewportSizeHint() const Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialImageList)
    Q_DECLARE_PRIVATE(QtMaterialImageList)

    QtMaterialImageListPrivate *const d_ptr;
};

class QtMaterialImageListItem : public QStandardItem
{
public:
    explicit QtMaterialImageListItem(const QString &text = QString());

    void setSecondaryText(const QString &text);
    QString secondaryText() const;

    void setPixmap(const QPixmap &pixmap);
    QPixmap pixmap() const;

    void setMasonryHeight(int value);
    int masonryHeight() const;

    void setOverlayTextEnabled(bool value);
    bool overlayTextEnabled() const;

    QStandardItem *clone() const Q_DECL_OVERRIDE;
};

#endif // QTMATERIALIMAGELIST_H
