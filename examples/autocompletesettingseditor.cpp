#include "autocompletesettingseditor.h"

#include <QCheckBox>
#include <QColorDialog>
#include <QComboBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QToolButton>
#include <QVBoxLayout>

#include <qtmaterialautocomplete.h>

AutoCompleteSettingsEditor::AutoCompleteSettingsEditor(QWidget *parent)
    : QWidget(parent),
      m_useThemeColors(new QCheckBox("Use theme colors")),
      m_showLabel(new QCheckBox("Show label")),
      m_filterMode(new QComboBox),
      m_caseSensitivity(new QComboBox),
      m_maxVisibleItems(new QSlider(Qt::Horizontal)),
      m_menuBackgroundButton(new QToolButton),
      m_menuTextButton(new QToolButton),
      m_menuSelectedButton(new QToolButton),
      m_menuBackgroundValue(new QLabel),
      m_menuTextValue(new QLabel),
      m_menuSelectedValue(new QLabel),
      m_statusLabel(new QLabel("Selected: none")),
      m_autocomplete(new QtMaterialAutoComplete)
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    QWidget *controls = new QWidget;
    QWidget *canvas = new QWidget;
    canvas->setStyleSheet("QWidget { background: white; }");

    layout->addWidget(controls);
    layout->addWidget(canvas);
    layout->setContentsMargins(20, 20, 20, 20);

    QFormLayout *form = new QFormLayout;
    controls->setLayout(form);

    m_filterMode->addItem("Starts with", QtMaterialAutoComplete::StartsWithFilter);
    m_filterMode->addItem("Contains", QtMaterialAutoComplete::ContainsFilter);

    m_caseSensitivity->addItem("Case insensitive", Qt::CaseInsensitive);
    m_caseSensitivity->addItem("Case sensitive", Qt::CaseSensitive);

    m_maxVisibleItems->setRange(1, 10);

    m_menuBackgroundButton->setObjectName("menuBackgroundColorButton");
    m_menuTextButton->setObjectName("menuTextColorButton");
    m_menuSelectedButton->setObjectName("menuSelectedColorButton");
    m_menuBackgroundButton->setText("Select");
    m_menuTextButton->setText("Select");
    m_menuSelectedButton->setText("Select");

    QWidget *backgroundField = new QWidget;
    QHBoxLayout *backgroundLayout = new QHBoxLayout;
    backgroundField->setLayout(backgroundLayout);
    backgroundLayout->setContentsMargins(0, 0, 0, 0);
    backgroundLayout->addWidget(m_menuBackgroundButton);
    backgroundLayout->addWidget(m_menuBackgroundValue);

    QWidget *textField = new QWidget;
    QHBoxLayout *textLayout = new QHBoxLayout;
    textField->setLayout(textLayout);
    textLayout->setContentsMargins(0, 0, 0, 0);
    textLayout->addWidget(m_menuTextButton);
    textLayout->addWidget(m_menuTextValue);

    QWidget *selectedField = new QWidget;
    QHBoxLayout *selectedLayout = new QHBoxLayout;
    selectedField->setLayout(selectedLayout);
    selectedLayout->setContentsMargins(0, 0, 0, 0);
    selectedLayout->addWidget(m_menuSelectedButton);
    selectedLayout->addWidget(m_menuSelectedValue);

    form->addRow(QString(), m_useThemeColors);
    form->addRow(QString(), m_showLabel);
    form->addRow("Filter mode", m_filterMode);
    form->addRow("Case sensitivity", m_caseSensitivity);
    form->addRow("Max visible items", m_maxVisibleItems);
    form->addRow("Menu background", backgroundField);
    form->addRow("Menu text", textField);
    form->addRow("Menu selected", selectedField);

    QVBoxLayout *canvasLayout = new QVBoxLayout;
    canvas->setLayout(canvasLayout);
    canvasLayout->addStretch();
    canvasLayout->addWidget(m_autocomplete, 0, Qt::AlignCenter);
    canvasLayout->addWidget(m_statusLabel, 0, Qt::AlignCenter);
    canvasLayout->addStretch();
    canvas->setMinimumHeight(500);

    m_autocomplete->setFixedWidth(320);
    m_autocomplete->setLabel("State");
    m_autocomplete->setDataSource(QStringList()
        << "Alabama" << "Alaska" << "American Samoa" << "Arizona" << "Arkansas"
        << "California" << "Colorado" << "Connecticut" << "Delaware" << "District of Columbia"
        << "Florida" << "Georgia" << "Guam" << "Hawaii" << "Idaho" << "Illinois"
        << "Indiana" << "Iowa" << "Kansas" << "Kentucky" << "Louisiana" << "Maine"
        << "Maryland" << "Massachusetts" << "Michigan" << "Minnesota" << "Mississippi"
        << "Missouri" << "Montana" << "Nebraska" << "Nevada" << "New Hampshire"
        << "New Jersey" << "New Mexico" << "New York" << "North Carolina" << "North Dakota"
        << "Northern Marianas Islands" << "Ohio" << "Oklahoma" << "Oregon" << "Pennsylvania"
        << "Puerto Rico" << "Rhode Island" << "South Carolina" << "South Dakota" << "Tennessee"
        << "Texas" << "Utah" << "Vermont" << "Virginia" << "Virgin Islands" << "Washington"
        << "West Virginia" << "Wisconsin" << "Wyoming");

    connect(m_useThemeColors, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_showLabel, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_filterMode, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(m_caseSensitivity, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(m_maxVisibleItems, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_menuBackgroundButton, SIGNAL(pressed()), this, SLOT(selectColor()));
    connect(m_menuTextButton, SIGNAL(pressed()), this, SLOT(selectColor()));
    connect(m_menuSelectedButton, SIGNAL(pressed()), this, SLOT(selectColor()));
    connect(m_autocomplete, SIGNAL(itemSelected(QString)), this, SLOT(handleItemSelected(QString)));

    setupForm();
}

AutoCompleteSettingsEditor::~AutoCompleteSettingsEditor()
{
}

void AutoCompleteSettingsEditor::setupForm()
{
    m_useThemeColors->setChecked(m_autocomplete->useThemeColors());
    m_showLabel->setChecked(m_autocomplete->hasLabel());
    m_filterMode->setCurrentIndex(m_filterMode->findData(m_autocomplete->filterMode()));
    m_caseSensitivity->setCurrentIndex(m_caseSensitivity->findData(m_autocomplete->caseSensitivity()));
    m_maxVisibleItems->setValue(m_autocomplete->maxVisibleItems());
    m_menuBackgroundValue->setText(m_autocomplete->menuBackgroundColor().name(QColor::HexRgb));
    m_menuTextValue->setText(m_autocomplete->menuTextColor().name(QColor::HexRgb));
    m_menuSelectedValue->setText(m_autocomplete->menuSelectedColor().name(QColor::HexArgb));
}

void AutoCompleteSettingsEditor::updateWidget()
{
    m_autocomplete->setUseThemeColors(m_useThemeColors->isChecked());
    m_autocomplete->setShowLabel(m_showLabel->isChecked());
    m_autocomplete->setFilterMode(static_cast<QtMaterialAutoComplete::FilterMode>(
        m_filterMode->currentData().toInt()));
    m_autocomplete->setCaseSensitivity(static_cast<Qt::CaseSensitivity>(
        m_caseSensitivity->currentData().toInt()));
    m_autocomplete->setMaxVisibleItems(m_maxVisibleItems->value());
    setupForm();
}

void AutoCompleteSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (!dialog.exec()) {
        return;
    }

    const QColor color = dialog.selectedColor();
    const QString senderName = sender()->objectName();

    if (QStringLiteral("menuBackgroundColorButton") == senderName) {
        m_autocomplete->setMenuBackgroundColor(color);
    } else if (QStringLiteral("menuTextColorButton") == senderName) {
        m_autocomplete->setMenuTextColor(color);
    } else if (QStringLiteral("menuSelectedColorButton") == senderName) {
        m_autocomplete->setMenuSelectedColor(color);
    }

    setupForm();
}

void AutoCompleteSettingsEditor::handleItemSelected(const QString &text)
{
    m_statusLabel->setText(QStringLiteral("Selected: %1").arg(text));
}
