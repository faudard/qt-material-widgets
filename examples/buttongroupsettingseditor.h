#ifndef BUTTONGROUPSETTINGSEDITOR_H
#define BUTTONGROUPSETTINGSEDITOR_H

#include <QWidget>

class QCheckBox;
class QVBoxLayout;
class QtMaterialButtonGroup;

class ButtonGroupSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ButtonGroupSettingsEditor(QWidget *parent = 0);

protected slots:
    void updateWidget();

private:
    QtMaterialButtonGroup *m_group;
    QCheckBox *m_useThemeColorsCheckBox;
    QCheckBox *m_exclusiveCheckBox;
};

#endif // BUTTONGROUPSETTINGSEDITOR_H
