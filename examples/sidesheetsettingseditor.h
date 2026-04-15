#ifndef SIDESHEETSETTINGSEDITOR_H
#define SIDESHEETSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialRaisedButton;
class QtMaterialSideSheet;

class SideSheetSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit SideSheetSettingsEditor(QWidget *parent = 0);

private slots:
    void toggleSheet();

private:
    QtMaterialRaisedButton *m_toggleButton;
    QtMaterialSideSheet *m_sheet;
};

#endif // SIDESHEETSETTINGSEDITOR_H
