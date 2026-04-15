#include "bottomsheetsettingseditor.h"

#include <QLabel>
#include <QVBoxLayout>

#include "qtmaterialbottomsheet.h"
#include "qtmaterialraisedbutton.h"

BottomSheetSettingsEditor::BottomSheetSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(40, 40, 40, 40);

    m_openButton = new QtMaterialRaisedButton("Open bottom sheet", this);
    layout->addWidget(m_openButton, 0, Qt::AlignCenter);

    m_bottomSheet = new QtMaterialBottomSheet(this);
    m_bottomSheet->setSheetHeight(220);

    QVBoxLayout *sheetLayout = new QVBoxLayout;
    sheetLayout->addWidget(new QLabel("Bottom sheet content", m_bottomSheet));
    sheetLayout->addWidget(new QLabel("Use this example as a foundation for actions, lists, or forms.", m_bottomSheet));
    sheetLayout->addStretch(1);
    m_bottomSheet->setContentLayout(sheetLayout);

    connect(m_openButton, SIGNAL(clicked(bool)), this, SLOT(showBottomSheet()));
}

void BottomSheetSettingsEditor::showBottomSheet()
{
    m_bottomSheet->showSheet();
}
