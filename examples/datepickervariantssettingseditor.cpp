#include "datepickervariantssettingseditor.h"
#include "qtmaterialdatefield.h"
#include "qtmaterialdockeddatepicker.h"
#include "qtmaterialdaterangepicker.h"

#include <QVBoxLayout>
#include <QLabel>

DatePickerVariantsSettingsEditor::DatePickerVariantsSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->setSpacing(24);
  layout->setContentsMargins(24, 24, 24, 24);

  QLabel *title = new QLabel(QStringLiteral("Date picker variants"));
  title->setStyleSheet("font-size: 20px; font-weight: 600;");

  QLabel *fieldLabel = new QLabel(QStringLiteral("Date field"));
  m_dateField = new QtMaterialDateField;
  m_dateField->setLabel("Pick a date");

  QLabel *dockedLabel = new QLabel(QStringLiteral("Standalone docked picker"));
  m_dockedPicker = new QtMaterialDockedDatePicker;
  m_dockedPicker->setMinimumHeight(320);

  QLabel *rangeLabel = new QLabel(QStringLiteral("Date range picker"));
  m_rangePicker = new QtMaterialDateRangePicker;
  m_rangePicker->setMinimumHeight(420);
  m_rangePicker->setShowDualMonth(true);

  // Au moins, si on choisit une date dans le picker standalone,
  // le champ texte reflète aussi cette date.
  connect(m_dockedPicker, &QtMaterialDockedDatePicker::dateSelected,
          m_dateField, &QtMaterialDateField::setDate);

  layout->addWidget(title);
  layout->addWidget(fieldLabel);
  layout->addWidget(m_dateField);
  layout->addWidget(dockedLabel);
  layout->addWidget(m_dockedPicker);
  layout->addWidget(rangeLabel);
  layout->addWidget(m_rangePicker);
  layout->addStretch(1);
}