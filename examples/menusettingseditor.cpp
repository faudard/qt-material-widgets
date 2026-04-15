#include "menusettingseditor.h"

#include <QAction>
#include <QCheckBox>
#include <QColorDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QToolButton>
#include <QVBoxLayout>
#include <QStyle>

#include <qtmaterialmenu.h>

MenuSettingsEditor::MenuSettingsEditor(QWidget *parent)
    : QWidget(parent),
      m_useThemeColors(new QCheckBox("Use theme colors")),
      m_dense(new QCheckBox("Dense mode")),
      m_elevation(new QSlider(Qt::Horizontal)),
      m_backgroundColorButton(new QToolButton),
      m_textColorButton(new QToolButton),
      m_selectedColorButton(new QToolButton),
      m_backgroundColorValue(new QLabel),
      m_textColorValue(new QLabel),
      m_selectedColorValue(new QLabel),
      m_statusLabel(new QLabel("Triggered: none")),
      m_showButton(new QPushButton("Show Menu")),
      m_menu(new QtMaterialMenu)
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

    m_elevation->setRange(0, 16);
    m_backgroundColorButton->setObjectName("backgroundColorButton");
    m_backgroundColorButton->setText("Select");
    m_textColorButton->setObjectName("textColorButton");
    m_textColorButton->setText("Select");
    m_selectedColorButton->setObjectName("selectedColorButton");
    m_selectedColorButton->setText("Select");

    QWidget *backgroundField = new QWidget;
    QHBoxLayout *backgroundLayout = new QHBoxLayout;
    backgroundField->setLayout(backgroundLayout);
    backgroundLayout->setContentsMargins(0, 0, 0, 0);
    backgroundLayout->addWidget(m_backgroundColorButton);
    backgroundLayout->addWidget(m_backgroundColorValue);

    QWidget *textField = new QWidget;
    QHBoxLayout *textLayout = new QHBoxLayout;
    textField->setLayout(textLayout);
    textLayout->setContentsMargins(0, 0, 0, 0);
    textLayout->addWidget(m_textColorButton);
    textLayout->addWidget(m_textColorValue);

    QWidget *selectedField = new QWidget;
    QHBoxLayout *selectedLayout = new QHBoxLayout;
    selectedField->setLayout(selectedLayout);
    selectedLayout->setContentsMargins(0, 0, 0, 0);
    selectedLayout->addWidget(m_selectedColorButton);
    selectedLayout->addWidget(m_selectedColorValue);

    form->addRow(QString(), m_useThemeColors);
    form->addRow(QString(), m_dense);
    form->addRow("Elevation", m_elevation);
    form->addRow("Background color", backgroundField);
    form->addRow("Text color", textField);
    form->addRow("Selected color", selectedField);

    QVBoxLayout *canvasLayout = new QVBoxLayout;
    canvas->setLayout(canvasLayout);
    canvasLayout->addStretch();
    canvasLayout->addWidget(m_showButton, 0, Qt::AlignCenter);
    canvasLayout->addWidget(m_statusLabel, 0, Qt::AlignCenter);
    canvasLayout->addStretch();

    populateMenu();

    connect(m_useThemeColors, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_dense, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_elevation, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_backgroundColorButton, SIGNAL(pressed()), this, SLOT(selectColor()));
    connect(m_textColorButton, SIGNAL(pressed()), this, SLOT(selectColor()));
    connect(m_selectedColorButton, SIGNAL(pressed()), this, SLOT(selectColor()));
    connect(m_showButton, SIGNAL(clicked()), this, SLOT(showMenu()));
    connect(m_menu, SIGNAL(triggered(QAction*)), this, SLOT(handleTriggered(QAction*)));

    setupForm();
}

MenuSettingsEditor::~MenuSettingsEditor()
{
}

void MenuSettingsEditor::setupForm()
{
    m_useThemeColors->setChecked(m_menu->useThemeColors());
    m_dense->setChecked(m_menu->isDense());
    m_elevation->setValue(m_menu->elevation());
    m_backgroundColorValue->setText(m_menu->backgroundColor().name(QColor::HexRgb));
    m_textColorValue->setText(m_menu->textColor().name(QColor::HexRgb));
    m_selectedColorValue->setText(m_menu->selectedColor().name(QColor::HexRgb));
}

void MenuSettingsEditor::updateWidget()
{
    m_menu->setUseThemeColors(m_useThemeColors->isChecked());
    m_menu->setDense(m_dense->isChecked());
    m_menu->setElevation(m_elevation->value());
    setupForm();
}

void MenuSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (!dialog.exec()) {
        return;
    }

    const QColor color = dialog.selectedColor();
    const QString senderName = sender()->objectName();

    if (QStringLiteral("backgroundColorButton") == senderName) {
        m_menu->setBackgroundColor(color);
    } else if (QStringLiteral("textColorButton") == senderName) {
        m_menu->setTextColor(color);
    } else if (QStringLiteral("selectedColorButton") == senderName) {
        m_menu->setSelectedColor(color);
    }

    setupForm();
}

void MenuSettingsEditor::showMenu()
{
    const QPoint globalPos = m_showButton->mapToGlobal(QPoint(0, m_showButton->height() + 4));
    m_menu->popup(globalPos);
}

void MenuSettingsEditor::handleTriggered(QAction *action)
{
    if (!action) {
        return;
    }

    m_statusLabel->setText(QStringLiteral("Triggered: %1").arg(action->text()));
}

void MenuSettingsEditor::populateMenu()
{
    m_menu->clearMenuItems();
    m_menu->addMenuItem(style()->standardIcon(QStyle::SP_DialogOpenButton), "Open");
    m_menu->addMenuItem(style()->standardIcon(QStyle::SP_DialogSaveButton), "Save");
    m_menu->addSeparator();
    QAction *disabledAction = m_menu->addMenuItem("Disabled item");
    disabledAction->setEnabled(false);
    m_menu->addMenuItem("Delete");
}
