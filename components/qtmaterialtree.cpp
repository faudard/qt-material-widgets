#include "qtmaterialtree.h"
#include "qtmaterialtree_p.h"

#include <QApplication>
#include <QCursor>
#include <QEvent>
#include <QFontMetrics>
#include <QFrame>
#include <QIcon>
#include <QPainter>
#include <QPainterPath>
#include <QPixmap>
#include <QStyledItemDelegate>

#include "lib/qtmaterialstyle.h"

class QtMaterialTreeDelegate : public QStyledItemDelegate
{
public:
    explicit QtMaterialTreeDelegate(QtMaterialTree *parent)
        : QStyledItemDelegate(parent),
          m_tree(parent)
    {
    }

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE
    {
        if (!painter || index.column() != 0) {
            return;
        }

        QStyleOptionViewItem opt(option);
        initStyleOption(&opt, index);

        const QRect rect = option.rect;
        const bool selected = opt.state & QStyle::State_Selected;
        const bool hovered = isHovered(index);
        const bool enabled = m_tree->isEnabled() && (index.flags() & Qt::ItemIsEnabled);

        QColor background = m_tree->backgroundColor();
        if (selected) {
            background = m_tree->selectedColor();
        } else if (hovered) {
            background = m_tree->hoverColor();
        }

        painter->save();
        painter->fillRect(rect, background);

        const int leftPadding = 8;
        const int rightPadding = 16;
        const int leadingSpacing = 12;
        const int trailingSpacing = 12;
        const QSize iconSize = m_tree->iconSize().isValid() ? m_tree->iconSize() : QSize(20, 20);
        const QSize avatarSize(32, 32);

        int textLeft = rect.left() + leftPadding;
        QRect leadingRect;

        const bool hasAvatar = index.data(QtMaterialTree::AvatarTextRole).isValid()
                            || index.data(QtMaterialTree::AvatarPixmapRole).isValid()
                            || index.data(QtMaterialTree::AvatarColorRole).isValid();
        const QVariant decorationValue = index.data(Qt::DecorationRole);
        const bool hasDecoration = decorationValue.isValid() && !decorationValue.isNull();

        if (hasAvatar) {
            leadingRect = QRect(textLeft,
                                rect.top() + (rect.height() - avatarSize.height()) / 2,
                                avatarSize.width(),
                                avatarSize.height());
            drawAvatar(painter, index, leadingRect, enabled);
            textLeft = leadingRect.right() + leadingSpacing;
        } else if (hasDecoration) {
            leadingRect = QRect(textLeft,
                                rect.top() + (rect.height() - iconSize.height()) / 2,
                                iconSize.width(),
                                iconSize.height());
            drawDecoration(painter, decorationValue, leadingRect, enabled);
            textLeft = leadingRect.right() + leadingSpacing;
        }

        const QString primaryText = index.data(Qt::DisplayRole).toString();
        const QString secondaryText = index.data(QtMaterialTree::SecondaryTextRole).toString();
        const QString trailingText = index.data(QtMaterialTree::TrailingTextRole).toString();
        const bool twoLine = !secondaryText.trimmed().isEmpty();

        QFont primaryFont(m_tree->font());
        QFont secondaryFont(m_tree->font());
        secondaryFont.setPointSizeF(qMax<qreal>(secondaryFont.pointSizeF() - 1, 9));

        QColor primaryColor = enabled ? m_tree->textColor() : QtMaterialStyle::instance().themeColor("disabled");
        QColor secondaryColor = enabled ? m_tree->secondaryTextColor() : QtMaterialStyle::instance().themeColor("disabled");

        QRect trailingRect;
        int textRight = rect.right() - rightPadding;
        if (!trailingText.isEmpty()) {
            const int trailingWidth = qMin(120,
                                           QFontMetrics(secondaryFont).width(trailingText) + 8);
            trailingRect = QRect(rect.right() - rightPadding - trailingWidth,
                                 rect.top(),
                                 trailingWidth,
                                 rect.height());
            textRight = trailingRect.left() - trailingSpacing;
        }

        QRect textRect(textLeft,
                       rect.top(),
                       qMax(0, textRight - textLeft),
                       rect.height());

        if (twoLine) {
            const int topPadding = m_tree->isDense() ? 6 : 10;
            const int primaryHeight = m_tree->isDense() ? 16 : 18;

            QRect primaryRect(textRect.left(),
                              rect.top() + topPadding,
                              textRect.width(),
                              primaryHeight);
            QRect secondaryRect(textRect.left(),
                                primaryRect.bottom() + 2,
                                textRect.width(),
                                qMax(0, rect.bottom() - (primaryRect.bottom() + 4)));

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

            if (!trailingRect.isNull()) {
                QRect alignedTrailingRect(trailingRect.left(),
                                          rect.top() + topPadding,
                                          trailingRect.width(),
                                          primaryHeight);
                painter->drawText(alignedTrailingRect,
                                  Qt::AlignRight | Qt::AlignVCenter | Qt::TextSingleLine,
                                  QFontMetrics(secondaryFont).elidedText(trailingText,
                                                                         Qt::ElideLeft,
                                                                         alignedTrailingRect.width()));
            }
        } else {
            painter->setFont(primaryFont);
            painter->setPen(primaryColor);
            painter->drawText(textRect,
                              Qt::AlignLeft | Qt::AlignVCenter | Qt::TextSingleLine,
                              QFontMetrics(primaryFont).elidedText(primaryText,
                                                                   Qt::ElideRight,
                                                                   textRect.width()));

            if (!trailingRect.isNull()) {
                painter->setFont(secondaryFont);
                painter->setPen(secondaryColor);
                painter->drawText(trailingRect,
                                  Qt::AlignRight | Qt::AlignVCenter | Qt::TextSingleLine,
                                  QFontMetrics(secondaryFont).elidedText(trailingText,
                                                                         Qt::ElideLeft,
                                                                         trailingRect.width()));
            }
        }

        if (shouldDrawDivider(index)) {
            const bool fullWidth = index.data(QtMaterialTree::FullWidthDividerRole).toBool();
            const int dividerLeft = fullWidth ? rect.left() : textLeft;
            painter->setPen(m_tree->dividerColor());
            painter->drawLine(QPoint(dividerLeft, rect.bottom()),
                              QPoint(rect.right() - rightPadding, rect.bottom()));
        }

        painter->restore();
    }

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE
    {
        Q_UNUSED(option)

        const bool twoLine = !index.data(QtMaterialTree::SecondaryTextRole).toString().trimmed().isEmpty();
        const bool hasAvatar = index.data(QtMaterialTree::AvatarTextRole).isValid()
                            || index.data(QtMaterialTree::AvatarPixmapRole).isValid()
                            || index.data(QtMaterialTree::AvatarColorRole).isValid();

        const int height = twoLine
            ? (m_tree->isDense() ? 52 : 64)
            : (hasAvatar ? (m_tree->isDense() ? 44 : 52)
                         : (m_tree->isDense() ? 36 : 44));

        return QSize(0, height);
    }

private:
    bool isHovered(const QModelIndex &index) const
    {
        const QPoint pos = m_tree->viewport()->mapFromGlobal(QCursor::pos());

        if (!m_tree->viewport()->rect().contains(pos)) {
            return false;
        }

        const QModelIndex hovered = m_tree->indexAt(pos);
        return hovered == index;
    }

