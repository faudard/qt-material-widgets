#ifndef NAVIGATIONSETTINGSEDITOR_H
#define NAVIGATIONSETTINGSEDITOR_H

#include <QWidget>

class QCheckBox;
class QLabel;
class QComboBox;
class QtMaterialNavigationBar;

class NavigationSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit NavigationSettingsEditor(QWidget *parent = 0);
    ~NavigationSettingsEditor();

private slots:
    void updateWidget();
    void updateIndexLabel(int index);

private:
    QtMaterialNavigationBar *m_navigationBar;
    QCheckBox *m_useThemeColorsCheckBox;
    QCheckBox *m_shiftingCheckBox;
    QCheckBox *m_labelsVisibleCheckBox;
    QCheckBox *m_disableThirdItemCheckBox;
    QLabel *m_currentIndexLabel;
};

#endif // NAVIGATIONSETTINGSEDITOR_H
