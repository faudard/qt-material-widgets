#ifndef RESPONSIVENAVIGATIONSETTINGSEDITOR_H
#define RESPONSIVENAVIGATIONSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialResponsiveNavigation;
class QSlider;
class QComboBox;

class ResponsiveNavigationSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ResponsiveNavigationSettingsEditor(QWidget *parent = 0);

private slots:
    void updateWidget();

private:
    QtMaterialResponsiveNavigation *m_navigation;
    QSlider *m_compactBreakpoint;
    QSlider *m_mediumBreakpoint;
    QComboBox *m_forcedMode;
};

#endif // RESPONSIVENAVIGATIONSETTINGSEDITOR_H
