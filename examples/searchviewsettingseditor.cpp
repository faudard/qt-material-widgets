#include "searchviewsettingseditor.h"
#include "qtmaterialsearchview.h"

#include <QVBoxLayout>
#include <QLabel>

SearchViewSettingsEditor::SearchViewSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    m_searchView = new QtMaterialSearchView(this);
    m_searchView->setPlaceholderText("Search mail");
    m_searchView->setSuggestions(QStringList()
                                 << "Archive"
                                 << "Attachments"
                                 << "Drafts"
                                 << "Important"
                                 << "Invoices"
                                 << "Meetings"
                                 << "Presentations"
                                 << "Travel");
    m_searchView->setActive(true);

    QLabel *hint = new QLabel("Search View example", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(hint);
    layout->addWidget(m_searchView);
    layout->addStretch(1);
}
