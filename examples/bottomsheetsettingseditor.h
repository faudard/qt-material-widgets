#ifndef BOTTOMSHEETSETTINGSEDITOR_H
#define BOTTOMSHEETSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialRaisedButton;
class QtMaterialBottomSheet;

class BottomSheetSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit BottomSheetSettingsEditor(QWidget *parent = 0);

private slots:
    void showBottomSheet();

private:
    QtMaterialRaisedButton *m_openButton;
    QtMaterialBottomSheet *m_bottomSheet;
};

#endif // BOTTOMSHEETSETTINGSEDITOR_H
