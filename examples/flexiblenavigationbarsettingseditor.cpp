#include "flexiblenavigationbarsettingseditor.h"
#include "qtmaterialflexiblenavigationbar.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QStyle>

FlexibleNavigationBarSettingsEditor::FlexibleNavigationBarSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Flexible Navigation Bar", this);
    m_bar = new QtMaterialFlexibleNavigationBar(this);

    m_bar->addItem(style()->standardIcon(QStyle::SP_DirHomeIcon), "Home");
    m_bar->addItem(style()->standardIcon(QStyle::SP_FileDialogContentsView), "Browse");
    m_bar->addItem(style()->standardIcon(QStyle::SP_MessageBoxInformation), "Info");
    m_bar->addItem(style()->standardIcon(QStyle::SP_DialogYesButton), "Profile");

    layout->addWidget(label);
    layout->addWidget(m_bar);
    layout->addStretch(1);
}
