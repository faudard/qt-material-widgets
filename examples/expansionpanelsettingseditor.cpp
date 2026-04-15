#include "expansionpanelsettingseditor.h"
#include "../components/qtmaterialexpansionpanel.h"
#include "../components/qtmaterialflatbutton.h"

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

ExpansionPanelSettingsEditor::ExpansionPanelSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(24, 24, 24, 24);
    layout->setSpacing(12);

    m_panel = new QtMaterialExpansionPanel(this);
    m_panel->setTitle("Shipping details");
    m_panel->setSubtitle("Tap to expand");
    m_panel->setExpanded(true);

    QVBoxLayout *content = new QVBoxLayout;
    content->setContentsMargins(16, 8, 16, 16);
    content->addWidget(new QLabel("Order #348291", m_panel));
    content->addWidget(new QLabel("Status: Processing", m_panel));
    content->addWidget(new QLabel("Estimated arrival: Friday", m_panel));

    QHBoxLayout *actions = new QHBoxLayout;
    actions->addStretch();
    actions->addWidget(new QtMaterialFlatButton("CANCEL", m_panel));
    actions->addWidget(new QtMaterialFlatButton("TRACK", m_panel));
    content->addLayout(actions);

    m_panel->setContentLayout(content);
    layout->addWidget(m_panel);

    m_titleEdit = new QLineEdit("Shipping details", this);
    m_subtitleEdit = new QLineEdit("Tap to expand", this);

    m_expandedCheckBox = new QCheckBox("Expanded", this);
    m_expandedCheckBox->setChecked(true);

    m_collapsibleCheckBox = new QCheckBox("Collapsible", this);
    m_collapsibleCheckBox->setChecked(true);

    m_dividerCheckBox = new QCheckBox("Show divider", this);
    m_dividerCheckBox->setChecked(true);

    layout->addWidget(new QLabel("Title", this));
    layout->addWidget(m_titleEdit);
    layout->addWidget(new QLabel("Subtitle", this));
    layout->addWidget(m_subtitleEdit);
    layout->addWidget(m_expandedCheckBox);
    layout->addWidget(m_collapsibleCheckBox);
    layout->addWidget(m_dividerCheckBox);
    layout->addStretch();

    connect(m_titleEdit, SIGNAL(textChanged(QString)), this, SLOT(updateWidget()));
    connect(m_subtitleEdit, SIGNAL(textChanged(QString)), this, SLOT(updateWidget()));
    connect(m_expandedCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_collapsibleCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_dividerCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
}

void ExpansionPanelSettingsEditor::updateWidget()
{
    m_panel->setTitle(m_titleEdit->text());
    m_panel->setSubtitle(m_subtitleEdit->text());
    m_panel->setExpanded(m_expandedCheckBox->isChecked());
    m_panel->setCollapsible(m_collapsibleCheckBox->isChecked());
    m_panel->setShowDivider(m_dividerCheckBox->isChecked());
}
