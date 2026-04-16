#include "bottomsheetvariantssettingseditor.h"
#include "qtmaterialmodalbottomsheet.h"
#include "qtmaterialstandardbottomsheet.h"

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>

BottomSheetVariantsSettingsEditor::BottomSheetVariantsSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    m_modalSheet = new QtMaterialModalBottomSheet(this);
    m_standardSheet = new QtMaterialStandardBottomSheet(this);
    m_openButton = new QPushButton(QStringLiteral("Open modal bottom sheet"), this);
    m_modalTheme = new QCheckBox(QStringLiteral("Use theme colors"), this);
    m_standardExpanded = new QCheckBox(QStringLiteral("Standard sheet expanded"), this);
    m_heightSlider = new QSlider(Qt::Horizontal, this);

    m_modalTheme->setChecked(true);
    m_standardExpanded->setChecked(true);
    m_heightSlider->setRange(160, 420);
    m_heightSlider->setValue(280);

    QVBoxLayout *controls = new QVBoxLayout;
    controls->addWidget(m_openButton);
    controls->addWidget(m_modalTheme);
    controls->addWidget(m_standardExpanded);
    controls->addWidget(new QLabel(QStringLiteral("Sheet height"), this));
    controls->addWidget(m_heightSlider);
    controls->addStretch(1);

    QVBoxLayout *demo = new QVBoxLayout;
    demo->addWidget(new QLabel(QStringLiteral("Standard bottom sheet"), this));
    demo->addWidget(m_standardSheet);
    demo->addStretch(1);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addLayout(controls);
    layout->addLayout(demo, 1);

    connect(m_openButton, &QPushButton::clicked, m_modalSheet, &QtMaterialModalBottomSheet::open);
    connect(m_modalTheme, &QCheckBox::toggled, this, &BottomSheetVariantsSettingsEditor::updateWidgets);
    connect(m_standardExpanded, &QCheckBox::toggled, this, &BottomSheetVariantsSettingsEditor::updateWidgets);
    connect(m_heightSlider, &QSlider::valueChanged, this, &BottomSheetVariantsSettingsEditor::updateWidgets);

    updateWidgets();
}

void BottomSheetVariantsSettingsEditor::updateWidgets()
{
    m_modalSheet->setUseThemeColors(m_modalTheme->isChecked());
    m_modalSheet->setSheetHeight(m_heightSlider->value());

    m_standardSheet->setExpanded(m_standardExpanded->isChecked());
    m_standardSheet->setSheetHeight(m_heightSlider->value());
}
