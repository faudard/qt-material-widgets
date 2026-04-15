#include "buttongroupsettingseditor.h"

#include "qtmaterialbuttongroup.h"
#include "qtmaterialflatbutton.h"

#include <QCheckBox>
#include <QVBoxLayout>

ButtonGroupSettingsEditor::ButtonGroupSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    m_group = new QtMaterialButtonGroup;
    m_group->addButton(new QtMaterialFlatButton("Back"));
    m_group->addButton(new QtMaterialFlatButton("Pause"));
    m_group->addButton(new QtMaterialFlatButton("Next"));

    m_useThemeColorsCheckBox = new QCheckBox("Use theme colors");
    m_useThemeColorsCheckBox->setChecked(true);

    m_exclusiveCheckBox = new QCheckBox("Exclusive");
    m_exclusiveCheckBox->setChecked(false);

    layout->addWidget(m_group);
    layout->addWidget(m_useThemeColorsCheckBox);
    layout->addWidget(m_exclusiveCheckBox);
    layout->addStretch(1);

    connect(m_useThemeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_exclusiveCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));

    updateWidget();
}

void ButtonGroupSettingsEditor::updateWidget()
{
    m_group->setUseThemeColors(m_useThemeColorsCheckBox->isChecked());
    m_group->setExclusive(m_exclusiveCheckBox->isChecked());
}
