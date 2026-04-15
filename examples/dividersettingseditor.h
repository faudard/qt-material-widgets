#ifndef DIVIDERSETTINGSEDITOR_H
#define DIVIDERSETTINGSEDITOR_H

#include <QWidget>

#include "ui_dividersettingsform.h"

class QtMaterialDivider;
class QtMaterialTextField;

class DividerSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit DividerSettingsEditor(QWidget *parent = 0);
    ~DividerSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::DividerSettingsForm *const ui;
    QtMaterialDivider       *const m_fullDivider;
    QtMaterialDivider       *const m_insetDivider;
    QtMaterialTextField     *const m_textField1;
    QtMaterialTextField     *const m_textField2;
};

#endif // DIVIDERSETTINGSEDITOR_H
