#include "searchbarsettingseditor.h"

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>

#include "qtmaterialsearchbar.h"

SearchBarSettingsEditor::SearchBarSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    m_searchBar = new QtMaterialSearchBar(this);
    m_searchBar->setPlaceholderText("Search mail");
    m_searchBar->setSuggestions(QStringList()
                                << "Search mail"
                                << "Search files"
                                << "Search contacts"
                                << "Search settings");

    m_themeColorsCheckBox = new QCheckBox("Use theme colors");
    m_collapsibleCheckBox = new QCheckBox("Collapsible");
    m_navigationIconCheckBox = new QCheckBox("Show leading navigation icon");
    m_trailingActionsCheckBox = new QCheckBox("Show trailing actions");
    m_delaySpinBox = new QSpinBox;
    m_delaySpinBox->setRange(0, 2000);
    m_delaySpinBox->setValue(250);

    m_themeColorsCheckBox->setChecked(true);
    m_navigationIconCheckBox->setChecked(true);
    m_trailingActionsCheckBox->setChecked(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_searchBar);

    QHBoxLayout *controls = new QHBoxLayout;
    controls->addWidget(m_themeColorsCheckBox);
    controls->addWidget(m_collapsibleCheckBox);
    controls->addWidget(m_navigationIconCheckBox);
    controls->addWidget(m_trailingActionsCheckBox);
    controls->addWidget(new QLabel("Delay"));
    controls->addWidget(m_delaySpinBox);
    controls->addStretch(1);

    layout->addLayout(controls);
    layout->addStretch(1);
    setLayout(layout);

    connect(m_themeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_collapsibleCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_navigationIconCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_trailingActionsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_delaySpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));

    updateWidget();
}

void SearchBarSettingsEditor::updateWidget()
{
    m_searchBar->setUseThemeColors(m_themeColorsCheckBox->isChecked());
    m_searchBar->setCollapsible(m_collapsibleCheckBox->isChecked());
    m_searchBar->setShowLeadingNavigationIcon(m_navigationIconCheckBox->isChecked());
    m_searchBar->setShowTrailingActions(m_trailingActionsCheckBox->isChecked());
    m_searchBar->setSearchDelay(m_delaySpinBox->value());
}
