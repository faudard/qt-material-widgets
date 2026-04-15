#include "rangeslidersettingseditor.h"
#include "qtmaterialrangeslider.h"

#include <QCheckBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>

RangeSliderSettingsEditor::RangeSliderSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    m_slider = new QtMaterialRangeSlider;
    m_slider->setRange(0, 100);
    m_slider->setValues(20, 80);
    mainLayout->addWidget(m_slider);

    m_rangeLabel = new QLabel;
    mainLayout->addWidget(m_rangeLabel);

    QWidget *panel = new QWidget;
    QFormLayout *form = new QFormLayout(panel);

    m_minimum = new QSpinBox;
    m_minimum->setRange(-999, 999);
    m_minimum->setValue(0);

    m_maximum = new QSpinBox;
    m_maximum->setRange(-999, 999);
    m_maximum->setValue(100);

    m_lower = new QSpinBox;
    m_lower->setRange(-999, 999);
    m_lower->setValue(20);

    m_upper = new QSpinBox;
    m_upper->setRange(-999, 999);
    m_upper->setValue(80);

    m_step = new QSpinBox;
    m_step->setRange(1, 100);
    m_step->setValue(10);

    m_stepMode = new QCheckBox;
    m_ticks = new QCheckBox;
    m_labels = new QCheckBox;
    m_inverted = new QCheckBox;

    form->addRow("Minimum", m_minimum);
    form->addRow("Maximum", m_maximum);
    form->addRow("Lower value", m_lower);
    form->addRow("Upper value", m_upper);
    form->addRow("Single step", m_step);
    form->addRow("Step mode", m_stepMode);
    form->addRow("Show tick marks", m_ticks);
    form->addRow("Show value labels", m_labels);
    form->addRow("Inverted", m_inverted);

    mainLayout->addWidget(panel);
    mainLayout->addStretch(1);

    connect(m_minimum, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_maximum, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_lower, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_upper, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_step, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_stepMode, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_ticks, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_labels, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_inverted, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_slider, SIGNAL(rangeChanged(int,int)), this, SLOT(syncLabels()));

    updateWidget();
    syncLabels();
}

void RangeSliderSettingsEditor::updateWidget()
{
    int minimum = m_minimum->value();
    int maximum = qMax(minimum, m_maximum->value());
    m_slider->setRange(minimum, maximum);
    m_slider->setSingleStep(m_step->value());
    m_slider->setStepMode(m_stepMode->isChecked());
    m_slider->setShowTickMarks(m_ticks->isChecked());
    m_slider->setShowValueLabels(m_labels->isChecked());
    m_slider->setInvertedAppearance(m_inverted->isChecked());
    m_slider->setValues(m_lower->value(), m_upper->value());
    syncLabels();
}

void RangeSliderSettingsEditor::syncLabels()
{
    m_rangeLabel->setText(QString("Selected range: %1 – %2")
                          .arg(m_slider->lowerValue())
                          .arg(m_slider->upperValue()));
}
