#include "listitemsettingseditor.h"

#include <QApplication>
#include <QCheckBox>
#include <QFormLayout>
#include <QPixmap>
#include <QStandardItemModel>
#include <QStyle>
#include <QVBoxLayout>

#include "qtmateriallist.h"
#include "qtmateriallistitem.h"

ListItemSettingsEditor::ListItemSettingsEditor(QWidget *parent)
    : QWidget(parent),
      m_list(new QtMaterialList),
      m_model(new QStandardItemModel(this)),
      m_denseCheckBox(new QCheckBox),
      m_useThemeColorsCheckBox(new QCheckBox),
      m_showDividerCheckBox(new QCheckBox)
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    QWidget *settingsWidget = new QWidget;
    QWidget *canvas = new QWidget;
    canvas->setStyleSheet("QWidget { background: white; }");

    layout->addWidget(settingsWidget);
    layout->addWidget(canvas);
    layout->setContentsMargins(20, 20, 20, 20);

    QFormLayout *form = new QFormLayout;
    settingsWidget->setLayout(form);

    form->addRow("Dense", m_denseCheckBox);
    form->addRow("Use theme colors", m_useThemeColorsCheckBox);
    form->addRow("Show dividers", m_showDividerCheckBox);

    QVBoxLayout *canvasLayout = new QVBoxLayout;
    canvas->setLayout(canvasLayout);
    canvasLayout->addWidget(m_list);
    canvasLayout->setContentsMargins(0, 0, 0, 0);

    m_list->setMinimumHeight(400);
    m_model->setItemPrototype(new QtMaterialListItem);
    m_list->setModel(m_model);

    populateModel();
    setupForm();

    connect(m_denseCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_useThemeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_showDividerCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
}

ListItemSettingsEditor::~ListItemSettingsEditor()
{
}

void ListItemSettingsEditor::populateModel()
{
    QtMaterialListItem *item = 0;

    item = new QtMaterialListItem("Ada Lovelace", "Drafting the first algorithm");
    item->setAvatar("A", QColor(63, 81, 181));
    item->setTrailingText("08:42");
    item->setDivider(true);
    m_model->appendRow(item);

    item = new QtMaterialListItem("Grace Hopper", "Compiler review ready for merge");
    item->setAvatar("G", QColor(0, 150, 136));
    item->setTrailingText("2m");
    item->setDivider(true);
    m_model->appendRow(item);

    item = new QtMaterialListItem(QApplication::style()->standardIcon(QStyle::SP_DirIcon),
                                  "Inbox",
                                  "24 unread messages");
    item->setTrailingText("24");
    item->setDivider(true);
    m_model->appendRow(item);

    item = new QtMaterialListItem(QApplication::style()->standardIcon(QStyle::SP_DialogApplyButton),
                                  "Starred",
                                  "Important items pinned to the top");
    item->setTrailingText("7");
    item->setDivider(true);
    m_model->appendRow(item);

    item = new QtMaterialListItem("Release notes", "Ready for product review");
    item->setAvatar("R", QColor(244, 67, 54));
    item->setTrailingText("Today");
    item->setDivider(true);
    m_model->appendRow(item);

    item = new QtMaterialListItem(QApplication::style()->standardIcon(QStyle::SP_FileDialogDetailedView),
                                  "Archive",
                                  "Last sync yesterday");
    item->setFullWidthDivider(false);
    item->setDivider(false);
    m_model->appendRow(item);

    if (m_model->rowCount() > 0) {
        m_list->setCurrentIndex(m_model->index(0, 0));
    }
}

void ListItemSettingsEditor::setupForm()
{
    m_denseCheckBox->setChecked(m_list->isDense());
    m_useThemeColorsCheckBox->setChecked(m_list->useThemeColors());
    m_showDividerCheckBox->setChecked(m_list->showDivider());
}

void ListItemSettingsEditor::updateWidget()
{
    m_list->setDense(m_denseCheckBox->isChecked());
    m_list->setUseThemeColors(m_useThemeColorsCheckBox->isChecked());
    m_list->setShowDivider(m_showDividerCheckBox->isChecked());
    setupForm();
}
