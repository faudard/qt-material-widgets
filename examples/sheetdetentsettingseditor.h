#ifndef SHEETDETENTSETTINGSEDITOR_H
#define SHEETDETENTSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialSheetDetentController;
class QFrame;
class QComboBox;
class QSpinBox;
class QPushButton;

class SheetDetentSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit SheetDetentSettingsEditor(QWidget *parent = 0);

private slots:
    void updateController();
    void setCollapsedDetent();
    void setHalfDetent();
    void setExpandedDetent();

private:
    QtMaterialSheetDetentController *m_controller;
    QFrame *m_sheet;
    QComboBox *m_orientationCombo;
    QSpinBox *m_collapsedSpin;
    QSpinBox *m_halfSpin;
    QSpinBox *m_expandedSpin;
    QPushButton *m_collapsedButton;
    QPushButton *m_halfButton;
    QPushButton *m_expandedButton;
};

#endif // SHEETDETENTSETTINGSEDITOR_H
