#ifndef SPLITBUTTONSETTINGSEDITOR_H
#define SPLITBUTTONSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialSplitButton;
class QCheckBox;
class QLineEdit;
class QPushButton;

class SplitButtonSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit SplitButtonSettingsEditor(QWidget *parent = 0);

private slots:
    void updateWidget();

private:
    QtMaterialSplitButton *m_button;
    QCheckBox *m_useThemeColors;
    QCheckBox *m_dense;
    QLineEdit *m_textField;
};

#endif // SPLITBUTTONSETTINGSEDITOR_H
