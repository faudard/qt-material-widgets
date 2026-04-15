#ifndef SUBHEADERSETTINGSEDITOR_H
#define SUBHEADERSETTINGSEDITOR_H

#include <QWidget>

class QCheckBox;
class QComboBox;
class QLineEdit;
class QSlider;
class QtMaterialSubheader;

class SubheaderSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit SubheaderSettingsEditor(QWidget *parent = 0);
    ~SubheaderSettingsEditor();

private slots:
    void updateWidget();

private:
    QtMaterialSubheader *m_subheader;
    QLineEdit *m_textField;
    QSlider *m_insetSlider;
    QCheckBox *m_denseCheckBox;
    QCheckBox *m_dividerCheckBox;
    QCheckBox *m_themeCheckBox;
    QComboBox *m_alignmentCombo;
};

#endif // SUBHEADERSETTINGSEDITOR_H
