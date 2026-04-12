#include "qtmaterialtable.h"
#include "qtmaterialtable_p.h"

#include <QAbstractItemModel>
#include <QCursor>
#include <QEvent>
#include <QFrame>
#include <QHeaderView>
#include <QPainter>
#include <QStyledItemDelegate>

#include "lib/qtmaterialstyle.h"

class QtMaterialTableHeaderView : public QHeaderView
{
public:
    explicit QtMaterialTableHeaderView(Qt::Orientation orientation, QtMaterialTable *parent)
        : QHeaderView(orientation, parent)
    {
        setSectionsClickable(false);
        setHighlightSections(false);
        setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    }

protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const Q_DECL_OVERRIDE
    {
        if (!painter || !rect.isValid()) {
            return;
        }

        const QtMaterialTable *table = static_cast<const QtMaterialTable *>(parentWidget());

        painter->save();
        painter->fillRect(rect, table->backgroundColor());
        painter->setPen(table->gridColor());
        painter->drawLine(rect.bottomLeft(), rect.bottomRight());

        const QVariant displayValue = model()
            ? model()->headerData(logicalIndex, orientation(), Qt::DisplayRole)
            : QVariant();

        const QVariant alignmentValue = model()
            ? model()->headerData(logicalIndex, orientation(), Qt::TextAlignmentRole)
            : QVariant();

        const int alignment = alignmentValue.isValid()
            ? alignmentValue.toInt()
            : static_cast<int>(Qt::AlignLeft | Qt::AlignVCenter);

        QFont font(table->font());
        font.setBold(true);
        painter->setFont(font);

        const QRect textRect = rect.adjusted(16, 0, -16, 0);
        const QString text = QFontMetrics(font).elidedText(
            displayValue.toString(),
            Qt::ElideRight,
            textRect.width());

        painter->setPen(table->isEnabled()
            ? table->headerColor()
            : QtMaterialStyle::instance().themeColor("disabled"));

        painter->drawText(textRect, alignment | Qt::TextSingleLine, text);
        painter->restore();
    }

    QSize sectionSizeFromContents(int logicalIndex) const Q_DECL_OVERRIDE
    {
        QSize size = QHeaderView::sectionSizeFromContents(logicalIndex);

        if (Qt::Horizontal == orientation()) {
            const QtMaterialTable *table = static_cast<const QtMaterialTable *>(parentWidget());
            size.setHeight(table->isDense() ? 48 : 56);
        }

        return size;
    }
};

class QtMaterialTableDelegate : public QStyledItemDelegate
{
public:
    explicit QtMaterialTableDelegate(QtMaterialTable *parent)
        : QStyledItemDelegate(parent),
          m_table(parent)
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

        QColor background = (index.row() % 2)
            ? m_table->alternateBackgroundColor()
            : m_table->backgroundColor();

        if (opt.state & QStyle::State_Selected) {
            background = m_table->selectedRowColor();
        } else if (isHovered(index)) {
            background = m_table->hoverRowColor();
        }

        painter->save();
        painter->fillRect(option.rect, background);
        painter->restore();

        opt.state &= ~QStyle::State_HasFocus;
        opt.backgroundBrush = QBrush(background);
        opt.palette.setBrush(QPalette::Base, QBrush(background));
        opt.palette.setBrush(QPalette::AlternateBase, QBrush(m_table->alternateBackgroundColor()));
        opt.palette.setBrush(QPalette::Highlight, QBrush(background));

        const QColor textColor = m_table->isEnabled()
            ? m_table->textColor()
            : QtMaterialStyle::instance().themeColor("disabled");

        opt.palette.setColor(QPalette::Text, textColor);
        opt.palette.setColor(QPalette::HighlightedText, textColor);
        opt.displayAlignment |= Qt::AlignVCenter;
        opt.rect = opt.rect.adjusted(16, 0, -16, 0);

        QStyledItemDelegate::paint(painter, opt, index);

        painter->save();
        painter->setPen(m_table->gridColor());
        painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
        painter->restore();
    }

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE
    {
        QSize size = QStyledItemDelegate::sizeHint(option, index);
        size.setHeight(m_table->isDense() ? 40 : 48);
        return size;
    }

private:
    bool isHovered(const QModelIndex &index) const
    {
        const QPoint pos = m_table->viewport()->mapFromGlobal(QCursor::pos());

        if (!m_table->viewport()->rect().contains(pos)) {
            return false;
        }

        const QModelIndex hovered = m_table->indexAt(pos);
        return hovered.isValid() && hovered.row() == index.row();
    }

    QtMaterialTable *const m_table;
};

/*!
 * \class QtMaterialTablePrivate
 * \internal
 */

QtMaterialTablePrivate::QtMaterialTablePrivate(QtMaterialTable *q)
    : q_ptr(q)
{
}

QtMaterialTablePrivate::~QtMaterialTablePrivate()
{
}

