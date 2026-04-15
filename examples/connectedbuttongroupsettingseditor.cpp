#include "connectedbuttongroupsettingseditor.h"

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>

#include "qtmaterialconnectedbuttongroup.h"

ConnectedButtonGroupSettingsEditor::ConnectedButtonGroupSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    m_group = new QtMaterialConnectedButtonGroup;
    m_group->addButton("Day");
    m_group->addButton("Week");
    m_group->addButton("Month");
    m_group->setCheckedIndex(0);

    m_exclusiveCheckBox = new QCheckBox("Exclusive");
    m_exclusiveCheckBox->setChecked(true);

    m_spacingSpinBox = new QSpinBox;
    m_spacingSpinBox->setRange(0, 24);
    m_spacingSpinBox->setValue(0);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(new QLabel("Connected Button Group"));
    layout->addWidget(m_group);
    layout->addSpacing(24);
    layout->addWidget(m_exclusiveCheckBox);

    QHBoxLayout *spacingLayout = new QHBoxLayout;
    spacingLayout->addWidget(new QLabel("Spacing"));
    spacingLayout->addWidget(m_spacingSpinBox);
    layout->addLayout(spacingLayout);
    layout->addStretch(1);
    setLayout(layout);

    connect(m_exclusiveCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_spacingSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
}

ConnectedButtonGroupSettingsEditor::~ConnectedButtonGroupSettingsEditor()
{
}

void ConnectedButtonGroupSettingsEditor::updateWidget()
{
    m_group->setExclusive(m_exclusiveCheckBox->isChecked());
    m_group->setSpacing(m_spacingSpinBox->value());
}
