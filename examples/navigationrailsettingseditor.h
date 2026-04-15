#ifndef NAVIGATIONRAILSETTINGSEDITOR_H
#define NAVIGATIONRAILSETTINGSEDITOR_H

#include <QWidget>

class QCheckBox;
class QSpinBox;
class QtMaterialNavigationRail;

class NavigationRailSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit NavigationRailSettingsEditor(QWidget *parent = 0);

private slots:
    void updateWidget();

private:
    QtMaterialNavigationRail *m_rail;
    QCheckBox *m_showLabelsCheckBox;
    QCheckBox *m_compactCheckBox;
    QCheckBox *m_themeColorsCheckBox;
    QSpinBox *m_spacingSpinBox;
};

#endif // NAVIGATIONRAILSETTINGSEDITOR_H
