#ifndef STEPPERSETTINGSEDITOR_H
#define STEPPERSETTINGSEDITOR_H

#include <QWidget>

class QCheckBox;
class QComboBox;
class QSpinBox;
class QtMaterialStepper;

class StepperSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit StepperSettingsEditor(QWidget *parent = 0);
    ~StepperSettingsEditor();

private slots:
    void updateWidget();

private:
    QtMaterialStepper *m_stepper;
    QCheckBox *m_clickableCheckBox;
    QCheckBox *m_labelsCheckBox;
    QComboBox *m_orientationComboBox;
    QSpinBox *m_currentStepSpinBox;
};

#endif // STEPPERSETTINGSEDITOR_H
