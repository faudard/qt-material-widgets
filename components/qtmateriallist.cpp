#include "qtmateriallist.h"
#include "qtmateriallist_p.h"

#include <QAbstractItemModel>
#include <QCursor>
#include <QEvent>
#include <QFrame>
#include <QIcon>
#include <QPainter>
#include <QPixmap>
#include <QStyledItemDelegate>

#include "lib/qtmaterialstyle.h"

class QtMaterialListDelegate : public QStyledItemDelegate
{
public:
    explicit QtMaterialListDelegate(QtMaterialList *parent)
        : QStyledItemDelegate(parent),
          m_list(parent)
    {
    }

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE
    {
        if (!painter) {
            return;
        }

        QStyleOptionViewItem opt(option);
        initStyleOption(&opt, index);

        const QRect rect = option.rect;
        const bool selected = opt.state & QStyle::State_Selected;
        const bool hovered = isHovered(index);
        const bool enabled = m_list->isEnabled() && (index.flags() & Qt::ItemIsEnabled);

        QColor background = m_list->backgroundColor();
        if (selected) {
            background = m_list->selectedColor();
        } else if (hovered) {
            background = m_list->hoverColor();
        }

        painter->save();
        painter->fillRect(rect, background);

        const QVariant decorationValue = index.data(Qt::DecorationRole);
        const bool hasDecoration = decorationValue.isValid() && !decorationValue.isNull();
        const int leftPadding = 16;
        const int rightPadding = 16;
        const int iconTextSpacing = 16;
        const QSize iconSize = m_list->iconSize().isValid() ? m_list->iconSize() : QSize(24, 24);

        QRect iconRect;
        int textLeft = rect.left() + leftPadding;

        if (hasDecoration) {
            iconRect = QRect(textLeft,
                             rect.top() + (rect.height() - iconSize.height()) / 2,
                             iconSize.width(),
                             iconSize.height());
            drawDecoration(painter, decorationValue, iconRect, enabled);
            textLeft = iconRect.right() + iconTextSpacing;
        }

        const QString primaryText = index.data(Qt::DisplayRole).toString();
        const QString secondaryText = index.data(QtMaterialList::SecondaryTextRole).toString();
        const bool twoLine = !secondaryText.trimmed().isEmpty();

        QFont primaryFont(m_list->font());
        QFont secondaryFont(m_list->font());
        secondaryFont.setPointSizeF(qMax<qreal>(secondaryFont.pointSizeF() - 1, 9));

        const QColor primaryColor = enabled
            ? m_list->textColor()
            : QtMaterialStyle::instance().themeColor("disabled");
        const QColor secondaryColor = enabled
            ? m_list->secondaryTextColor()
            : QtMaterialStyle::instance().themeColor("disabled");

        QRect textRect(textLeft,
                       rect.top(),
                       rect.width() - (textLeft - rect.left()) - rightPadding,
                       rect.height());

        if (twoLine) {
            const int topPadding = m_list->isDense() ? 8 : 12;
            const int primaryHeight = m_list->isDense() ? 18 : 20;
            QRect primaryRect(textRect.left(),
                              rect.top() + topPadding,
                              textRect.width(),
                              primaryHeight);
            QRect secondaryRect(textRect.left(),
                                primaryRect.bottom() + 2,
                                textRect.width(),
                                rect.bottom() - (primaryRect.bottom() + 2) - 8);

            painter->setFont(primaryFont);
            painter->setPen(primaryColor);
            painter->drawText(primaryRect,
                              Qt::AlignLeft | Qt::AlignVCenter | Qt::TextSingleLine,
                              QFontMetrics(primaryFont).elidedText(primaryText,
                                                                   Qt::ElideRight,
                                                                   primaryRect.width()));

            painter->setFont(secondaryFont);
            painter->setPen(secondaryColor);
            painter->drawText(secondaryRect,
                              Qt::AlignLeft | Qt::AlignTop | Qt::TextSingleLine,
                              QFontMetrics(secondaryFont).elidedText(secondaryText,
                                                                     Qt::ElideRight,
                                                                     secondaryRect.width()));
        } else {
            painter->setFont(primaryFont);
            painter->setPen(primaryColor);
            painter->drawText(textRect,
                              Qt::AlignLeft | Qt::AlignVCenter | Qt::TextSingleLine,
                              QFontMetrics(primaryFont).elidedText(primaryText,
                                                                   Qt::ElideRight,
                                                                   textRect.width()));
        }

        if (shouldDrawDivider(index)) {
            const bool fullWidth = index.data(QtMaterialList::FullWidthDividerRole).toBool();
            const int dividerLeft = fullWidth ? rect.left() : textLeft;
            painter->setPen(m_list->dividerColor());
            painter->drawLine(QPoint(dividerLeft, rect.bottom()),
                              QPoint(rect.right() - rightPadding, rect.bottom()));
        }

        painter->restore();
    }

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE
    {
        Q_UNUSED(option)

        const bool twoLine = !index.data(QtMaterialList::SecondaryTextRole).toString().trimmed().isEmpty();
        const int height = twoLine
            ? (m_list->isDense() ? 60 : 72)
            : (m_list->isDense() ? 40 : 48);

        return QSize(0, height);
    }

private:
    bool isHovered(const QModelIndex &index) const
    {
        const QPoint pos = m_list->viewport()->mapFromGlobal(QCursor::pos());

        if (!m_list->viewport()->rect().contains(pos)) {
            return false;
        }

        const QModelIndex hovered = m_list->indexAt(pos);
        return hovered.isValid() && hovered.row() == index.row();
    }

