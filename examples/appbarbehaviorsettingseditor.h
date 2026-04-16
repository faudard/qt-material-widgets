#ifndef APPBARBEHAVIORSETTINGSEDITOR_H
#define APPBARBEHAVIORSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialAppBar;
class QtMaterialTopAppBarScrollController;
class QtMaterialAppBarBehavior;
class QListWidget;
class QComboBox;
class QCheckBox;
class QScrollArea;

class AppBarBehaviorSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit AppBarBehaviorSettingsEditor(QWidget *parent = 0);
    ~AppBarBehaviorSettingsEditor();

private slots:
    void updateBehavior();

private:
    QtMaterialAppBar *m_appBar;
    QtMaterialTopAppBarScrollController *m_controller;
    QtMaterialAppBarBehavior *m_behavior;
    QScrollArea *m_scrollArea;
    QComboBox *m_modeCombo;
    QCheckBox *m_snapCheckBox;
};

#endif // APPBARBEHAVIORSETTINGSEDITOR_H