void QtMaterialTablePrivate::init()
{
    Q_Q(QtMaterialTable);

    useThemeColors = true;
    dense = false;

    q->setAlternatingRowColors(true);
    q->setSelectionBehavior(QAbstractItemView::SelectRows);
    q->setSelectionMode(QAbstractItemView::SingleSelection);
    q->setShowGrid(false);
    q->setFrameShape(QFrame::NoFrame);
    q->setWordWrap(false);
    q->setMouseTracking(true);
    q->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    q->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    q->viewport()->setAttribute(Qt::WA_Hover, true);
    q->viewport()->installEventFilter(q);
    q->setItemDelegate(new QtMaterialTableDelegate(q));
    q->setHorizontalHeader(new QtMaterialTableHeaderView(Qt::Horizontal, q));
    q->horizontalHeader()->setStretchLastSection(true);
    q->horizontalHeader()->setMinimumSectionSize(72);
    q->horizontalHeader()->setDefaultSectionSize(160);
    q->verticalHeader()->hide();
    q->setCornerButtonEnabled(false);

    setupMetrics();
}

void QtMaterialTablePrivate::setupMetrics()
{
    Q_Q(QtMaterialTable);

    q->verticalHeader()->setDefaultSectionSize(dense ? 40 : 48);
    q->horizontalHeader()->setFixedHeight(dense ? 48 : 56);
    q->updateGeometries();
}

/*!
 * \class QtMaterialTable
 */

QtMaterialTable::QtMaterialTable(QWidget *parent)
    : QTableView(parent),
      d_ptr(new QtMaterialTablePrivate(this))
{
    d_func()->init();
}

QtMaterialTable::~QtMaterialTable()
{
}

void QtMaterialTable::setUseThemeColors(bool value)
{
    Q_D(QtMaterialTable);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    viewport()->update();
    horizontalHeader()->viewport()->update();
}

bool QtMaterialTable::useThemeColors() const
{
    Q_D(const QtMaterialTable);
    return d->useThemeColors;
}

void QtMaterialTable::setDense(bool value)
{
    Q_D(QtMaterialTable);

    if (d->dense == value) {
        return;
    }

    d->dense = value;
    d->setupMetrics();
    doItemsLayout();
    viewport()->update();
    horizontalHeader()->viewport()->update();
}

bool QtMaterialTable::isDense() const
{
    Q_D(const QtMaterialTable);
    return d->dense;
}

void QtMaterialTable::setHeaderColor(const QColor &color)
{
    Q_D(QtMaterialTable);
    d->headerColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    horizontalHeader()->viewport()->update();
}

QColor QtMaterialTable::headerColor() const
{
    Q_D(const QtMaterialTable);

    if (d->useThemeColors || !d->headerColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("accent3");
    } else {
        return d->headerColor;
    }
}

void QtMaterialTable::setTextColor(const QColor &color)
{
    Q_D(QtMaterialTable);
    d->textColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    viewport()->update();
}

QColor QtMaterialTable::textColor() const
{
    Q_D(const QtMaterialTable);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("text");
    } else {
        return d->textColor;
    }
}

void QtMaterialTable::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialTable);
    d->backgroundColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    viewport()->update();
    horizontalHeader()->viewport()->update();
}

QColor QtMaterialTable::backgroundColor() const
{
    Q_D(const QtMaterialTable);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("canvas");
    } else {
        return d->backgroundColor;
    }
}

void QtMaterialTable::setAlternateBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialTable);
    d->alternateBackgroundColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    viewport()->update();
}

QColor QtMaterialTable::alternateBackgroundColor() const
{
    Q_D(const QtMaterialTable);

    if (!d->useThemeColors && d->alternateBackgroundColor.isValid()) {
        return d->alternateBackgroundColor;
    }

    if (!d->useThemeColors && d->backgroundColor.isValid()) {
        QColor color = d->backgroundColor;
        return color.lightness() > 128 ? color.darker(104) : color.lighter(116);
    }

    return QtMaterialStyle::instance().themeColor("accent2");
}

void QtMaterialTable::setGridColor(const QColor &color)
{
    Q_D(QtMaterialTable);
    d->gridColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    viewport()->update();
    horizontalHeader()->viewport()->update();
}

QColor QtMaterialTable::gridColor() const
{
    Q_D(const QtMaterialTable);

    if (d->useThemeColors || !d->gridColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("border");
    } else {
        return d->gridColor;
    }
}

void QtMaterialTable::setSelectedRowColor(const QColor &color)
{
    Q_D(QtMaterialTable);
    d->selectedRowColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    viewport()->update();
}

QColor QtMaterialTable::selectedRowColor() const
{
    Q_D(const QtMaterialTable);

    if (d->useThemeColors || !d->selectedRowColor.isValid()) {
        QColor color = QtMaterialStyle::instance().themeColor("primary1");
        color.setAlpha(38);
        return color;
    } else {
        return d->selectedRowColor;
    }
}

void QtMaterialTable::setHoverRowColor(const QColor &color)
{
    Q_D(QtMaterialTable);
    d->hoverRowColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    viewport()->update();
}

QColor QtMaterialTable::hoverRowColor() const
{
    Q_D(const QtMaterialTable);

    if (d->useThemeColors || !d->hoverRowColor.isValid()) {
        QColor color = QtMaterialStyle::instance().themeColor("text");
        color.setAlpha(12);
        return color;
    } else {
        return d->hoverRowColor;
    }
}

bool QtMaterialTable::eventFilter(QObject *obj, QEvent *event)
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

    return QTableView::eventFilter(obj, event);
}
