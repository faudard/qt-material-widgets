#ifndef SEARCHVIEWSETTINGSEDITOR_H
#define SEARCHVIEWSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialSearchView;

class SearchViewSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit SearchViewSettingsEditor(QWidget *parent = 0);

private:
    QtMaterialSearchView *m_searchView;
};

#endif // SEARCHVIEWSETTINGSEDITOR_H