    bool shouldDrawDivider(const QModelIndex &index) const
    {
        const QVariant dividerValue = index.data(QtMaterialTree::DividerRole);
        return dividerValue.isValid() ? dividerValue.toBool() : m_tree->showDivider();
    }

    QColor avatarForeground(const QColor &background) const
    {
        const int gray = qGray(background.rgb());
        return gray < 160 ? QColor(Qt::white) : QColor(0, 0, 0, 222);
    }

    void drawAvatar(QPainter *painter,
                    const QModelIndex &index,
                    const QRect &rect,
                    bool enabled) const
    {
        const QVariant pixmapValue = index.data(QtMaterialTree::AvatarPixmapRole);
        if (pixmapValue.isValid() && pixmapValue.canConvert<QPixmap>()) {
            const QPixmap pixmap = qvariant_cast<QPixmap>(pixmapValue);
            if (!pixmap.isNull()) {
                painter->save();
                painter->setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(rect);
                painter->setClipPath(path);
                painter->drawPixmap(rect,
                                    pixmap.scaled(rect.size(),
                                                  Qt::KeepAspectRatioByExpanding,
                                                  Qt::SmoothTransformation));
                painter->restore();
                return;
            }
        }

        QColor fill = index.data(QtMaterialTree::AvatarColorRole).value<QColor>();
        if (!fill.isValid()) {
            fill = QtMaterialStyle::instance().themeColor("primary1");
        }
        if (!enabled) {
            fill.setAlpha(110);
        }

        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(Qt::NoPen);
        painter->setBrush(fill);
        painter->drawEllipse(rect);

        const QString avatarText = index.data(QtMaterialTree::AvatarTextRole).toString().left(2).toUpper();
        if (!avatarText.isEmpty()) {
            QFont font(m_tree->font());
            font.setBold(true);
            font.setPointSizeF(qMax<qreal>(font.pointSizeF() - 1, 9));
            painter->setFont(font);
            painter->setPen(avatarForeground(fill));
            painter->drawText(rect, Qt::AlignCenter, avatarText);
        }
        painter->restore();
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
        }
    }

    QtMaterialTree *const m_tree;
};

