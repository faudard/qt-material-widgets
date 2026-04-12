#include "treesettingseditor.h"

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStandardItemModel>
#include <QVBoxLayout>

#include "qtmaterialtree.h"
#include "qtmaterialtreeitem.h"

TreeSettingsEditor::TreeSettingsEditor(QWidget *parent)
    : QWidget(parent),
      m_tree(new QtMaterialTree),
      m_model(new QStandardItemModel(this)),
      m_useThemeColors(new QCheckBox(tr("Use theme colors"))),
      m_dense(new QCheckBox(tr("Dense"))),
      m_showDivider(new QCheckBox(tr("Show dividers"))),
      m_expandAll(new QPushButton(tr("Expand all"))),
      m_collapseAll(new QPushButton(tr("Collapse all")))
{
    setupForm();
    setupTree();
}

TreeSettingsEditor::~TreeSettingsEditor()
{
}

void TreeSettingsEditor::setupForm()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *controlsLayout = new QHBoxLayout;
    QLabel *title = new QLabel(tr("Material Tree"));

    QFont titleFont(font());
    titleFont.setPointSize(titleFont.pointSize() + 4);
    titleFont.setBold(true);
    title->setFont(titleFont);

    controlsLayout->addWidget(m_useThemeColors);
    controlsLayout->addWidget(m_dense);
    controlsLayout->addWidget(m_showDivider);
    controlsLayout->addSpacing(12);
    controlsLayout->addWidget(m_expandAll);
    controlsLayout->addWidget(m_collapseAll);
    controlsLayout->addStretch(1);

    mainLayout->addWidget(title);
    mainLayout->addLayout(controlsLayout);
    mainLayout->addWidget(m_tree, 1);
    setLayout(mainLayout);

    m_useThemeColors->setChecked(true);
    m_showDivider->setChecked(false);

    connect(m_useThemeColors, &QCheckBox::toggled,
            m_tree, &QtMaterialTree::setUseThemeColors);
    connect(m_dense, &QCheckBox::toggled,
            m_tree, &QtMaterialTree::setDense);
    connect(m_showDivider, &QCheckBox::toggled,
            m_tree, &QtMaterialTree::setShowDivider);
    connect(m_expandAll, &QPushButton::clicked,
            m_tree, &QtMaterialTree::expandAll);
    connect(m_collapseAll, &QPushButton::clicked,
            m_tree, &QtMaterialTree::collapseAll);
}

void TreeSettingsEditor::setupTree()
{
    m_model->setHorizontalHeaderLabels(QStringList() << tr("Navigation"));

    QtMaterialTreeItem *inbox = new QtMaterialTreeItem(tr("Inbox"), tr("4 unread threads"));
    inbox->setAvatar("IN", QColor(33, 150, 243));
    inbox->setTrailingText(tr("Today"));

    QtMaterialTreeItem *design = new QtMaterialTreeItem(tr("Design"), tr("3 active documents"));
    design->setAvatar("DE", QColor(0, 188, 212));
    design->setTrailingText(tr("Team"));

    QtMaterialTreeItem *components = new QtMaterialTreeItem(tr("Components"), tr("Table, List, Tree"));
    components->setAvatar("CO", QColor(156, 39, 176));
    components->setDivider(true);

    QtMaterialTreeItem *table = new QtMaterialTreeItem(tr("Table"), tr("PR #1 draft ready"));
    table->setTrailingText(tr("Done"));
    table->setAvatar("TB", QColor(63, 81, 181));

    QtMaterialTreeItem *list = new QtMaterialTreeItem(tr("List"), tr("PR #2 draft ready"));
    list->setTrailingText(tr("Done"));
    list->setAvatar("LI", QColor(76, 175, 80));

    QtMaterialTreeItem *listItem = new QtMaterialTreeItem(tr("List Item"), tr("PR #3 draft ready"));
    listItem->setTrailingText(tr("Done"));
    listItem->setAvatar("IT", QColor(255, 152, 0));

    QtMaterialTreeItem *treeItem = new QtMaterialTreeItem(tr("Tree Item"), tr("Current PR scope"));
    treeItem->setTrailingText(tr("Review"));
    treeItem->setAvatar("TR", QColor(244, 67, 54));
    treeItem->setDivider(true);

    components->appendRow(table);
    components->appendRow(list);
    components->appendRow(listItem);
    components->appendRow(treeItem);
    design->appendRow(components);

    QtMaterialTreeItem *archive = new QtMaterialTreeItem(tr("Archive"), tr("Older releases"));
    archive->setAvatar("AR", QColor(96, 125, 139));

    m_model->appendRow(inbox);
    m_model->appendRow(design);
    m_model->appendRow(archive);

    m_tree->setModel(m_model);
    m_tree->expand(design->index());
    m_tree->expand(components->index());
}
