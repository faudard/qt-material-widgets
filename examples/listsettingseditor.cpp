#include "listsettingseditor.h"

#include <QApplication>
#include <QCheckBox>
#include <QColorDialog>
#include <QFormLayout>
#include <QPushButton>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QStyle>
#include <QVBoxLayout>

#include "qtmateriallist.h"

ListSettingsEditor::ListSettingsEditor(QWidget *parent)
    : QWidget(parent),
      m_list(new QtMaterialList),
      m_model(new QStandardItemModel(this)),
      m_disabledCheckBox(new QCheckBox),
      m_denseCheckBox(new QCheckBox),
      m_useThemeColorsCheckBox(new QCheckBox),
      m_showDividerCheckBox(new QCheckBox),
      m_textColorButton(new QPushButton),
      m_secondaryTextColorButton(new QPushButton),
      m_backgroundColorButton(new QPushButton),
      m_dividerColorButton(new QPushButton),
      m_selectedColorButton(new QPushButton),
      m_hoverColorButton(new QPushButton)
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

    form->addRow("Disabled", m_disabledCheckBox);
    form->addRow("Dense", m_denseCheckBox);
    form->addRow("Use theme colors", m_useThemeColorsCheckBox);
    form->addRow("Show dividers", m_showDividerCheckBox);
    form->addRow("Text color", m_textColorButton);
    form->addRow("Secondary text color", m_secondaryTextColorButton);
    form->addRow("Background color", m_backgroundColorButton);
    form->addRow("Divider color", m_dividerColorButton);
    form->addRow("Selected color", m_selectedColorButton);
    form->addRow("Hover color", m_hoverColorButton);

    m_textColorButton->setObjectName("textColor");
    m_secondaryTextColorButton->setObjectName("secondaryTextColor");
    m_backgroundColorButton->setObjectName("backgroundColor");
    m_dividerColorButton->setObjectName("dividerColor");
    m_selectedColorButton->setObjectName("selectedColor");
    m_hoverColorButton->setObjectName("hoverColor");

    QVBoxLayout *canvasLayout = new QVBoxLayout;
    canvas->setLayout(canvasLayout);
    canvasLayout->addWidget(m_list);
    canvasLayout->setContentsMargins(0, 0, 0, 0);

    m_list->setMinimumHeight(360);
    m_list->setModel(m_model);

    populateModel();
    setupForm();

    connect(m_disabledCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_denseCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_useThemeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_showDividerCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));

    connect(m_textColorButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(m_secondaryTextColorButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(m_backgroundColorButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(m_dividerColorButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(m_selectedColorButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(m_hoverColorButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
}

ListSettingsEditor::~ListSettingsEditor()
{
}

void ListSettingsEditor::populateModel()
{
    struct RowData
    {
        const char *title;
        const char *subtitle;
        QStyle::StandardPixmap icon;
        bool divider;
    };

    const RowData rows[] = {
        { "Inbox", "24 new messages", QStyle::SP_DirIcon, true },
        { "Starred", "Important items", QStyle::SP_DialogApplyButton, true },
        { "Sent mail", "Last sync just now", QStyle::SP_ArrowForward, true },
        { "Drafts", "Needs review", QStyle::SP_FileIcon, true },
        { "Trash", "14 items", QStyle::SP_TrashIcon, false }
    };

    for (unsigned int i = 0; i < sizeof(rows) / sizeof(rows[0]); ++i) {
        QStandardItem *item = new QStandardItem(QString::fromLatin1(rows[i].title));
        item->setData(QString::fromLatin1(rows[i].subtitle), QtMaterialList::SecondaryTextRole);
        item->setData(rows[i].divider, QtMaterialList::DividerRole);
        item->setData(QApplication::style()->standardIcon(rows[i].icon), Qt::DecorationRole);
        item->setEditable(false);
        m_model->appendRow(item);
    }

    if (m_model->rowCount() > 0) {
        m_list->setCurrentIndex(m_model->index(0, 0));
    }
}

void ListSettingsEditor::setupForm()
{
    m_disabledCheckBox->setChecked(!m_list->isEnabled());
    m_denseCheckBox->setChecked(m_list->isDense());
    m_useThemeColorsCheckBox->setChecked(m_list->useThemeColors());
    m_showDividerCheckBox->setChecked(m_list->showDivider());

    setButtonColor(m_textColorButton, m_list->textColor());
    setButtonColor(m_secondaryTextColorButton, m_list->secondaryTextColor());
    setButtonColor(m_backgroundColorButton, m_list->backgroundColor());
    setButtonColor(m_dividerColorButton, m_list->dividerColor());
    setButtonColor(m_selectedColorButton, m_list->selectedColor());
    setButtonColor(m_hoverColorButton, m_list->hoverColor());
}

void ListSettingsEditor::updateWidget()
{
    m_list->setDisabled(m_disabledCheckBox->isChecked());
    m_list->setDense(m_denseCheckBox->isChecked());
    m_list->setUseThemeColors(m_useThemeColorsCheckBox->isChecked());
    m_list->setShowDivider(m_showDividerCheckBox->isChecked());
    setupForm();
}

void ListSettingsEditor::selectColor()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());

    if (!button) {
        return;
    }

    QColor currentColor;

    if ("textColor" == button->objectName()) {
        currentColor = m_list->textColor();
    } else if ("secondaryTextColor" == button->objectName()) {
        currentColor = m_list->secondaryTextColor();
    } else if ("backgroundColor" == button->objectName()) {
        currentColor = m_list->backgroundColor();
    } else if ("dividerColor" == button->objectName()) {
        currentColor = m_list->dividerColor();
    } else if ("selectedColor" == button->objectName()) {
        currentColor = m_list->selectedColor();
    } else if ("hoverColor" == button->objectName()) {
        currentColor = m_list->hoverColor();
    }

    const QColor color = QColorDialog::getColor(currentColor, this);

    if (!color.isValid()) {
        return;
    }

    if ("textColor" == button->objectName()) {
        m_list->setTextColor(color);
    } else if ("secondaryTextColor" == button->objectName()) {
        m_list->setSecondaryTextColor(color);
    } else if ("backgroundColor" == button->objectName()) {
        m_list->setBackgroundColor(color);
    } else if ("dividerColor" == button->objectName()) {
        m_list->setDividerColor(color);
    } else if ("selectedColor" == button->objectName()) {
        m_list->setSelectedColor(color);
    } else if ("hoverColor" == button->objectName()) {
        m_list->setHoverColor(color);
    }

    m_useThemeColorsCheckBox->setChecked(false);
    setupForm();
}

void ListSettingsEditor::setButtonColor(QPushButton *button, const QColor &color)
{
    if (!button) {
        return;
    }

    button->setText(color.name(QColor::HexRgb));
    button->setStyleSheet(QString(
        "QPushButton {"
        "background-color: %1;"
        "border: 1px solid rgba(0, 0, 0, 32);"
        "padding: 6px 12px;"
        "}"
    ).arg(color.name(QColor::HexRgb)));
}