QtMaterialTreePrivate::QtMaterialTreePrivate(QtMaterialTree *q)
    : q_ptr(q)
{
}

QtMaterialTreePrivate::~QtMaterialTreePrivate()
{
}

void QtMaterialTreePrivate::init()
{
    Q_Q(QtMaterialTree);

    useThemeColors = true;
    dense = false;
    showDivider = false;

    q->setFrameShape(QFrame::NoFrame);
    q->setMouseTracking(true);
    q->setUniformRowHeights(false);
    q->setSelectionMode(QAbstractItemView::SingleSelection);
    q->setSelectionBehavior(QAbstractItemView::SelectRows);
    q->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    q->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    q->setHeaderHidden(true);
    q->setRootIsDecorated(true);
    q->setAllColumnsShowFocus(false);
    q->setItemsExpandable(true);
    q->setExpandsOnDoubleClick(true);
    q->setEditTriggers(QAbstractItemView::NoEditTriggers);
    q->setIndentation(20);
    q->setAnimated(true);
    q->viewport()->setAttribute(Qt::WA_Hover, true);
    q->viewport()->installEventFilter(q);
    q->setItemDelegate(new QtMaterialTreeDelegate(q));
    q->setIconSize(QSize(20, 20));
}

QModelIndex QtMaterialTreePrivate::hoveredIndex() const
{
    Q_Q(const QtMaterialTree);

    const QPoint pos = q->viewport()->mapFromGlobal(QCursor::pos());
    if (!q->viewport()->rect().contains(pos)) {
        return QModelIndex();
    }
    return q->indexAt(pos);
}

QtMaterialTree::QtMaterialTree(QWidget *parent)
    : QTreeView(parent),
      d_ptr(new QtMaterialTreePrivate(this))
{
    d_func()->init();
}

QtMaterialTree::~QtMaterialTree()
{
}

void QtMaterialTree::setUseThemeColors(bool value)
{
    Q_D(QtMaterialTree);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    viewport()->update();
}

bool QtMaterialTree::useThemeColors() const
{
    Q_D(const QtMaterialTree);
    return d->useThemeColors;
}

void QtMaterialTree::setDense(bool value)
{
    Q_D(QtMaterialTree);

    if (d->dense == value) {
        return;
    }

    d->dense = value;
    doItemsLayout();
    viewport()->update();
}

bool QtMaterialTree::isDense() const
{
    Q_D(const QtMaterialTree);
    return d->dense;
}

void QtMaterialTree::setShowDivider(bool value)
{
    Q_D(QtMaterialTree);

    if (d->showDivider == value) {
        return;
    }

    d->showDivider = value;
    viewport()->update();
}

