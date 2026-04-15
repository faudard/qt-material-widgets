#ifndef RANGESLIDERSETTINGSEDITOR_H
#define RANGESLIDERSETTINGSEDITOR_H

#include <QWidget>

class QCheckBox;
class QLabel;
class QSlider;
class QSpinBox;
class QtMaterialRangeSlider;

class RangeSliderSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit RangeSliderSettingsEditor(QWidget *parent = 0);

private slots:
    void updateWidget();
    void syncLabels();

private:
    QtMaterialRangeSlider *m_slider;
    QLabel *m_rangeLabel;
    QSpinBox *m_minimum;
    QSpinBox *m_maximum;
    QSpinBox *m_lower;
    QSpinBox *m_upper;
    QSpinBox *m_step;
    QCheckBox *m_stepMode;
    QCheckBox *m_ticks;
    QCheckBox *m_labels;
    QCheckBox *m_inverted;
};

#endif // RANGESLIDERSETTINGSEDITOR_H
