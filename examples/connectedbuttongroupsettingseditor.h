#ifndef CONNECTEDBUTTONGROUPSETTINGSEDITOR_H
#define CONNECTEDBUTTONGROUPSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialConnectedButtonGroup;
class QCheckBox;
class QSpinBox;

class ConnectedButtonGroupSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectedButtonGroupSettingsEditor(QWidget *parent = 0);
    ~ConnectedButtonGroupSettingsEditor();

private slots:
    void updateWidget();

private:
    QtMaterialConnectedButtonGroup *m_group;
    QCheckBox *m_exclusiveCheckBox;
    QSpinBox *m_spacingSpinBox;
};

#endif // CONNECTEDBUTTONGROUPSETTINGSEDITOR_H
