#include "datetimepickersettingseditor.h"

#include "qtmaterialdatepicker.h"
#include "qtmaterialtimepicker.h"

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

DateTimePickerSettingsEditor::DateTimePickerSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *root = new QVBoxLayout(this);
    QHBoxLayout *pickers = new QHBoxLayout;
    QHBoxLayout *controls = new QHBoxLayout;

    m_datePicker = new QtMaterialDatePicker;
    m_timePicker = new QtMaterialTimePicker;
    m_themeCheckBox = new QCheckBox(tr("Use theme colors"));
    m_24hCheckBox = new QCheckBox(tr("24-hour mode"));
    m_infoLabel = new QLabel;

    m_themeCheckBox->setChecked(true);

    pickers->addWidget(m_datePicker);
    pickers->addWidget(m_timePicker);

    controls->addWidget(m_themeCheckBox);
    controls->addWidget(m_24hCheckBox);
    controls->addStretch(1);

    root->addLayout(pickers);
    root->addLayout(controls);
    root->addWidget(m_infoLabel);
    root->addStretch(1);

    connect(m_themeCheckBox, &QCheckBox::toggled, m_datePicker, &QtMaterialDatePicker::setUseThemeColors);
    connect(m_themeCheckBox, &QCheckBox::toggled, m_timePicker, &QtMaterialTimePicker::setUseThemeColors);
    connect(m_24hCheckBox, &QCheckBox::toggled, m_timePicker, &QtMaterialTimePicker::set24HourMode);
    connect(m_datePicker, &QtMaterialDatePicker::dateChanged, this, &DateTimePickerSettingsEditor::updateInfo);
    connect(m_timePicker, &QtMaterialTimePicker::timeChanged, this, &DateTimePickerSettingsEditor::updateInfo);

    updateInfo();
}

DateTimePickerSettingsEditor::~DateTimePickerSettingsEditor()
{
}

void DateTimePickerSettingsEditor::updateInfo()
{
    m_infoLabel->setText(tr("Selected: %1 %2")
                         .arg(m_datePicker->date().toString(Qt::ISODate))
                         .arg(m_timePicker->time().toString(m_24hCheckBox->isChecked() ? "HH:mm" : "hh:mm AP")));
}
