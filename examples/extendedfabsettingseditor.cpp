#include "extendedfabsettingseditor.h"
#include "qtmaterialextendedfab.h"

#include <QCheckBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QVBoxLayout>

ExtendedFabSettingsEditor::ExtendedFabSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    m_fab = new QtMaterialExtendedFloatingActionButton(QIcon(), "Compose", this);
    m_collapsed = new QCheckBox(this);
    m_checkable = new QCheckBox(this);
    m_checked = new QCheckBox(this);
    m_text = new QLineEdit("Compose", this);

    connect(m_collapsed, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_checkable, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_checked, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_text, SIGNAL(textChanged(QString)), this, SLOT(updateWidget()));

    QFormLayout *controls = new QFormLayout;
    controls->addRow("Text", m_text);
    controls->addRow("Collapsed", m_collapsed);
    controls->addRow("Checkable", m_checkable);
    controls->addRow("Checked", m_checked);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_fab, 0, Qt::AlignCenter);
    layout->addLayout(controls);
    layout->addStretch(1);
    setLayout(layout);

    updateWidget();
}

void ExtendedFabSettingsEditor::updateWidget()
{
    m_fab->setText(m_text->text());
    m_fab->setCollapsed(m_collapsed->isChecked());
    m_fab->setCheckable(m_checkable->isChecked());
    m_fab->setChecked(m_checked->isChecked());
}
