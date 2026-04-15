#ifndef SEARCHBARSETTINGSEDITOR_H
#define SEARCHBARSETTINGSEDITOR_H

#include <QWidget>

class QCheckBox;
class QSpinBox;
class QtMaterialSearchBar;

class SearchBarSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit SearchBarSettingsEditor(QWidget *parent = 0);

private slots:
    void updateWidget();

private:
    QtMaterialSearchBar *m_searchBar;
    QCheckBox *m_themeColorsCheckBox;
    QCheckBox *m_collapsibleCheckBox;
    QCheckBox *m_navigationIconCheckBox;
    QCheckBox *m_trailingActionsCheckBox;
    QSpinBox *m_delaySpinBox;
};

#endif // SEARCHBARSETTINGSEDITOR_H
