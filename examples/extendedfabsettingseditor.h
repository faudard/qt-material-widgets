#ifndef EXTENDEDFABSETTINGSEDITOR_H
#define EXTENDEDFABSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialExtendedFloatingActionButton;
class QCheckBox;
class QLineEdit;
class QVBoxLayout;

class ExtendedFabSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ExtendedFabSettingsEditor(QWidget *parent = 0);

private slots:
    void updateWidget();

private:
    QtMaterialExtendedFloatingActionButton *m_fab;
    QCheckBox *m_collapsed;
    QCheckBox *m_checkable;
    QCheckBox *m_checked;
    QLineEdit *m_text;
};

#endif // EXTENDEDFABSETTINGSEDITOR_H
