#include "sidesheetsettingseditor.h"

#include <QLabel>
#include <QVBoxLayout>
#include "qtmaterialraisedbutton.h"
#include "qtmaterialsidesheet.h"

SideSheetSettingsEditor::SideSheetSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);

    m_toggleButton = new QtMaterialRaisedButton("OPEN SIDE SHEET", this);
    layout->addWidget(m_toggleButton, 0, Qt::AlignLeft);

    m_sheet = new QtMaterialSideSheet(this);
    m_sheet->setSheetWidth(320);
    m_sheet->setEdge(QtMaterialSideSheet::Right);

    QVBoxLayout *sheetLayout = new QVBoxLayout;
    sheetLayout->addWidget(new QLabel("Side Sheet", m_sheet));
    sheetLayout->addWidget(new QLabel("Put navigation, settings, or contextual content here.", m_sheet));
    sheetLayout->addStretch(1);
    m_sheet->setContentLayout(sheetLayout);

    QObject::connect(m_toggleButton, SIGNAL(clicked(bool)), this, SLOT(toggleSheet()));
}

void SideSheetSettingsEditor::toggleSheet()
{
    if (m_sheet->isVisible()) {
        m_sheet->closeSheet();
    } else {
        m_sheet->open();
    }
}
