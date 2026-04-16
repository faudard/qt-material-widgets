#include "sheethandlesettingseditor.h"
#include "qtmaterialsheethandle.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QCheckBox>
#include <QSpinBox>
#include <QLabel>

SheetHandleSettingsEditor::SheetHandleSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    m_handle = new QtMaterialSheetHandle;

    QLabel *info = new QLabel(QStringLiteral("Click or drag the sheet handle. Use keyboard Enter/Space to cycle detents."));
    info->setWordWrap(true);

    QFormLayout *form = new QFormLayout;
    m_cycleCheckBox = new QCheckBox;
    m_cycleCheckBox->setChecked(true);
    m_widthSpinBox = new QSpinBox;
    m_widthSpinBox->setRange(8, 80);
    m_widthSpinBox->setValue(32);
    m_heightSpinBox = new QSpinBox;
    m_heightSpinBox->setRange(2, 16);
    m_heightSpinBox->setValue(4);
    m_targetSpinBox = new QSpinBox;
    m_targetSpinBox->setRange(24, 96);
    m_targetSpinBox->setValue(48);

    form->addRow(QStringLiteral("Cycle detents on click"), m_cycleCheckBox);
    form->addRow(QStringLiteral("Handle width"), m_widthSpinBox);
    form->addRow(QStringLiteral("Handle height"), m_heightSpinBox);
    form->addRow(QStringLiteral("Hit target"), m_targetSpinBox);

    layout->addWidget(info);
    layout->addStretch();
    layout->addWidget(m_handle, 0, Qt::AlignHCenter);
    layout->addStretch();
    layout->addLayout(form);

    connect(m_cycleCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_widthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_heightSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_targetSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));

    updateWidget();
}

void SheetHandleSettingsEditor::updateWidget()
{
    m_handle->setCycleDetentsOnClick(m_cycleCheckBox->isChecked());
    m_handle->setHandleWidth(m_widthSpinBox->value());
    m_handle->setHandleHeight(m_heightSpinBox->value());
    m_handle->setHitTargetSize(m_targetSpinBox->value());
}
