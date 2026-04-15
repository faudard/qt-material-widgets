#ifndef AUTOCOMPLETESETTINGSEDITOR_H
#define AUTOCOMPLETESETTINGSEDITOR_H

#include <QWidget>

class QCheckBox;
class QComboBox;
class QLabel;
class QSlider;
class QToolButton;
class QtMaterialAutoComplete;

class AutoCompleteSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit AutoCompleteSettingsEditor(QWidget *parent = 0);
    ~AutoCompleteSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();
    void handleItemSelected(const QString &text);

private:
    QCheckBox *const m_useThemeColors;
    QCheckBox *const m_showLabel;
    QComboBox *const m_filterMode;
    QComboBox *const m_caseSensitivity;
    QSlider *const m_maxVisibleItems;
    QToolButton *const m_menuBackgroundButton;
    QToolButton *const m_menuTextButton;
    QToolButton *const m_menuSelectedButton;
    QLabel *const m_menuBackgroundValue;
    QLabel *const m_menuTextValue;
    QLabel *const m_menuSelectedValue;
    QLabel *const m_statusLabel;
    QtMaterialAutoComplete *const m_autocomplete;
};

#endif // AUTOCOMPLETESETTINGSEDITOR_H
