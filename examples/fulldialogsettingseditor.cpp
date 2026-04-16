#include "fulldialogsettingseditor.h"
#include "qtmaterialfulldialog.h"

#include <QPushButton>
#include <QVBoxLayout>

FullDialogSettingsEditor::FullDialogSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    m_button = new QPushButton(tr("Open full-screen dialog"), this);
    layout->addWidget(m_button);
    layout->addStretch(1);

    m_dialog = new QtMaterialFullScreenDialog(window());
    m_dialog->setTitle(tr("Edit profile"));

    connect(m_button, SIGNAL(clicked()), this, SLOT(showDialog()));
}

void FullDialogSettingsEditor::showDialog()
{
    m_dialog->resize(window()->size());
    m_dialog->open();
}
