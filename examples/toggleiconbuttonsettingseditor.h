#ifndef TOGGLEICONBUTTONSETTINGSEDITOR_H
#define TOGGLEICONBUTTONSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialToggleIconButton;
class QCheckBox;

class ToggleIconButtonSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ToggleIconButtonSettingsEditor(QWidget *parent = 0);
    ~ToggleIconButtonSettingsEditor();

private slots:
    void updateWidget();

private:
    QtMaterialToggleIconButton *m_button;
    QCheckBox *m_useThemeColors;
    QCheckBox *m_checked;
    QCheckBox *m_enabled;
};

#endif // TOGGLEICONBUTTONSETTINGSEDITOR_H