    bool shouldDrawDivider(const QModelIndex &index) const
    {
        const QVariant dividerValue = index.data(QtMaterialList::DividerRole);
        return dividerValue.isValid() ? dividerValue.toBool() : m_list->showDivider();
    }

    void drawDecoration(QPainter *painter,
                        const QVariant &value,
                        const QRect &rect,
                        bool enabled) const
    {
        if (value.canConvert<QIcon>()) {
            const QIcon icon = qvariant_cast<QIcon>(value);
            icon.paint(painter, rect, Qt::AlignCenter,
                       enabled ? QIcon::Normal : QIcon::Disabled);
            return;
        }

        if (value.canConvert<QPixmap>()) {
            const QPixmap pixmap = qvariant_cast<QPixmap>(value);
            painter->drawPixmap(rect,
                                pixmap.scaled(rect.size(),
                                              Qt::KeepAspectRatio,
                                              Qt::SmoothTransformation));
            return;
        }

        if (value.canConvert<QColor>()) {
            painter->save();
            painter->setRenderHint(QPainter::Antialiasing);
            painter->setPen(Qt::NoPen);
            painter->setBrush(qvariant_cast<QColor>(value));
            painter->drawEllipse(rect);
            painter->restore();
        }
    }

    QtMaterialList *const m_list;
};

/*!
 * \class QtMaterialListPrivate
 * \internal
 */

QtMaterialListPrivate::QtMaterialListPrivate(QtMaterialList *q)
    : q_ptr(q)
{
}

QtMaterialListPrivate::~QtMaterialListPrivate()
{
}

void QtMaterialListPrivate::init()
{
    Q_Q(QtMaterialList);

    useThemeColors = true;
    dense = false;
    showDivider = true;

    q->setFrameShape(QFrame::NoFrame);
    q->setSpacing(0);
    q->setMouseTracking(true);
    q->setUniformItemSizes(false);
    q->setSelectionMode(QAbstractItemView::SingleSelection);
    q->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    q->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    q->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    q->setEditTriggers(QAbstractItemView::NoEditTriggers);
    q->setResizeMode(QListView::Adjust);
    q->setMovement(QListView::Static);
    q->viewport()->setAttribute(Qt::WA_Hover, true);
    q->viewport()->installEventFilter(q);
    q->setItemDelegate(new QtMaterialListDelegate(q));
    q->setIconSize(QSize(24, 24));
}

