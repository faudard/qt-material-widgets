#ifndef TOPAPPBARSCROLLSETTINGSEDITOR_H
#define TOPAPPBARSCROLLSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialTopAppBarScrollController;
class QtMaterialMediumTopAppBar;
class QScrollArea;
class QVBoxLayout;

class TopAppBarScrollSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit TopAppBarScrollSettingsEditor(QWidget *parent = 0);
    ~TopAppBarScrollSettingsEditor();

private:
    QtMaterialMediumTopAppBar *m_appBar;
    QtMaterialTopAppBarScrollController *m_controller;
    QScrollArea *m_scrollArea;
    QWidget *m_scrollContents;
    QVBoxLayout *m_scrollLayout;
};

#endif // TOPAPPBARSCROLLSETTINGSEDITOR_H
