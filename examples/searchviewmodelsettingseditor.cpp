#include "searchviewmodelsettingseditor.h"
#include "qtmaterialsearchsuggestionmodel.h"
#include "qtmaterialsearchviewitems.h"

#include <QListView>
#include <QVBoxLayout>

SearchViewModelSettingsEditor::SearchViewModelSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QListView *view = new QListView;
    QtMaterialSearchSuggestionModel *model = new QtMaterialSearchSuggestionModel(view);
    QtMaterialSearchViewItemDelegate *delegate = new QtMaterialSearchViewItemDelegate(view);

    QList<QVariantMap> items;
    QVariantMap a;
    a.insert("text", "Search chips");
    a.insert("secondaryText", "Open the chips documentation");
    a.insert("category", "Docs");
    items << a;
    QVariantMap b;
    b.insert("text", "Search bar");
    b.insert("secondaryText", "Open search-related examples");
    b.insert("category", "Components");
    items << b;

    model->setSuggestions(items);
    view->setModel(model);
    view->setItemDelegate(delegate);
    view->setMouseTracking(true);

    layout->addWidget(view);
}
