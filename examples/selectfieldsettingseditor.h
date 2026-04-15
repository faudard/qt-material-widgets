#ifndef SELECTFIELDSETTINGSEDITOR_H
#define SELECTFIELDSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialSelectField;
class QCheckBox;
class QSpinBox;

class SelectFieldSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit SelectFieldSettingsEditor(QWidget *parent = 0);

private slots:
    void updateWidget();

private:
    QtMaterialSelectField *m_selectField;
    QCheckBox *m_showIndicator;
    QCheckBox *m_editable;
    QSpinBox *m_currentIndex;
};

#endif // SELECTFIELDSETTINGSEDITOR_H
