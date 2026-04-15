#include "papersettingseditor.h"

#include <QCheckBox>
#include <QColorDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QToolButton>
#include <QVBoxLayout>

#include <qtmaterialpaper.h>

PaperSettingsEditor::PaperSettingsEditor(QWidget *parent)
    : QWidget(parent),
      m_useThemeColors(new QCheckBox("Use theme colors")),
      m_cornerRadius(new QSlider(Qt::Horizontal)),
      m_elevation(new QSlider(Qt::Horizontal)),
      m_backgroundColorButton(new QToolButton),
      m_outlineColorButton(new QToolButton),
      m_backgroundColorValue(new QLabel),
      m_outlineColorValue(new QLabel),
      m_paper(new QtMaterialPaper)
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    QWidget *controls = new QWidget;
    QWidget *canvas = new QWidget;
    canvas->setStyleSheet("QWidget { background: #f5f5f5; }");

    layout->addWidget(controls);
    layout->addWidget(canvas);
    layout->setContentsMargins(20, 20, 20, 20);

    QFormLayout *form = new QFormLayout;
    controls->setLayout(form);

    m_cornerRadius->setRange(0, 24);
    m_elevation->setRange(0, 12);
    m_backgroundColorButton->setObjectName("backgroundColorButton");
    m_backgroundColorButton->setText("Select");
    m_outlineColorButton->setObjectName("outlineColorButton");
    m_outlineColorButton->setText("Select");

    QWidget *backgroundField = new QWidget;
    QHBoxLayout *backgroundLayout = new QHBoxLayout;
    backgroundField->setLayout(backgroundLayout);
    backgroundLayout->setContentsMargins(0, 0, 0, 0);
    backgroundLayout->addWidget(m_backgroundColorButton);
    backgroundLayout->addWidget(m_backgroundColorValue);

    QWidget *outlineField = new QWidget;
    QHBoxLayout *outlineLayout = new QHBoxLayout;
    outlineField->setLayout(outlineLayout);
    outlineLayout->setContentsMargins(0, 0, 0, 0);
    outlineLayout->addWidget(m_outlineColorButton);
    outlineLayout->addWidget(m_outlineColorValue);

    form->addRow(QString(), m_useThemeColors);
    form->addRow("Corner radius", m_cornerRadius);
    form->addRow("Elevation", m_elevation);
    form->addRow("Background color", backgroundField);
    form->addRow("Outline color", outlineField);

    QVBoxLayout *canvasLayout = new QVBoxLayout;
    canvas->setLayout(canvasLayout);
    canvasLayout->addStretch();
    canvasLayout->addWidget(m_paper, 0, Qt::AlignCenter);
    canvasLayout->addStretch();

    QVBoxLayout *paperLayout = new QVBoxLayout;
    QLabel *title = new QLabel("QtMaterialPaper");
    QLabel *body = new QLabel("Elevated surfaces for menus, cards, dialogs, and custom content.");
    title->setAlignment(Qt::AlignCenter);
    body->setAlignment(Qt::AlignCenter);
    body->setWordWrap(true);
    m_paper->setLayout(paperLayout);
    paperLayout->addStretch();
    paperLayout->addWidget(title);
    paperLayout->addWidget(body);
    paperLayout->addStretch();

    connect(m_useThemeColors, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_cornerRadius, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_elevation, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_backgroundColorButton, SIGNAL(pressed()), this, SLOT(selectColor()));
    connect(m_outlineColorButton, SIGNAL(pressed()), this, SLOT(selectColor()));

    setupForm();
}

PaperSettingsEditor::~PaperSettingsEditor()
{
}

void PaperSettingsEditor::setupForm()
{
    m_useThemeColors->setChecked(m_paper->useThemeColors());
    m_cornerRadius->setValue(static_cast<int>(m_paper->cornerRadius()));
    m_elevation->setValue(m_paper->elevation());
    m_backgroundColorValue->setText(m_paper->backgroundColor().name(QColor::HexRgb));
    m_outlineColorValue->setText(m_paper->outlineColor().name(QColor::HexRgb));
}

void PaperSettingsEditor::updateWidget()
{
    m_paper->setUseThemeColors(m_useThemeColors->isChecked());
    m_paper->setCornerRadius(m_cornerRadius->value());
    m_paper->setElevation(m_elevation->value());
    setupForm();
}

void PaperSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (!dialog.exec()) {
        return;
    }

    const QColor color = dialog.selectedColor();
    const QString senderName = sender()->objectName();

    if (QStringLiteral("backgroundColorButton") == senderName) {
        m_paper->setBackgroundColor(color);
    } else if (QStringLiteral("outlineColorButton") == senderName) {
        m_paper->setOutlineColor(color);
    }

    setupForm();
}