/*!
 * \class QtMaterialList
 */

QtMaterialList::QtMaterialList(QWidget *parent)
    : QListView(parent),
      d_ptr(new QtMaterialListPrivate(this))
{
    d_func()->init();
}

QtMaterialList::~QtMaterialList()
{
}

void QtMaterialList::setUseThemeColors(bool value)
{
    Q_D(QtMaterialList);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    viewport()->update();
}

bool QtMaterialList::useThemeColors() const
{
    Q_D(const QtMaterialList);
    return d->useThemeColors;
}

void QtMaterialList::setDense(bool value)
{
    Q_D(QtMaterialList);

    if (d->dense == value) {
        return;
    }

    d->dense = value;
    doItemsLayout();
    viewport()->update();
}

bool QtMaterialList::isDense() const
{
    Q_D(const QtMaterialList);
    return d->dense;
}

void QtMaterialList::setShowDivider(bool value)
{
    Q_D(QtMaterialList);

    if (d->showDivider == value) {
        return;
    }

    d->showDivider = value;
    viewport()->update();
}

bool QtMaterialList::showDivider() const
{
    Q_D(const QtMaterialList);
    return d->showDivider;
}

void QtMaterialList::setTextColor(const QColor &color)
{
    Q_D(QtMaterialList);
    d->textColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    viewport()->update();
}

QColor QtMaterialList::textColor() const
{
    Q_D(const QtMaterialList);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("text");
    } else {
        return d->textColor;
    }
}

void QtMaterialList::setSecondaryTextColor(const QColor &color)
{
    Q_D(QtMaterialList);
    d->secondaryTextColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    viewport()->update();
}

QColor QtMaterialList::secondaryTextColor() const
{
    Q_D(const QtMaterialList);

    if (d->useThemeColors || !d->secondaryTextColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("accent3");
    } else {
        return d->secondaryTextColor;
    }
}

void QtMaterialList::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialList);
    d->backgroundColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    viewport()->update();
}

QColor QtMaterialList::backgroundColor() const
{
    Q_D(const QtMaterialList);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("canvas");
    } else {
        return d->backgroundColor;
    }
}

void QtMaterialList::setDividerColor(const QColor &color)
{
    Q_D(QtMaterialList);
    d->dividerColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    viewport()->update();
}

QColor QtMaterialList::dividerColor() const
{
    Q_D(const QtMaterialList);

    if (d->useThemeColors || !d->dividerColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("border");
    } else {
        return d->dividerColor;
    }
}

void QtMaterialList::setSelectedColor(const QColor &color)
{
    Q_D(QtMaterialList);
    d->selectedColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    viewport()->update();
}

QColor QtMaterialList::selectedColor() const
{
    Q_D(const QtMaterialList);

    if (d->useThemeColors || !d->selectedColor.isValid()) {
        QColor color = QtMaterialStyle::instance().themeColor("primary1");
        color.setAlpha(38);
        return color;
    } else {
        return d->selectedColor;
    }
}

void QtMaterialList::setHoverColor(const QColor &color)
{
    Q_D(QtMaterialList);
    d->hoverColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    viewport()->update();
}

QColor QtMaterialList::hoverColor() const
{
    Q_D(const QtMaterialList);

    if (d->useThemeColors || !d->hoverColor.isValid()) {
        QColor color = QtMaterialStyle::instance().themeColor("text");
        color.setAlpha(12);
        return color;
    } else {
        return d->hoverColor;
    }
}

bool QtMaterialList::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == viewport()) {
        switch (event->type()) {
        case QEvent::MouseMove:
        case QEvent::HoverMove:
        case QEvent::Leave:
            viewport()->update();
            break;
        default:
            break;
        }
    }

    return QListView::eventFilter(obj, event);
}
