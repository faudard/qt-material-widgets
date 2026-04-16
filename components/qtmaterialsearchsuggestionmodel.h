#ifndef QTMATERIALSEARCHSUGGESTIONMODEL_H
#define QTMATERIALSEARCHSUGGESTIONMODEL_H

#include <QAbstractListModel>
#include <QStringList>

class QtMaterialSearchSuggestionModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum SearchSuggestionRole {
        SecondaryTextRole = Qt::UserRole + 1,
        IconRole,
        CategoryRole,
        ScoreRole
    };

    explicit QtMaterialSearchSuggestionModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    void clear();
    void setSuggestions(const QList<QVariantMap> &items);
    QList<QVariantMap> suggestions() const;

private:
    QList<QVariantMap> m_items;
};

#endif // QTMATERIALSEARCHSUGGESTIONMODEL_H
