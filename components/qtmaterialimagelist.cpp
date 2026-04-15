#include "qtmaterialimagelist.h"
#include "qtmaterialimagelist_p.h"
#include "lib/qtmaterialstyle.h"

#include <QPainter>
#include <QPainterPath>
#include <QStandardItemModel>
#include <QApplication>

namespace {
enum MaterialImageListRole {
    SecondaryTextRole = Qt::UserRole + 1,
    PixmapRole,
    MasonryHeightRole,
    OverlayTextRole
};
}

QtMaterialImageListDelegate::QtMaterialImageListDelegate(QtMaterialImageList *parent)
    : QStyledItemDelegate(parent),
      m_list(parent)
{
}

QSize QtMaterialImageListDelegate::sizeHint(const QStyleOptionViewItem &,
                                            const QModelIndex &index) const
{
    const int width = m_list->columnWidth();
    const int imageHeight = qMax(72, index.data(MasonryHeightRole).toInt());
    const int footer = m_list->showOverlayText() ? 0 : 56;
    return QSize(width, imageHeight + footer);
}

void QtMaterialImageListDelegate::paint(QPainter *painter,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);

    QRect r = option.rect.adjusted(4, 4, -4, -4);
    QPainterPath path;
    path.addRoundedRect(r, 4, 4);
    painter->setClipPath(path);

    QColor bg = m_list->backgroundColor();
    if (option.state & QStyle::State_MouseOver) {
        bg = m_list->hoverColor();
    }
    if (option.state & QStyle::State_Selected) {
        bg = m_list->selectedColor();
    }
    painter->fillRect(r, bg);

    QPixmap px = index.data(PixmapRole).value<QPixmap>();
    QRect imageRect = r;
    if (!m_list->showOverlayText()) {
        imageRect.setBottom(r.bottom() - 56);
    }

    if (!px.isNull()) {
        painter->drawPixmap(imageRect, px.scaled(imageRect.size(),
                                                Qt::KeepAspectRatioByExpanding,
                                                Qt::SmoothTransformation));
    } else {
        painter->fillRect(imageRect, bg.darker(106));
    }

    const QString title = index.data(Qt::DisplayRole).toString();
    const QString subtitle = index.data(SecondaryTextRole).toString();
    const bool overlay = index.data(OverlayTextRole).toBool() || m_list->showOverlayText();

    if (overlay) {
        QRect overlayRect = QRect(r.left(), r.bottom() - 48, r.width(), 48);
        painter->fillRect(overlayRect, m_list->overlayColor());
        painter->setPen(Qt::white);
        painter->drawText(overlayRect.adjusted(12, 8, -12, -22),
                          Qt::AlignLeft | Qt::AlignVCenter,
                          title);
        painter->setPen(QColor(255, 255, 255, 180));
        painter->drawText(overlayRect.adjusted(12, 24, -12, -6),
                          Qt::AlignLeft | Qt::AlignVCenter,
                          subtitle);
    } else {
        QRect footerRect = QRect(r.left(), r.bottom() - 56, r.width(), 56);
        painter->fillRect(footerRect, bg);
        painter->setPen(m_list->textColor());
        painter->drawText(footerRect.adjusted(12, 8, -12, -22),
                          Qt::AlignLeft | Qt::AlignVCenter,
                          title);
        painter->setPen(m_list->secondaryTextColor());
        painter->drawText(footerRect.adjusted(12, 24, -12, -6),
                          Qt::AlignLeft | Qt::AlignVCenter,
                          subtitle);
    }

    painter->restore();
}

QtMaterialImageListPrivate::QtMaterialImageListPrivate(QtMaterialImageList *q)
    : q_ptr(q),
      delegate(0),
      useThemeColors(true),
      masonryMode(false),
      showOverlayText(true),
      columnWidth(180),
      itemSpacing(12)
{
}

QtMaterialImageListPrivate::~QtMaterialImageListPrivate()
{
}

void QtMaterialImageListPrivate::init()
{
    Q_Q(QtMaterialImageList);

    delegate = new QtMaterialImageListDelegate(q);
    q->setItemDelegate(delegate);
    q->setViewMode(QListView::IconMode);
    q->setFlow(QListView::LeftToRight);
    q->setResizeMode(QListView::Adjust);
    q->setWrapping(true);
    q->setSpacing(itemSpacing);
    q->setMouseTracking(true);
    q->setSelectionMode(QAbstractItemView::SingleSelection);
    q->setUniformItemSizes(false);
    q->setGridSize(QSize(columnWidth + itemSpacing, 220));

    if (!q->model()) {
        q->setModel(new QStandardItemModel(q));
    }
}

QtMaterialImageList::QtMaterialImageList(QWidget *parent)
    : QListView(parent),
      d_ptr(new QtMaterialImageListPrivate(this))
{
    d_ptr->init();
}

QtMaterialImageList::~QtMaterialImageList()
{
    delete d_ptr;
}

void QtMaterialImageList::setUseThemeColors(bool value)
{
    Q_D(QtMaterialImageList);
    d->useThemeColors = value;
    viewport()->update();
}

bool QtMaterialImageList::useThemeColors() const
{
    Q_D(const QtMaterialImageList);
    return d->useThemeColors;
}

