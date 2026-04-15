#ifndef SEARCHFIELDSETTINGSEDITOR_H
#define SEARCHFIELDSETTINGSEDITOR_H

#include <QWidget>

class QCheckBox;
class QSpinBox;
class QLabel;
class QtMaterialSearchField;

class SearchFieldSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit SearchFieldSettingsEditor(QWidget *parent = 0);

private slots:
    void updateWidget();
    void handleSearch(const QString &text);
    void handleCleared();

private:
    QtMaterialSearchField *m_searchField;
    QCheckBox *m_showSearchIcon;
    QCheckBox *m_showClearButton;
    QCheckBox *m_useThemeColors;
    QSpinBox *m_searchDelay;
    QLabel *m_status;
};

#endif // SEARCHFIELDSETTINGSEDITOR_H
