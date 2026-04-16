#include "sidesheetvariantssettingseditor.h"
#include "../components/qtmaterialmodalsidesheet.h"
#include "../components/qtmaterialstandardsidesheet.h"

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

SideSheetVariantsSettingsEditor::SideSheetVariantsSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *root = new QHBoxLayout(this);
    QVBoxLayout *controls = new QVBoxLayout;
    QVBoxLayout *content = new QVBoxLayout;

    m_openButton = new QPushButton(tr("Open modal side sheet"), this);
    m_dismissOverlayCheckBox = new QCheckBox(tr("Dismiss on overlay click"), this);
    m_dismissOverlayCheckBox->setChecked(true);
    m_standardExpandedCheckBox = new QCheckBox(tr("Standard sheet expanded"), this);
    m_standardExpandedCheckBox->setChecked(true);

    controls->addWidget(m_openButton);
    controls->addWidget(m_dismissOverlayCheckBox);
    controls->addWidget(m_standardExpandedCheckBox);
    controls->addStretch();

    QWidget *page = new QWidget(this);
    QHBoxLayout *pageLayout = new QHBoxLayout(page);
    m_standardSheet = new QtMaterialStandardSideSheet(page);
    QVBoxLayout *sheetLayout = new QVBoxLayout;
    sheetLayout->addWidget(new QLabel(tr("Standard side sheet content"), m_standardSheet));
    sheetLayout->addWidget(new QLabel(tr("Useful for persistent supplementary content."), m_standardSheet));
    m_standardSheet->setContentLayout(sheetLayout);

    QWidget *mainContent = new QWidget(page);
    QVBoxLayout *mainLayout = new QVBoxLayout(mainContent);
    mainLayout->addWidget(new QLabel(tr("Main page content"), mainContent));
    mainLayout->addWidget(new QLabel(tr("Use the controls to open the modal sheet or collapse the standard sheet."), mainContent));
    mainLayout->addStretch();

    pageLayout->addWidget(m_standardSheet);
    pageLayout->addWidget(mainContent, 1);

    content->addWidget(page, 1);

    root->addLayout(controls);
    root->addLayout(content, 1);

    m_modalSheet = new QtMaterialModalSideSheet(window());
    m_modalSheet->resize(800, 500);
    QVBoxLayout *modalLayout = new QVBoxLayout;
    modalLayout->addWidget(new QLabel(tr("Modal side sheet"), m_modalSheet));
    modalLayout->addWidget(new QLabel(tr("Dismiss by clicking the overlay or using your own close control."), m_modalSheet));
    modalLayout->addStretch();
    m_modalSheet->setContentLayout(modalLayout);

    connect(m_openButton, SIGNAL(clicked()), this, SLOT(openModalSheet()));
    connect(m_dismissOverlayCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateStates()));
    connect(m_standardExpandedCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateStates()));
}

void SideSheetVariantsSettingsEditor::openModalSheet()
{
    m_modalSheet->setGeometry(window()->rect());
    m_modalSheet->open();
}

void SideSheetVariantsSettingsEditor::updateStates()
{
    m_modalSheet->setDismissOnOverlayClick(m_dismissOverlayCheckBox->isChecked());
    m_standardSheet->setExpanded(m_standardExpandedCheckBox->isChecked());
}
