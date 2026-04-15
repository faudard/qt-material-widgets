#include "centeredslidersettingseditor.h"

#include <QCheckBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>

#include "qtmaterialcenteredslider.h"

CenteredSliderSettingsEditor::CenteredSliderSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    m_slider = new QtMaterialCenteredSlider;
    m_slider->setMinimum(-100);
    m_slider->setMaximum(100);
    m_slider->setCenterValue(0);
    m_slider->setValue(30);

    m_centerMarkerCheckBox = new QCheckBox("Show center marker");
    m_centerMarkerCheckBox->setChecked(true);

    m_valueLabelCheckBox = new QCheckBox("Show value label");
    m_valueLabelCheckBox->setChecked(false);

    m_minimumSpinBox = new QSpinBox;
    m_minimumSpinBox->setRange(-9999, 9999);
    m_minimumSpinBox->setValue(-100);

    m_maximumSpinBox = new QSpinBox;
    m_maximumSpinBox->setRange(-9999, 9999);
    m_maximumSpinBox->setValue(100);

    m_valueSpinBox = new QSpinBox;
    m_valueSpinBox->setRange(-9999, 9999);
    m_valueSpinBox->setValue(30);

    m_centerSpinBox = new QSpinBox;
    m_centerSpinBox->setRange(-9999, 9999);
    m_centerSpinBox->setValue(0);

    QFormLayout *form = new QFormLayout;
    form->addRow("Minimum", m_minimumSpinBox);
    form->addRow("Maximum", m_maximumSpinBox);
    form->addRow("Value", m_valueSpinBox);
    form->addRow("Center", m_centerSpinBox);
    form->addRow(m_centerMarkerCheckBox);
    form->addRow(m_valueLabelCheckBox);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel("Centered slider"));
    mainLayout->addWidget(m_slider);
    mainLayout->addSpacing(24);
    mainLayout->addLayout(form);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    connect(m_centerMarkerCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_valueLabelCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_minimumSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_maximumSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_valueSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_centerSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
}

void CenteredSliderSettingsEditor::updateWidget()
{
    int minimum = m_minimumSpinBox->value();
    int maximum = m_maximumSpinBox->value();
    if (minimum > maximum) {
        qSwap(minimum, maximum);
    }

    m_slider->setMinimum(minimum);
    m_slider->setMaximum(maximum);
    m_slider->setCenterValue(m_centerSpinBox->value());
    m_slider->setValue(m_valueSpinBox->value());
    m_slider->setShowCenterMarker(m_centerMarkerCheckBox->isChecked());
    m_slider->setShowValueLabel(m_valueLabelCheckBox->isChecked());
}