bool QtMaterialTree::showDivider() const
{
    Q_D(const QtMaterialTree);
    return d->showDivider;
}

void QtMaterialTree::setTextColor(const QColor &color)
{
    Q_D(QtMaterialTree);
    d->textColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    viewport()->update();
}

QColor QtMaterialTree::textColor() const
{
    Q_D(const QtMaterialTree);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("text");
    } else {
        return d->textColor;
    }
}

void QtMaterialTree::setSecondaryTextColor(const QColor &color)
{
    Q_D(QtMaterialTree);
    d->secondaryTextColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    viewport()->update();
}

QColor QtMaterialTree::secondaryTextColor() const
{
    Q_D(const QtMaterialTree);

    if (d->useThemeColors || !d->secondaryTextColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("accent3");
    } else {
        return d->secondaryTextColor;
    }
}

void QtMaterialTree::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialTree);
    d->backgroundColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    viewport()->update();
}

QColor QtMaterialTree::backgroundColor() const
{
    Q_D(const QtMaterialTree);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("canvas");
    } else {
        return d->backgroundColor;
    }
}

void QtMaterialTree::setDividerColor(const QColor &color)
{
    Q_D(QtMaterialTree);
    d->dividerColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    viewport()->update();
}

QColor QtMaterialTree::dividerColor() const
{
    Q_D(const QtMaterialTree);

    if (d->useThemeColors || !d->dividerColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("border");
    } else {
        return d->dividerColor;
    }
}

void QtMaterialTree::setSelectedColor(const QColor &color)
{
    Q_D(QtMaterialTree);
    d->selectedColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    viewport()->update();
}

QColor QtMaterialTree::selectedColor() const
{
    Q_D(const QtMaterialTree);

    if (d->useThemeColors || !d->selectedColor.isValid()) {
        QColor color = QtMaterialStyle::instance().themeColor("primary1");
        color.setAlpha(38);
        return color;
    } else {
        return d->selectedColor;
    }
}

void QtMaterialTree::setHoverColor(const QColor &color)
{
    Q_D(QtMaterialTree);
    d->hoverColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    viewport()->update();
}

QColor QtMaterialTree::hoverColor() const
{
    Q_D(const QtMaterialTree);

    if (d->useThemeColors || !d->hoverColor.isValid()) {
        QColor color = QtMaterialStyle::instance().themeColor("text");
        color.setAlpha(12);
        return color;
    } else {
        return d->hoverColor;
    }
}

void QtMaterialTree::setBranchColor(const QColor &color)
{
    Q_D(QtMaterialTree);
    d->branchColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    viewport()->update();
}

QColor QtMaterialTree::branchColor() const
{
    Q_D(const QtMaterialTree);

    if (d->useThemeColors || !d->branchColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("accent3");
    } else {
        return d->branchColor;
    }
}

bool QtMaterialTree::eventFilter(QObject *obj, QEvent *event)
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

    return QTreeView::eventFilter(obj, event);
}

void QtMaterialTree::drawBranches(QPainter *painter,
                                  const QRect &rect,
                                  const QModelIndex &index) const
{
    if (!painter) {
        return;
    }

    if (!model() || !model()->hasChildren(index)) {
        return;
    }

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(branchColor(), 1.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(Qt::NoBrush);

    const int size = 8;
    const QPoint center(rect.left() + rect.width() / 2,
                        rect.top() + rect.height() / 2);

    QPainterPath path;
    if (isExpanded(index)) {
        path.moveTo(center.x() - size / 2, center.y() - 1);
        path.lineTo(center.x(), center.y() + size / 2 - 1);
        path.lineTo(center.x() + size / 2, center.y() - 1);
    } else {
        path.moveTo(center.x() - 2, center.y() - size / 2);
        path.lineTo(center.x() + size / 2 - 2, center.y());
        path.lineTo(center.x() - 2, center.y() + size / 2);
    }
    painter->drawPath(path);
    painter->restore();
}
