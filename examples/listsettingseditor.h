#ifndef LISTSETTINGSEDITOR_H
#define LISTSETTINGSEDITOR_H

#include <QWidget>

class QCheckBox;
class QPushButton;
class QStandardItemModel;
class QtMaterialList;

class ListSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ListSettingsEditor(QWidget *parent = 0);
    ~ListSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    void populateModel();
    void setButtonColor(QPushButton *button, const QColor &color);

    QtMaterialList *const m_list;
    QStandardItemModel *const m_model;
    QCheckBox *const m_disabledCheckBox;
    QCheckBox *const m_denseCheckBox;
    QCheckBox *const m_useThemeColorsCheckBox;
    QCheckBox *const m_showDividerCheckBox;
    QPushButton *const m_textColorButton;
    QPushButton *const m_secondaryTextColorButton;
    QPushButton *const m_backgroundColorButton;
    QPushButton *const m_dividerColorButton;
    QPushButton *const m_selectedColorButton;
    QPushButton *const m_hoverColorButton;
};

#endif // LISTSETTINGSEDITOR_H
