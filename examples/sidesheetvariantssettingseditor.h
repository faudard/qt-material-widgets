#ifndef SIDESHEETVARIANTSSETTINGSEDITOR_H
#define SIDESHEETVARIANTSSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialModalSideSheet;
class QtMaterialStandardSideSheet;
class QPushButton;
class QCheckBox;

class SideSheetVariantsSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit SideSheetVariantsSettingsEditor(QWidget *parent = 0);

private slots:
    void openModalSheet();
    void updateStates();

private:
    QtMaterialModalSideSheet *m_modalSheet;
    QtMaterialStandardSideSheet *m_standardSheet;
    QPushButton *m_openButton;
    QCheckBox *m_dismissOverlayCheckBox;
    QCheckBox *m_standardExpandedCheckBox;
};

#endif // SIDESHEETVARIANTSSETTINGSEDITOR_H
