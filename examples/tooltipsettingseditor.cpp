#include "tooltipsettingseditor.h"

#include "qtmaterialraisedbutton.h"
#include "qtmaterialtooltip.h"

#include <QCheckBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QVBoxLayout>

TooltipSettingsEditor::TooltipSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *row = new QHBoxLayout;
    QWidget *canvas = new QWidget;
    canvas->setMinimumHeight(220);
    canvas->setStyleSheet("background:white;");
    QVBoxLayout *canvasLayout = new QVBoxLayout(canvas);
    canvasLayout->addStretch();

    m_button = new QtMaterialRaisedButton("Hover me", canvas);
    m_button->setMaximumWidth(180);
    canvasLayout->addWidget(m_button, 0, Qt::AlignCenter);
    canvasLayout->addStretch();

    m_tooltip = new QtMaterialTooltip(canvas);
    m_tooltip->setTarget(m_button);
    m_tooltip->setText("Material tooltip");

    QWidget *controls = new QWidget;
    QFormLayout *form = new QFormLayout(controls);

    m_themeColors = new QCheckBox;
    m_themeColors->setChecked(true);
    m_fontSize = new QSpinBox;
    m_fontSize->setRange(8, 24);
    m_fontSize->setValue(10);
    m_padding = new QSpinBox;
    m_padding->setRange(4, 32);
    m_padding->setValue(12);
    m_autoHide = new QSpinBox;
    m_autoHide->setRange(0, 10000);
    m_autoHide->setSingleStep(250);
    m_autoHide->setValue(2500);

    form->addRow("Use theme colors", m_themeColors);
    form->addRow("Font size", m_fontSize);
    form->addRow("Padding", m_padding);
    form->addRow("Auto hide (ms)", m_autoHide);

    row->addWidget(canvas, 1);
    row->addWidget(controls);
    mainLayout->addLayout(row);

    QObject::connect(m_themeColors, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    QObject::connect(m_fontSize, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    QObject::connect(m_padding, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    QObject::connect(m_autoHide, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));

    updateWidget();
}

void TooltipSettingsEditor::updateWidget()
{
    m_tooltip->setUseThemeColors(m_themeColors->isChecked());
    m_tooltip->setFontSize(m_fontSize->value());
    m_tooltip->setPadding(m_padding->value());
    m_tooltip->setAutoHideDuration(m_autoHide->value());
}
