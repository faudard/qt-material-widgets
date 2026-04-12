#ifndef TREESETTINGSEDITOR_H
#define TREESETTINGSEDITOR_H

#include <QWidget>

class QCheckBox;
class QPushButton;
class QStandardItemModel;
class QtMaterialTree;

class TreeSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit TreeSettingsEditor(QWidget *parent = 0);
    ~TreeSettingsEditor();

private:
    void setupForm();
    void setupTree();

    QtMaterialTree *m_tree;
    QStandardItemModel *m_model;
    QCheckBox *m_useThemeColors;
    QCheckBox *m_dense;
    QCheckBox *m_showDivider;
    QPushButton *m_expandAll;
    QPushButton *m_collapseAll;
};

#endif // TREESETTINGSEDITOR_H
