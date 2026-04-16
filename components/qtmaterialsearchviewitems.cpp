#include "qtmaterialsearchviewitems.h"
#include "qtmaterialsearchsuggestionmodel.h"

#include <QPainter>
#include <QApplication>

QtMaterialSearchViewItemDelegate::QtMaterialSearchViewItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
    , m_textColor(Qt::black)
    , m_secondaryTextColor(QColor(0, 0, 0, 153))
    , m_dividerColor(QColor(0, 0, 0, 30))
{
}

void QtMaterialSearchViewItemDelegate::setTextColor(const QColor &color)
{
    m_textColor = color;
}

QColor QtMaterialSearchViewItemDelegate::textColor() const
{
    return m_textColor;
}

void QtMaterialSearchViewItemDelegate::setSecondaryTextColor(const QColor &color)
{
    m_secondaryTextColor = color;
}

QColor QtMaterialSearchViewItemDelegate::secondaryTextColor() const
{
    return m_secondaryTextColor;
}

void QtMaterialSearchViewItemDelegate::setDividerColor(const QColor &color)
{
    m_dividerColor = color;
}

QColor QtMaterialSearchViewItemDelegate::dividerColor() const
{
    return m_dividerColor;
}

QSize QtMaterialSearchViewItemDelegate::sizeHint(const QStyleOptionViewItem &option,
                                                 const QModelIndex &index) const
{
    Q_UNUSED(option)
    const bool hasSecondary = !index.data(QtMaterialSearchSuggestionModel::SecondaryTextRole).toString().isEmpty();
    return QSize(0, hasSecondary ? 64 : 48);
}

void QtMaterialSearchViewItemDelegate::paint(QPainter *painter,
                                             const QStyleOptionViewItem &option,
                                             const QModelIndex &index) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, false);

    QRect rect = option.rect;
    if (option.state & QStyle::State_Selected) {
        painter->fillRect(rect, option.palette.highlight().color().lighter(180));
    } else if (option.state & QStyle::State_MouseOver) {
        painter->fillRect(rect, option.palette.highlight().color().lighter(195));
    }

    const QString text = index.data(Qt::DisplayRole).toString();
    const QString secondary = index.data(QtMaterialSearchSuggestionModel::SecondaryTextRole).toString();

    QRect textRect = rect.adjusted(16, 10, -16, -10);
    painter->setPen(m_textColor);
    QFont f = option.font;
    f.setBold(false);
    painter->setFont(f);
    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignTop, text);

    if (!secondary.isEmpty()) {
        painter->setPen(m_secondaryTextColor);
        QRect secondaryRect = textRect.adjusted(0, 24, 0, 0);
        painter->drawText(secondaryRect, Qt::AlignLeft | Qt::AlignTop, secondary);
    }

    painter->setPen(m_dividerColor);
    painter->drawLine(rect.bottomLeft() + QPoint(16, 0), rect.bottomRight());
    painter->restore();
}
