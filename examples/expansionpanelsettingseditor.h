#ifndef EXPANSIONPANELSETTINGSEDITOR_H
#define EXPANSIONPANELSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialExpansionPanel;
class QCheckBox;
class QLineEdit;

class ExpansionPanelSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ExpansionPanelSettingsEditor(QWidget *parent = 0);

private Q_SLOTS:
    void updateWidget();

private:
    QtMaterialExpansionPanel *m_panel;
    QLineEdit *m_titleEdit;
    QLineEdit *m_subtitleEdit;
    QCheckBox *m_expandedCheckBox;
    QCheckBox *m_collapsibleCheckBox;
    QCheckBox *m_dividerCheckBox;
};

#endif // EXPANSIONPANELSETTINGSEDITOR_H
