#include "navigationsettingseditor.h"

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

#include "../components/qtmaterialnavigationbar.h"

NavigationSettingsEditor::NavigationSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(24, 24, 24, 24);
    mainLayout->setSpacing(24);

    QLabel *title = new QLabel(tr("Navigation Bar"));
    QFont f = title->font();
    f.setPointSize(14);
    f.setBold(true);
    title->setFont(f);

    m_navigationBar = new QtMaterialNavigationBar;
    m_navigationBar->addItem(tr("Home"));
    m_navigationBar->addItem(tr("Explore"));
    m_navigationBar->addItem(tr("Library"));
    m_navigationBar->addItem(tr("Profile"));

    m_useThemeColorsCheckBox = new QCheckBox(tr("Use theme colors"));
    m_useThemeColorsCheckBox->setChecked(true);

    m_shiftingCheckBox = new QCheckBox(tr("Shifting"));
    m_labelsVisibleCheckBox = new QCheckBox(tr("Labels visible"));
    m_labelsVisibleCheckBox->setChecked(true);

    m_disableThirdItemCheckBox = new QCheckBox(tr("Disable third item"));

    m_currentIndexLabel = new QLabel;
    updateIndexLabel(0);

    connect(m_useThemeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_shiftingCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_labelsVisibleCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_disableThirdItemCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_navigationBar, SIGNAL(currentChanged(int)), this, SLOT(updateIndexLabel(int)));

    QVBoxLayout *controls = new QVBoxLayout;
    controls->setSpacing(8);
    controls->addWidget(m_useThemeColorsCheckBox);
    controls->addWidget(m_shiftingCheckBox);
    controls->addWidget(m_labelsVisibleCheckBox);
    controls->addWidget(m_disableThirdItemCheckBox);
    controls->addWidget(m_currentIndexLabel);
    controls->addStretch(1);

    mainLayout->addWidget(title);
    mainLayout->addWidget(m_navigationBar);
    mainLayout->addLayout(controls);
    mainLayout->addStretch(1);

    setLayout(mainLayout);
    updateWidget();
}

NavigationSettingsEditor::~NavigationSettingsEditor()
{
}

void NavigationSettingsEditor::updateWidget()
{
    m_navigationBar->setUseThemeColors(m_useThemeColorsCheckBox->isChecked());
    m_navigationBar->setShifting(m_shiftingCheckBox->isChecked());
    m_navigationBar->setLabelsVisible(m_labelsVisibleCheckBox->isChecked());
    m_navigationBar->setItemEnabled(2, !m_disableThirdItemCheckBox->isChecked());

    if (!m_useThemeColorsCheckBox->isChecked()) {
        m_navigationBar->setBackgroundColor(QColor("#ffffff"));
        m_navigationBar->setTextColor(QColor("#5f6368"));
        m_navigationBar->setSelectedColor(QColor("#3f51b5"));
        m_navigationBar->setRippleColor(QColor("#3f51b5"));
    }
}

void NavigationSettingsEditor::updateIndexLabel(int index)
{
    m_currentIndexLabel->setText(tr("Current index: %1").arg(index));
}
