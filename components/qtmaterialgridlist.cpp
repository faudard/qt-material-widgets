#include "qtmaterialgridlist.h"
#include "qtmaterialgridlist_p.h"

#include <QAbstractItemModel>
#include <QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QPalette>
#include <QStandardItemModel>
#include <QStyledItemDelegate>

namespace {

class QtMaterialGridListDelegate : public QStyledItemDelegate
{
public:
    explicit QtMaterialGridListDelegate(QtMaterialGridList *list)
        : QStyledItemDelegate(list), m_list(list)
    {
    }

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE
    {
        Q_UNUSED(option)
        Q_UNUSED(index)
        return QSize(m_list->cellWidth(), m_list->cellHeight());
    }

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE
    {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing, true);

        const QRect r = option.rect.adjusted(4, 4, -4, -4);
        const bool selected = option.state & QStyle::State_Selected;
        const bool hovered  = option.state & QStyle::State_MouseOver;

        QColor background = m_list->backgroundColor();
        if (selected) {
            background = m_list->selectedColor();
        } else if (hovered) {
            background = m_list->hoverColor();
        }

        painter->setPen(Qt::NoPen);
        painter->setBrush(background);
        painter->drawRoundedRect(r, 4, 4);

        const QString title = index.data(Qt::DisplayRole).toString();
        const QString subtitle = index.data(QtMaterialGridList::SecondaryTextRole).toString();
        const QPixmap pixmap = qvariant_cast<QPixmap>(index.data(QtMaterialGridList::PixmapRole));
        const bool overlay = index.data(QtMaterialGridList::OverlayTextRole).toBool() || m_list->showOverlayText();

        QRect textRect = r.adjusted(12, 12, -12, -12);
        const bool hasImage = !pixmap.isNull();
        QRect imageRect;

        if (hasImage) {
            imageRect = QRect(r.left() + 8, r.top() + 8, r.width() - 16, qMax(72, r.height() / 2));
            QPixmap scaled = pixmap.scaled(imageRect.size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
            painter->setClipRect(imageRect);
            painter->drawPixmap(imageRect.topLeft(), scaled, QRect(QPoint(0, 0), imageRect.size()));
            painter->setClipping(false);

            if (overlay) {
                QRect overlayRect(imageRect.left(), imageRect.bottom() - 40, imageRect.width(), 40);
                painter->fillRect(overlayRect, QColor(0, 0, 0, 110));
                painter->setPen(Qt::white);
                painter->drawText(overlayRect.adjusted(8, 0, -8, 0), Qt::AlignVCenter | Qt::AlignLeft,
                                  QFontMetrics(option.font).elidedText(title, Qt::ElideRight, overlayRect.width() - 16));
                textRect = QRect(r.left() + 12, imageRect.bottom() + 8, r.width() - 24, r.bottom() - imageRect.bottom() - 20);
            } else {
                textRect = QRect(r.left() + 12, imageRect.bottom() + 12, r.width() - 24, r.bottom() - imageRect.bottom() - 20);
            }
        }

        painter->setPen(m_list->textColor());
        QFont titleFont = option.font;
        titleFont.setBold(true);
        painter->setFont(titleFont);

        QRect primaryRect = textRect;
        if (!subtitle.isEmpty()) {
            primaryRect.setHeight(qMin(24, textRect.height() / 2));
        }

        painter->drawText(primaryRect, Qt::AlignLeft | Qt::AlignTop | Qt::TextWordWrap,
                          QFontMetrics(titleFont).elidedText(title, Qt::ElideRight, primaryRect.width()));

        if (!subtitle.isEmpty() && (!overlay || !hasImage)) {
            painter->setPen(m_list->secondaryTextColor());
            QFont subtitleFont = option.font;
            subtitleFont.setPointSize(qMax(8, subtitleFont.pointSize() - 1));
            painter->setFont(subtitleFont);
            QRect secondaryRect = textRect.adjusted(0, primaryRect.height() + 4, 0, 0);
            painter->drawText(secondaryRect, Qt::AlignLeft | Qt::AlignTop | Qt::TextWordWrap,
                              QFontMetrics(subtitleFont).elidedText(subtitle, Qt::ElideRight, secondaryRect.width()));
        }

        painter->restore();
    }

private:
    QtMaterialGridList *const m_list;
};

static QColor fallbackColor(const QWidget *widget, const QPalette::ColorRole &role, const QColor &fallback)
{
    if (!widget) {
        return fallback;
    }
    QColor color = widget->palette().color(role);
    return color.isValid() ? color : fallback;
}

}

QtMaterialGridListPrivate::QtMaterialGridListPrivate(QtMaterialGridList *q)
    : q_ptr(q),
      delegate(0),
      useThemeColors(true),
      showOverlayText(false),
      cellWidth(180),
      cellHeight(200),
      itemSpacing(12)
{
}

QtMaterialGridListPrivate::~QtMaterialGridListPrivate()
{
}

