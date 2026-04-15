#ifndef TOOLBARSETTINGSEDITOR_H
#define TOOLBARSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialToolBar;
class QtMaterialIconButton;
class QCheckBox;
class QLineEdit;

class ToolbarSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ToolbarSettingsEditor(QWidget *parent = 0);
    ~ToolbarSettingsEditor();

protected slots:
    void updateWidget();
    void selectColor();

private:
    QtMaterialToolBar *const m_toolBar;
    QtMaterialIconButton *const m_navButton;
    QtMaterialIconButton *const m_searchButton;
    QtMaterialIconButton *const m_moreButton;
    QCheckBox *m_useThemeColorsCheckBox;
    QCheckBox *m_denseCheckBox;
    QCheckBox *m_centeredTitleCheckBox;
    QLineEdit *m_titleLineEdit;
    QLineEdit *m_subtitleLineEdit;
    QLineEdit *m_backgroundColorLineEdit;
};

#endif // TOOLBARSETTINGSEDITOR_H
