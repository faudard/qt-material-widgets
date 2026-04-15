#ifndef MENUSETTINGSEDITOR_H
#define MENUSETTINGSEDITOR_H

#include <QWidget>

class QAction;
class QCheckBox;
class QLabel;
class QPushButton;
class QSlider;
class QToolButton;
class QtMaterialMenu;

class MenuSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit MenuSettingsEditor(QWidget *parent = 0);
    ~MenuSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();
    void showMenu();
    void handleTriggered(QAction *action);

private:
    void populateMenu();

    QCheckBox *const m_useThemeColors;
    QCheckBox *const m_dense;
    QSlider *const m_elevation;
    QToolButton *const m_backgroundColorButton;
    QToolButton *const m_textColorButton;
    QToolButton *const m_selectedColorButton;
    QLabel *const m_backgroundColorValue;
    QLabel *const m_textColorValue;
    QLabel *const m_selectedColorValue;
    QLabel *const m_statusLabel;
    QPushButton *const m_showButton;
    QtMaterialMenu *const m_menu;
};

#endif // MENUSETTINGSEDITOR_H
