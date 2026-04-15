#include "steppersettingseditor.h"

#include <QCheckBox>
#include <QComboBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>

#include "qtmaterialstepper.h"

StepperSettingsEditor::StepperSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    m_stepper = new QtMaterialStepper;
    m_stepper->setStepLabels(QStringList()
                             << "Account"
                             << "Profile"
                             << "Confirmation"
                             << "Done");

    m_clickableCheckBox = new QCheckBox;
    m_clickableCheckBox->setChecked(true);

    m_labelsCheckBox = new QCheckBox;
    m_labelsCheckBox->setChecked(true);

    m_orientationComboBox = new QComboBox;
    m_orientationComboBox->addItem("Horizontal", Qt::Horizontal);
    m_orientationComboBox->addItem("Vertical", Qt::Vertical);

    m_currentStepSpinBox = new QSpinBox;
    m_currentStepSpinBox->setMinimum(0);
    m_currentStepSpinBox->setMaximum(3);
    m_currentStepSpinBox->setValue(1);

    QWidget *canvas = new QWidget;
    canvas->setMinimumHeight(260);
    canvas->setStyleSheet("background:white;");
    QVBoxLayout *canvasLayout = new QVBoxLayout(canvas);
    canvasLayout->addStretch();
    canvasLayout->addWidget(m_stepper);
    canvasLayout->addStretch();

    QFormLayout *form = new QFormLayout;
    form->addRow("Clickable", m_clickableCheckBox);
    form->addRow("Show Labels", m_labelsCheckBox);
    form->addRow("Orientation", m_orientationComboBox);
    form->addRow("Current Step", m_currentStepSpinBox);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(canvas, 2);
    QWidget *panel = new QWidget;
    panel->setLayout(form);
    layout->addWidget(panel, 1);

    connect(m_clickableCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_labelsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_orientationComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(m_currentStepSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_stepper, SIGNAL(currentStepChanged(int)), m_currentStepSpinBox, SLOT(setValue(int)));

    updateWidget();
}

StepperSettingsEditor::~StepperSettingsEditor()
{
}

void StepperSettingsEditor::updateWidget()
{
    m_stepper->setClickable(m_clickableCheckBox->isChecked());
    m_stepper->setShowLabels(m_labelsCheckBox->isChecked());
    m_stepper->setOrientation(static_cast<Qt::Orientation>(m_orientationComboBox->currentData().toInt()));
    m_stepper->setCurrentStep(m_currentStepSpinBox->value());
}
