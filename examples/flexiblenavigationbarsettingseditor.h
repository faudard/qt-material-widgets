#ifndef FLEXIBLENAVIGATIONBARSETTINGSEDITOR_H
#define FLEXIBLENAVIGATIONBARSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialFlexibleNavigationBar;

class FlexibleNavigationBarSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit FlexibleNavigationBarSettingsEditor(QWidget *parent = 0);

private:
    QtMaterialFlexibleNavigationBar *m_bar;
};

#endif // FLEXIBLENAVIGATIONBARSETTINGSEDITOR_H
