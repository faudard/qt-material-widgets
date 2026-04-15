#ifndef PAPERSETTINGSEDITOR_H
#define PAPERSETTINGSEDITOR_H

#include <QWidget>

class QCheckBox;
class QLabel;
class QSlider;
class QToolButton;
class QtMaterialPaper;

class PaperSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit PaperSettingsEditor(QWidget *parent = 0);
    ~PaperSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    QCheckBox *const m_useThemeColors;
    QSlider *const m_cornerRadius;
    QSlider *const m_elevation;
    QToolButton *const m_backgroundColorButton;
    QToolButton *const m_outlineColorButton;
    QLabel *const m_backgroundColorValue;
    QLabel *const m_outlineColorValue;
    QtMaterialPaper *const m_paper;
};

#endif // PAPERSETTINGSEDITOR_H
