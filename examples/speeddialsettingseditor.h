#ifndef SPEEDDIALSETTINGSEDITOR_H
#define SPEEDDIALSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialSpeedDial;
class QCheckBox;
class QSpinBox;
class QComboBox;

class SpeedDialSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit SpeedDialSettingsEditor(QWidget *parent = 0);

private slots:
    void updateWidget();

private:
    QtMaterialSpeedDial *m_speedDial;
    QCheckBox *m_themeColorsCheckBox;
    QCheckBox *m_labelsVisibleCheckBox;
    QSpinBox *m_spacingSpinBox;
    QComboBox *m_cornerComboBox;
};

#endif // SPEEDDIALSETTINGSEDITOR_H
