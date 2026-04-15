#ifndef LOADINGPROGRESSSETTINGSEDITOR_H
#define LOADINGPROGRESSSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialProgress;
class QtMaterialCircularProgress;
class QCheckBox;
class QSlider;
class QComboBox;

class LoadingProgressSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit LoadingProgressSettingsEditor(QWidget *parent = 0);

private slots:
    void updateWidgets();

private:
    QtMaterialProgress *m_linear;
    QtMaterialCircularProgress *m_circular;
    QCheckBox *m_showLabels;
    QCheckBox *m_roundedCaps;
    QSlider *m_thickness;
    QSlider *m_value;
    QComboBox *m_mode;
};

#endif // LOADINGPROGRESSSETTINGSEDITOR_H
