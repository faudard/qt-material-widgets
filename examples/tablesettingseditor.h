#ifndef TABLESETTINGSEDITOR_H
#define TABLESETTINGSEDITOR_H

#include <QWidget>

class QCheckBox;
class QPushButton;
class QStandardItemModel;
class QtMaterialTable;

class TableSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit TableSettingsEditor(QWidget *parent = 0);
    ~TableSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    void populateModel();
    void setButtonColor(QPushButton *button, const QColor &color);

    QtMaterialTable *const m_table;
    QStandardItemModel *const m_model;
    QCheckBox *const m_disabledCheckBox;
    QCheckBox *const m_denseCheckBox;
    QCheckBox *const m_useThemeColorsCheckBox;
    QPushButton *const m_headerColorButton;
    QPushButton *const m_textColorButton;
    QPushButton *const m_backgroundColorButton;
    QPushButton *const m_alternateBackgroundColorButton;
    QPushButton *const m_gridColorButton;
    QPushButton *const m_selectedRowColorButton;
    QPushButton *const m_hoverRowColorButton;
};

#endif // TABLESETTINGSEDITOR_H
