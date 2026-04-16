#ifndef CHIPSETTINGSEDITOR_H
#define CHIPSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialChip;
class QButtonGroup;
class QCheckBox;
class QPushButton;

class ChipSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ChipSettingsEditor(QWidget *parent = 0);

private slots:
    void updateWidget();
    void restoreRemovableChip();

private:
    QtMaterialChip *m_actionChip;
    QtMaterialChip *m_filterChip;
    QtMaterialChip *m_choiceChip1;
    QtMaterialChip *m_choiceChip2;
    QtMaterialChip *m_choiceChip3;
    QtMaterialChip *m_removableChip;

    QButtonGroup *m_choiceGroup;

    QCheckBox *m_checkableCheckBox;
    QCheckBox *m_checkedCheckBox;
    QCheckBox *m_closableCheckBox;
    QCheckBox *m_leadingIconCheckBox;
    QCheckBox *m_trailingIconCheckBox;
    QCheckBox *m_themeColorsCheckBox;
    QPushButton *m_restoreButton;
};

#endif // CHIPSETTINGSEDITOR_H
