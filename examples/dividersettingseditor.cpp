#include "dividersettingseditor.h"

#include <QColorDialog>
#include <QLabel>
#include <QVBoxLayout>

#include <qtmaterialdivider.h>
#include <qtmaterialtextfield.h>

DividerSettingsEditor::DividerSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::DividerSettingsForm),
      m_fullDivider(new QtMaterialDivider),
      m_insetDivider(new QtMaterialDivider),
      m_textField1(new QtMaterialTextField),
      m_textField2(new QtMaterialTextField)
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    QWidget *widget = new QWidget;
    layout->addWidget(widget);

    QWidget *canvas = new QWidget;
    canvas->setStyleSheet("QWidget { background: white; }");
    layout->addWidget(canvas);

    ui->setupUi(widget);
    layout->setContentsMargins(20, 20, 20, 20);

    m_textField1->setLabel("First Name");
    m_textField1->setText("Ada");
    // m_textField1->setShowUnderline(false); TODO

    m_textField2->setLabel("Middle Name");
    m_textField2->setText("Lovelace");
    // m_textField2->setShowUnderline(false); TODO

    QLabel *fullWidthLabel = new QLabel("Full-width divider");
    QLabel *insetLabel = new QLabel("Inset divider");

    layout = new QVBoxLayout;
    layout->setContentsMargins(24, 24, 24, 24);
    canvas->setLayout(layout);

    layout->addWidget(fullWidthLabel);
    layout->addWidget(m_textField1);
    layout->addWidget(m_fullDivider);
    layout->addWidget(m_textField2);
    layout->addSpacing(24);
    layout->addWidget(insetLabel);
    layout->addWidget(m_insetDivider);
    layout->addStretch();

    setupForm();

    connect(ui->disabledCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->useThemeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->thicknessSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui->insetStartSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui->insetEndSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui->colorToolButton, SIGNAL(pressed()), this, SLOT(selectColor()));
}

DividerSettingsEditor::~DividerSettingsEditor()
{
    delete ui;
}

void DividerSettingsEditor::setupForm()
{
    ui->disabledCheckBox->setChecked(!m_insetDivider->isEnabled());
    ui->useThemeColorsCheckBox->setChecked(m_insetDivider->useThemeColors());
    ui->thicknessSpinBox->setValue(m_insetDivider->thickness());
    ui->insetStartSpinBox->setValue(m_insetDivider->insetStart());
    ui->insetEndSpinBox->setValue(m_insetDivider->insetEnd());
    ui->colorLineEdit->setText(m_insetDivider->color().name(QColor::HexRgb));
}

void DividerSettingsEditor::updateWidget()
{
    const bool disabled = ui->disabledCheckBox->isChecked();
    const bool useThemeColors = ui->useThemeColorsCheckBox->isChecked();
    const int thickness = ui->thicknessSpinBox->value();

    m_fullDivider->setDisabled(disabled);
    m_insetDivider->setDisabled(disabled);

    m_fullDivider->setUseThemeColors(useThemeColors);
    m_insetDivider->setUseThemeColors(useThemeColors);

    m_fullDivider->setThickness(thickness);
    m_insetDivider->setThickness(thickness);

    m_fullDivider->setInsetStart(0);
    m_fullDivider->setInsetEnd(0);

    m_insetDivider->setInsetStart(ui->insetStartSpinBox->value());
    m_insetDivider->setInsetEnd(ui->insetEndSpinBox->value());

    setupForm();
}

void DividerSettingsEditor::selectColor()
{
    QColorDialog dialog(this);

    if (dialog.exec()) {
        const QColor color = dialog.selectedColor();

        m_fullDivider->setColor(color);
        m_insetDivider->setColor(color);

        ui->colorLineEdit->setText(color.name(QColor::HexRgb));
    }

    setupForm();
}
