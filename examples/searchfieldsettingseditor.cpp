#include "searchfieldsettingseditor.h"
#include "qtmaterialsearchfield.h"

#include <QCheckBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>

SearchFieldSettingsEditor::SearchFieldSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    m_searchField = new QtMaterialSearchField;
    m_searchField->setLabel("Search");
    m_searchField->setPlaceholderText("Type to search");

    m_showSearchIcon = new QCheckBox("Show search icon");
    m_showSearchIcon->setChecked(true);

    m_showClearButton = new QCheckBox("Show clear button");
    m_showClearButton->setChecked(true);

    m_useThemeColors = new QCheckBox("Use theme colors");
    m_useThemeColors->setChecked(true);

    m_searchDelay = new QSpinBox;
    m_searchDelay->setRange(0, 2000);
    m_searchDelay->setSingleStep(50);
    m_searchDelay->setValue(250);

    m_status = new QLabel("Search status: idle");

    QFormLayout *form = new QFormLayout;
    form->addRow(m_showSearchIcon);
    form->addRow(m_showClearButton);
    form->addRow(m_useThemeColors);
    form->addRow("Search delay (ms)", m_searchDelay);

    QWidget *canvas = new QWidget;
    canvas->setStyleSheet("background: white;");
    QVBoxLayout *canvasLayout = new QVBoxLayout(canvas);
    canvasLayout->addStretch();
    canvasLayout->addWidget(m_searchField);
    canvasLayout->addWidget(m_status);
    canvasLayout->addStretch();
    canvasLayout->setContentsMargins(24, 24, 24, 24);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addLayout(form);
    layout->addWidget(canvas, 1);

    connect(m_showSearchIcon, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_showClearButton, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_useThemeColors, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_searchDelay, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_searchField, SIGNAL(searchRequested(QString)), this, SLOT(handleSearch(QString)));
    connect(m_searchField, SIGNAL(cleared()), this, SLOT(handleCleared()));

    updateWidget();
}

void SearchFieldSettingsEditor::updateWidget()
{
    m_searchField->setShowSearchIcon(m_showSearchIcon->isChecked());
    m_searchField->setShowClearButton(m_showClearButton->isChecked());
    m_searchField->setUseThemeColors(m_useThemeColors->isChecked());
    m_searchField->setSearchDelay(m_searchDelay->value());
}

void SearchFieldSettingsEditor::handleSearch(const QString &text)
{
    m_status->setText(QString("Search status: \"%1\"").arg(text));
}

void SearchFieldSettingsEditor::handleCleared()
{
    m_status->setText("Search status: cleared");
}