void QtMaterialImageList::setMasonryMode(bool value)
{
    Q_D(QtMaterialImageList);
    d->masonryMode = value;
    doItemsLayout();
}

bool QtMaterialImageList::masonryMode() const
{
    Q_D(const QtMaterialImageList);
    return d->masonryMode;
}

void QtMaterialImageList::setShowOverlayText(bool value)
{
    Q_D(QtMaterialImageList);
    d->showOverlayText = value;
    viewport()->update();
}

bool QtMaterialImageList::showOverlayText() const
{
    Q_D(const QtMaterialImageList);
    return d->showOverlayText;
}

void QtMaterialImageList::setColumnWidth(int value)
{
    Q_D(QtMaterialImageList);
    d->columnWidth = value;
    setGridSize(QSize(value + d->itemSpacing, 220));
    doItemsLayout();
}

int QtMaterialImageList::columnWidth() const
{
    Q_D(const QtMaterialImageList);
    return d->columnWidth;
}

void QtMaterialImageList::setItemSpacing(int value)
{
    Q_D(QtMaterialImageList);
    d->itemSpacing = value;
    setSpacing(value);
    doItemsLayout();
}

int QtMaterialImageList::itemSpacing() const
{
    Q_D(const QtMaterialImageList);
    return d->itemSpacing;
}

void QtMaterialImageList::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialImageList);
    d->backgroundColor = color;
    d->useThemeColors = false;
    viewport()->update();
}

QColor QtMaterialImageList::backgroundColor() const
{
    Q_D(const QtMaterialImageList);
    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("canvas");
    }
    return d->backgroundColor;
}

void QtMaterialImageList::setTextColor(const QColor &color)
{
    Q_D(QtMaterialImageList);
    d->textColor = color;
    d->useThemeColors = false;
    viewport()->update();
}

QColor QtMaterialImageList::textColor() const
{
    Q_D(const QtMaterialImageList);
    if (d->useThemeColors || !d->textColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("text");
    }
    return d->textColor;
}

void QtMaterialImageList::setSecondaryTextColor(const QColor &color)
{
    Q_D(QtMaterialImageList);
    d->secondaryTextColor = color;
    d->useThemeColors = false;
    viewport()->update();
}

QColor QtMaterialImageList::secondaryTextColor() const
{
    Q_D(const QtMaterialImageList);
    if (d->useThemeColors || !d->secondaryTextColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("accent1");
    }
    return d->secondaryTextColor;
}

void QtMaterialImageList::setOverlayColor(const QColor &color)
{
    Q_D(QtMaterialImageList);
    d->overlayColor = color;
    d->useThemeColors = false;
    viewport()->update();
}

QColor QtMaterialImageList::overlayColor() const
{
    Q_D(const QtMaterialImageList);
    if (d->useThemeColors || !d->overlayColor.isValid()) {
        return QColor(0, 0, 0, 140);
    }
    return d->overlayColor;
}

void QtMaterialImageList::setSelectedColor(const QColor &color)
{
    Q_D(QtMaterialImageList);
    d->selectedColor = color;
    d->useThemeColors = false;
    viewport()->update();
}

QColor QtMaterialImageList::selectedColor() const
{
    Q_D(const QtMaterialImageList);
    if (d->useThemeColors || !d->selectedColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("primary1").lighter(160);
    }
    return d->selectedColor;
}

void QtMaterialImageList::setHoverColor(const QColor &color)
{
    Q_D(QtMaterialImageList);
    d->hoverColor = color;
    d->useThemeColors = false;
    viewport()->update();
}

QColor QtMaterialImageList::hoverColor() const
{
    Q_D(const QtMaterialImageList);
    if (d->useThemeColors || !d->hoverColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("border");
    }
    return d->hoverColor;
}

QSize QtMaterialImageList::viewportSizeHint() const
{
    Q_D(const QtMaterialImageList);
    return QSize(d->columnWidth * 3 + d->itemSpacing * 4, 420);
}

QtMaterialImageListItem::QtMaterialImageListItem(const QString &text)
    : QStandardItem(text)
{
}

void QtMaterialImageListItem::setSecondaryText(const QString &text)
{
    setData(text, SecondaryTextRole);
}

QString QtMaterialImageListItem::secondaryText() const
{
    return data(SecondaryTextRole).toString();
}

void QtMaterialImageListItem::setPixmap(const QPixmap &pixmap)
{
    setData(pixmap, PixmapRole);
}

QPixmap QtMaterialImageListItem::pixmap() const
{
    return data(PixmapRole).value<QPixmap>();
}

void QtMaterialImageListItem::setMasonryHeight(int value)
{
    setData(value, MasonryHeightRole);
}

int QtMaterialImageListItem::masonryHeight() const
{
    return data(MasonryHeightRole).toInt();
}

void QtMaterialImageListItem::setOverlayTextEnabled(bool value)
{
    setData(value, OverlayTextRole);
}

bool QtMaterialImageListItem::overlayTextEnabled() const
{
    return data(OverlayTextRole).toBool();
}

QStandardItem *QtMaterialImageListItem::clone() const
{
    return new QtMaterialImageListItem(*this);
}
