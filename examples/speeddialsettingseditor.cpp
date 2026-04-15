#include "speeddialsettingseditor.h"
#include "qtmaterialspeeddial.h"

#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QIcon>

SpeedDialSettingsEditor::SpeedDialSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    m_speedDial = new QtMaterialSpeedDial(this);
    m_speedDial->addAction(QIcon::fromTheme("document-new"), "New");
    m_speedDial->addAction(QIcon::fromTheme("document-open"), "Open");
    m_speedDial->addAction(QIcon::fromTheme("document-save"), "Save");

    m_themeColorsCheckBox = new QCheckBox("Use theme colors");
    m_themeColorsCheckBox->setChecked(true);

    m_labelsVisibleCheckBox = new QCheckBox("Show labels");
    m_labelsVisibleCheckBox->setChecked(true);

    m_spacingSpinBox = new QSpinBox;
    m_spacingSpinBox->setRange(0, 48);
    m_spacingSpinBox->setValue(12);

    m_cornerComboBox = new QComboBox;
    m_cornerComboBox->addItem("Bottom Right", Qt::BottomRightCorner);
    m_cornerComboBox->addItem("Bottom Left", Qt::BottomLeftCorner);
    m_cornerComboBox->addItem("Top Right", Qt::TopRightCorner);
    m_cornerComboBox->addItem("Top Left", Qt::TopLeftCorner);

    QVBoxLayout *controls = new QVBoxLayout;
    controls->addWidget(m_themeColorsCheckBox);
    controls->addWidget(m_labelsVisibleCheckBox);
    controls->addWidget(new QLabel("Action spacing"));
    controls->addWidget(m_spacingSpinBox);
    controls->addWidget(new QLabel("Anchor corner"));
    controls->addWidget(m_cornerComboBox);
    controls->addStretch(1);

    QWidget *canvas = new QWidget;
    canvas->setMinimumSize(420, 320);
    canvas->setStyleSheet("background: white;");
    m_speedDial->setParent(canvas);
    m_speedDial->setGeometry(canvas->rect());

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addLayout(controls);
    layout->addWidget(canvas, 1);

    connect(m_themeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_labelsVisibleCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_spacingSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_cornerComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));

    updateWidget();
}

void SpeedDialSettingsEditor::updateWidget()
{
    m_speedDial->setUseThemeColors(m_themeColorsCheckBox->isChecked());
    m_speedDial->setLabelsVisible(m_labelsVisibleCheckBox->isChecked());
    m_speedDial->setActionSpacing(m_spacingSpinBox->value());
    m_speedDial->setAnchorCorner(static_cast<Qt::Corner>(m_cornerComboBox->currentData().toInt()));
    m_speedDial->updateGeometry();
    m_speedDial->resize(m_speedDial->parentWidget()->size());
}
