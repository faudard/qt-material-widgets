#include "toggleiconbuttonsettingseditor.h"
#include "qtmaterialtoggleiconbutton.h"

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QStyle>

ToggleIconButtonSettingsEditor::ToggleIconButtonSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    m_button = new QtMaterialToggleIconButton(style()->standardIcon(QStyle::SP_DialogApplyButton));
    m_button->setSelectedIcon(style()->standardIcon(QStyle::SP_DialogYesButton));
    m_button->setIconSize(QSize(24, 24));
    m_button->setFixedSize(48, 48);

    m_useThemeColors = new QCheckBox(tr("Use theme colors"));
    m_useThemeColors->setChecked(true);

    m_checked = new QCheckBox(tr("Checked"));
    m_enabled = new QCheckBox(tr("Enabled"));
    m_enabled->setChecked(true);

    connect(m_useThemeColors, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_checked, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_enabled, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));

    QVBoxLayout *controls = new QVBoxLayout;
    controls->addWidget(new QLabel(tr("Toggle Icon Button")));
    controls->addWidget(m_useThemeColors);
    controls->addWidget(m_checked);
    controls->addWidget(m_enabled);
    controls->addStretch(1);

    QHBoxLayout *canvas = new QHBoxLayout;
    canvas->addStretch(1);
    canvas->addWidget(m_button);
    canvas->addStretch(1);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addLayout(controls);
    layout->addLayout(canvas, 1);

    updateWidget();
}

ToggleIconButtonSettingsEditor::~ToggleIconButtonSettingsEditor()
{
}

void ToggleIconButtonSettingsEditor::updateWidget()
{
    m_button->setUseThemeColors(m_useThemeColors->isChecked());
    m_button->setChecked(m_checked->isChecked());
    m_button->setEnabled(m_enabled->isChecked());

    if (!m_useThemeColors->isChecked()) {
        m_button->setColor(QColor("#616161"));
        m_button->setSelectedColor(QColor("#1e88e5"));
        m_button->setDisabledColor(QColor("#bdbdbd"));
        m_button->setSelectedDisabledColor(QColor("#90caf9"));
    }
}
