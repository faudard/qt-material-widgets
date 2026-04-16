#ifndef BOTTOMSHEETVARIANTSSETTINGSEDITOR_H
#define BOTTOMSHEETVARIANTSSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialModalBottomSheet;
class QtMaterialStandardBottomSheet;
class QPushButton;
class QCheckBox;
class QSlider;

class BottomSheetVariantsSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit BottomSheetVariantsSettingsEditor(QWidget *parent = 0);

private slots:
    void updateWidgets();

private:
    QtMaterialModalBottomSheet *m_modalSheet;
    QtMaterialStandardBottomSheet *m_standardSheet;
    QPushButton *m_openButton;
    QCheckBox *m_modalTheme;
    QCheckBox *m_standardExpanded;
    QSlider *m_heightSlider;
};

#endif // BOTTOMSHEETVARIANTSSETTINGSEDITOR_H
