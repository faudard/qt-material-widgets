#ifndef LISTITEMSETTINGSEDITOR_H
#define LISTITEMSETTINGSEDITOR_H

#include <QWidget>

class QCheckBox;
class QStandardItemModel;
class QtMaterialList;

class ListItemSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ListItemSettingsEditor(QWidget *parent = 0);
    ~ListItemSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();

private:
    void populateModel();

    QtMaterialList *const m_list;
    QStandardItemModel *const m_model;
    QCheckBox *const m_denseCheckBox;
    QCheckBox *const m_useThemeColorsCheckBox;
    QCheckBox *const m_showDividerCheckBox;
};

#endif // LISTITEMSETTINGSEDITOR_H
