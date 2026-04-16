#include "responsivenavigationsettingseditor.h"
#include "qtmaterialresponsivenavigation.h"

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>

ResponsiveNavigationSettingsEditor::ResponsiveNavigationSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(24);

    m_navigation = new QtMaterialResponsiveNavigation;
    m_navigation->addItem(QIcon(), QStringLiteral("Home"));
    m_navigation->addItem(QIcon(), QStringLiteral("Explore"));
    m_navigation->addItem(QIcon(), QStringLiteral("Saved"));

    m_compactBreakpoint = new QSlider(Qt::Horizontal);
    m_compactBreakpoint->setRange(320, 900);
    m_compactBreakpoint->setValue(600);

    m_mediumBreakpoint = new QSlider(Qt::Horizontal);
    m_mediumBreakpoint->setRange(700, 1440);
    m_mediumBreakpoint->setValue(1024);

    m_forcedMode = new QComboBox;
    m_forcedMode->addItem(QStringLiteral("Auto"), -1);
    m_forcedMode->addItem(QStringLiteral("Bottom bar"), QtMaterialResponsiveNavigation::BottomBarMode);
    m_forcedMode->addItem(QStringLiteral("Rail"), QtMaterialResponsiveNavigation::RailMode);
    m_forcedMode->addItem(QStringLiteral("Drawer"), QtMaterialResponsiveNavigation::DrawerMode);

    connect(m_compactBreakpoint, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_mediumBreakpoint, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_forcedMode, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));

    layout->addWidget(new QLabel(QStringLiteral("Responsive navigation")));
    layout->addWidget(m_navigation);
    layout->addWidget(new QLabel(QStringLiteral("Compact breakpoint")));
    layout->addWidget(m_compactBreakpoint);
    layout->addWidget(new QLabel(QStringLiteral("Medium breakpoint")));
    layout->addWidget(m_mediumBreakpoint);
    layout->addWidget(new QLabel(QStringLiteral("Mode")));
    layout->addWidget(m_forcedMode);
    layout->addStretch();

    updateWidget();
}

void ResponsiveNavigationSettingsEditor::updateWidget()
{
    m_navigation->setCompactBreakpoint(m_compactBreakpoint->value());
    m_navigation->setMediumBreakpoint(m_mediumBreakpoint->value());

    const int modeData = m_forcedMode->itemData(m_forcedMode->currentIndex()).toInt();
    if (modeData < 0) {
        m_navigation->updateForAvailableWidth(m_navigation->width());
    } else {
        m_navigation->setNavigationMode(static_cast<QtMaterialResponsiveNavigation::NavigationMode>(modeData));
    }
}
