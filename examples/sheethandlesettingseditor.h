#ifndef SHEETHANDLESETTINGSEDITOR_H
#define SHEETHANDLESETTINGSEDITOR_H

#include <QWidget>

class QtMaterialSheetHandle;
class QCheckBox;
class QSpinBox;

class SheetHandleSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit SheetHandleSettingsEditor(QWidget *parent = 0);

private slots:
    void updateWidget();

private:
    QtMaterialSheetHandle *m_handle;
    QCheckBox *m_cycleCheckBox;
    QSpinBox *m_widthSpinBox;
    QSpinBox *m_heightSpinBox;
    QSpinBox *m_targetSpinBox;
};

#endif // SHEETHANDLESETTINGSEDITOR_H
