#ifndef GRIDLISTSETTINGSEDITOR_H
#define GRIDLISTSETTINGSEDITOR_H

#include <QWidget>

class QCheckBox;
class QPushButton;
class QSpinBox;
class QStandardItemModel;
class QtMaterialGridList;

class GridListSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit GridListSettingsEditor(QWidget *parent = 0);
    ~GridListSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    void init();
    void populateModel();

    QtMaterialGridList *const m_gridList;
    QStandardItemModel *const m_model;
    QCheckBox *m_useThemeColorsCheckBox;
    QCheckBox *m_overlayTextCheckBox;
    QSpinBox *m_cellWidthSpinBox;
    QSpinBox *m_cellHeightSpinBox;
    QSpinBox *m_spacingSpinBox;
    QPushButton *m_backgroundColorButton;
    QPushButton *m_textColorButton;
};

#endif // GRIDLISTSETTINGSEDITOR_H
