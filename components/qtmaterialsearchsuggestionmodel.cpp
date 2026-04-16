#include "qtmaterialsearchsuggestionmodel.h"

QtMaterialSearchSuggestionModel::QtMaterialSearchSuggestionModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int QtMaterialSearchSuggestionModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_items.count();
}

QVariant QtMaterialSearchSuggestionModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_items.count()) {
        return QVariant();
    }

    const QVariantMap item = m_items.at(index.row());
    switch (role) {
    case Qt::DisplayRole:
        return item.value("text");
    case SecondaryTextRole:
        return item.value("secondaryText");
    case IconRole:
        return item.value("icon");
    case CategoryRole:
        return item.value("category");
    case ScoreRole:
        return item.value("score");
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> QtMaterialSearchSuggestionModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(Qt::DisplayRole, "text");
    roles.insert(SecondaryTextRole, "secondaryText");
    roles.insert(IconRole, "icon");
    roles.insert(CategoryRole, "category");
    roles.insert(ScoreRole, "score");
    return roles;
}

void QtMaterialSearchSuggestionModel::clear()
{
    beginResetModel();
    m_items.clear();
    endResetModel();
}

void QtMaterialSearchSuggestionModel::setSuggestions(const QList<QVariantMap> &items)
{
    beginResetModel();
    m_items = items;
    endResetModel();
}

QList<QVariantMap> QtMaterialSearchSuggestionModel::suggestions() const
{
    return m_items;
}
