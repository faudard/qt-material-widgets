#ifndef CENTEREDSLIDERSETTINGSEDITOR_H
#define CENTEREDSLIDERSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialCenteredSlider;
class QCheckBox;
class QSpinBox;

class CenteredSliderSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit CenteredSliderSettingsEditor(QWidget *parent = 0);

private slots:
    void updateWidget();

private:
    QtMaterialCenteredSlider *m_slider;
    QCheckBox *m_centerMarkerCheckBox;
    QCheckBox *m_valueLabelCheckBox;
    QSpinBox  *m_minimumSpinBox;
    QSpinBox  *m_maximumSpinBox;
    QSpinBox  *m_valueSpinBox;
    QSpinBox  *m_centerSpinBox;
};

#endif  // CENTEREDSLIDERSETTINGSEDITOR_H
