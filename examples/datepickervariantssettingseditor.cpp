#include "datepickervariantssettingseditor.h"
#include "qtmaterialdatefield.h"
#include "qtmaterialdockeddatepicker.h"

#include <QVBoxLayout>
#include <QLabel>

DatePickerVariantsSettingsEditor::DatePickerVariantsSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(24);
    layout->setContentsMargins(24, 24, 24, 24);

    QLabel *title = new QLabel(QStringLiteral("Date picker variants"));
    title->setStyleSheet("font-size: 20px;");

    m_dateField = new QtMaterialDateField;
    m_dateField->setLabel("Docked date field");

    m_dockedPicker = new QtMaterialDockedDatePicker;
    m_dockedPicker->setMinimumHeight(320);

    layout->addWidget(title);
    layout->addWidget(m_dateField);
    layout->addWidget(m_dockedPicker);
    layout->addStretch(1);
}