void QtMaterialGridListPrivate::init()
{
    Q_Q(QtMaterialGridList);

    delegate = new QtMaterialGridListDelegate(q);

    q->setViewMode(QListView::IconMode);
    q->setResizeMode(QListView::Adjust);
    q->setMovement(QListView::Static);
    q->setWrapping(true);
    q->setMouseTracking(true);
    q->setSelectionRectVisible(false);
    q->setUniformItemSizes(true);
    q->setItemDelegate(delegate);
    q->setFrameShape(QFrame::NoFrame);
    q->setSelectionMode(QAbstractItemView::SingleSelection);

    updateMetrics();
}

void QtMaterialGridListPrivate::updateMetrics()
{
    Q_Q(QtMaterialGridList);
    q->setGridSize(QSize(cellWidth + itemSpacing, cellHeight + itemSpacing));
    // q->setSpacing(itemSpacing); // TODO crash here
    q->viewport()->update();
}

QtMaterialGridList::QtMaterialGridList(QWidget *parent)
    : QListView(parent),
      d_ptr(new QtMaterialGridListPrivate(this))
{
    d_func()->init();
}

QtMaterialGridList::~QtMaterialGridList()
{
}

void QtMaterialGridList::setUseThemeColors(bool value)
{
    Q_D(QtMaterialGridList);
    if (d->useThemeColors == value) {
        return;
    }
    d->useThemeColors = value;
    viewport()->update();
}

bool QtMaterialGridList::useThemeColors() const
{
    Q_D(const QtMaterialGridList);
    return d->useThemeColors;
}

void QtMaterialGridList::setCellWidth(int value)
{
    Q_D(QtMaterialGridList);
    d->cellWidth = qMax(80, value);
    d->updateMetrics();
}

int QtMaterialGridList::cellWidth() const
{
    Q_D(const QtMaterialGridList);
    return d->cellWidth;
}

void QtMaterialGridList::setCellHeight(int value)
{
    Q_D(QtMaterialGridList);
    d->cellHeight = qMax(80, value);
    d->updateMetrics();
}

int QtMaterialGridList::cellHeight() const
{
    Q_D(const QtMaterialGridList);
    return d->cellHeight;
}

void QtMaterialGridList::setSpacing(int value)
{
    Q_D(QtMaterialGridList);
    d->itemSpacing = qMax(0, value);
    d->updateMetrics();
}

int QtMaterialGridList::spacing() const
{
    Q_D(const QtMaterialGridList);
    return d->itemSpacing;
}

void QtMaterialGridList::setShowOverlayText(bool value)
{
    Q_D(QtMaterialGridList);
    d->showOverlayText = value;
    viewport()->update();
}

bool QtMaterialGridList::showOverlayText() const
{
    Q_D(const QtMaterialGridList);
    return d->showOverlayText;
}

void QtMaterialGridList::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialGridList);
    d->backgroundColor = color;
    d->useThemeColors = false;
    viewport()->update();
}

QColor QtMaterialGridList::backgroundColor() const
{
    Q_D(const QtMaterialGridList);
    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return fallbackColor(this, QPalette::Base, QColor(250, 250, 250));
    }
    return d->backgroundColor;
}

void QtMaterialGridList::setTextColor(const QColor &color)
{
    Q_D(QtMaterialGridList);
    d->textColor = color;
    d->useThemeColors = false;
    viewport()->update();
}

QColor QtMaterialGridList::textColor() const
{
    Q_D(const QtMaterialGridList);
    if (d->useThemeColors || !d->textColor.isValid()) {
        return fallbackColor(this, QPalette::Text, QColor(33, 33, 33));
    }
    return d->textColor;
}

void QtMaterialGridList::setSecondaryTextColor(const QColor &color)
{
    Q_D(QtMaterialGridList);
    d->secondaryTextColor = color;
    d->useThemeColors = false;
    viewport()->update();
}

QColor QtMaterialGridList::secondaryTextColor() const
{
    Q_D(const QtMaterialGridList);
    if (d->useThemeColors || !d->secondaryTextColor.isValid()) {
        return QColor(117, 117, 117);
    }
    return d->secondaryTextColor;
}

void QtMaterialGridList::setSelectedColor(const QColor &color)
{
    Q_D(QtMaterialGridList);
    d->selectedColor = color;
    d->useThemeColors = false;
    viewport()->update();
}

QColor QtMaterialGridList::selectedColor() const
{
    Q_D(const QtMaterialGridList);
    if (d->useThemeColors || !d->selectedColor.isValid()) {
        return QColor(225, 245, 254);
    }
    return d->selectedColor;
}

void QtMaterialGridList::setHoverColor(const QColor &color)
{
    Q_D(QtMaterialGridList);
    d->hoverColor = color;
    d->useThemeColors = false;
    viewport()->update();
}

QColor QtMaterialGridList::hoverColor() const
{
    Q_D(const QtMaterialGridList);
    if (d->useThemeColors || !d->hoverColor.isValid()) {
        return QColor(245, 245, 245);
    }
    return d->hoverColor;
}
