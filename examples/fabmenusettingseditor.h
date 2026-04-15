#ifndef FABMENUSETTINGSEDITOR_H
#define FABMENUSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialFabMenu;
class QCheckBox;
class QSpinBox;
class QComboBox;

class FabMenuSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit FabMenuSettingsEditor(QWidget *parent = 0);

private slots:
    void updateWidget();

private:
    QtMaterialFabMenu *m_menu;
    QCheckBox *m_labelsVisible;
    QSpinBox *m_spacing;
    QComboBox *m_corner;
};

#endif // FABMENUSETTINGSEDITOR_H