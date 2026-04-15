#include "selectfieldsettingseditor.h"
#include "qtmaterialselectfield.h"

#include <QCheckBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>

SelectFieldSettingsEditor::SelectFieldSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    m_selectField = new QtMaterialSelectField;
    m_selectField->setLabel("Country");
    m_selectField->setPlaceholderOption("Choose a country");
    m_selectField->setItems(QStringList() << "France" << "Germany" << "Japan" << "Canada" << "Brazil");

    m_showIndicator = new QCheckBox("Show dropdown indicator");
    m_showIndicator->setChecked(true);

    m_editable = new QCheckBox("Editable selection");

    m_currentIndex = new QSpinBox;
    m_currentIndex->setRange(-1, 4);
    m_currentIndex->setValue(-1);

    QFormLayout *controls = new QFormLayout;
    controls->addRow(m_showIndicator);
    controls->addRow(m_editable);
    controls->addRow("Current index", m_currentIndex);

    QWidget *preview = new QWidget;
    preview->setMinimumHeight(180);
    QVBoxLayout *previewLayout = new QVBoxLayout(preview);
    previewLayout->addStretch();
    previewLayout->addWidget(m_selectField, 0, Qt::AlignHCenter);
    previewLayout->addStretch();

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addLayout(controls);
    layout->addWidget(preview, 1);

    connect(m_showIndicator, &QCheckBox::toggled,
            this, &SelectFieldSettingsEditor::updateWidget);
    connect(m_editable, &QCheckBox::toggled,
            this, &SelectFieldSettingsEditor::updateWidget);
    connect(m_currentIndex, qOverload<int>(&QSpinBox::valueChanged),
            this, &SelectFieldSettingsEditor::updateWidget);

    updateWidget();
}

void SelectFieldSettingsEditor::updateWidget()
{
    m_selectField->setShowDropdownIndicator(m_showIndicator->isChecked());
    m_selectField->setEditableSelection(m_editable->isChecked());
    m_selectField->setCurrentIndex(m_currentIndex->value());
}
