#include "daterangepickersettingseditor.h"

#include "qtmaterialdaterangepicker.h"

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

DateRangePickerSettingsEditor::DateRangePickerSettingsEditor(QWidget *parent)
    : QWidget(parent),
      m_picker(new QtMaterialDateRangePicker),
      m_label(new QLabel),
      m_dualMonthCheckBox(new QCheckBox(QStringLiteral("Dual month")))
{
    m_picker->setMinimumDate(QDate::currentDate().addYears(-1));
    m_picker->setMaximumDate(QDate::currentDate().addYears(1));

    m_dualMonthCheckBox->setChecked(true);

    connect(m_picker, SIGNAL(dateRangeChanged(QDate,QDate)), this, SLOT(updateRangeText()));
    connect(m_dualMonthCheckBox, &QCheckBox::toggled, m_picker, &QtMaterialDateRangePicker::setShowDualMonth);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_picker, 0, Qt::AlignCenter);
    layout->addWidget(m_dualMonthCheckBox, 0, Qt::AlignLeft);
    layout->addWidget(m_label);
    layout->addStretch(1);
    setLayout(layout);

    updateRangeText();
}

void DateRangePickerSettingsEditor::updateRangeText()
{
    if (!m_picker->startDate().isValid()) {
        m_label->setText(QStringLiteral("No range selected"));
        return;
    }

    if (!m_picker->endDate().isValid()) {
        m_label->setText(QStringLiteral("Start: %1").arg(m_picker->startDate().toString(Qt::ISODate)));
        return;
    }

    m_label->setText(QStringLiteral("Range: %1 → %2")
                         .arg(m_picker->startDate().toString(Qt::ISODate))
                         .arg(m_picker->endDate().toString(Qt::ISODate)));
}
