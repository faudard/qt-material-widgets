#include "navigationrailsettingseditor.h"
#include "qtmaterialnavigationrail.h"

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QStyle>

NavigationRailSettingsEditor::NavigationRailSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *contentLayout = new QHBoxLayout;
    QVBoxLayout *controlsLayout = new QVBoxLayout;

    m_rail = new QtMaterialNavigationRail;
    m_rail->addItem(style()->standardIcon(QStyle::SP_DesktopIcon), "Home");
    m_rail->addItem(style()->standardIcon(QStyle::SP_DirHomeIcon), "Explore");
    m_rail->addItem(style()->standardIcon(QStyle::SP_FileDialogDetailedView), "Library");
    m_rail->setCurrentIndex(0);

    m_showLabelsCheckBox = new QCheckBox("Show labels");
    m_showLabelsCheckBox->setChecked(true);

    m_compactCheckBox = new QCheckBox("Compact");

    m_themeColorsCheckBox = new QCheckBox("Use theme colors");
    m_themeColorsCheckBox->setChecked(true);

    m_spacingSpinBox = new QSpinBox;
    m_spacingSpinBox->setRange(0, 24);
    m_spacingSpinBox->setValue(8);

    controlsLayout->addWidget(m_showLabelsCheckBox);
    controlsLayout->addWidget(m_compactCheckBox);
    controlsLayout->addWidget(m_themeColorsCheckBox);
    controlsLayout->addWidget(new QLabel("Item spacing"));
    controlsLayout->addWidget(m_spacingSpinBox);
    controlsLayout->addStretch(1);

    contentLayout->addWidget(m_rail, 0, Qt::AlignLeft);
    contentLayout->addSpacing(24);
    contentLayout->addLayout(controlsLayout);
    contentLayout->addStretch(1);

    mainLayout->addLayout(contentLayout);
    mainLayout->addStretch(1);

    connect(m_showLabelsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_compactCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_themeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_spacingSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));

    updateWidget();
}

void NavigationRailSettingsEditor::updateWidget()
{
    m_rail->setShowLabels(m_showLabelsCheckBox->isChecked());
    m_rail->setCompact(m_compactCheckBox->isChecked());
    m_rail->setUseThemeColors(m_themeColorsCheckBox->isChecked());
    m_rail->setItemSpacing(m_spacingSpinBox->value());
}
