#include "navigationbadgessettingseditor.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>

#include "qtmaterialnavigationbadgeintegration.h"
#include "qtmaterialnavigationbar.h"
#include "qtmaterialnavigationrail.h"

NavigationBadgesSettingsEditor::NavigationBadgesSettingsEditor(QWidget *parent)
    : QWidget(parent),
      m_bar(new QtMaterialNavigationBar(this)),
      m_rail(new QtMaterialNavigationRail(this)),
      m_barBadges(new QtMaterialNavigationBadgeIntegration(this)),
      m_railBadges(new QtMaterialNavigationBadgeIntegration(this))
{
    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *content = new QHBoxLayout;
    QPushButton *button = new QPushButton(tr("Cycle badges"));

    m_bar->addItem(tr("Home"), QIcon());
    m_bar->addItem(tr("Inbox"), QIcon());
    m_bar->addItem(tr("Updates"), QIcon());

    m_rail->addItem(QIcon(), tr("Home"));
    m_rail->addItem(QIcon(), tr("Inbox"));
    m_rail->addItem(QIcon(), tr("Updates"));

    m_barBadges->attachTo(m_bar);
    m_railBadges->attachTo(m_rail);

    content->addWidget(m_rail);
    content->addWidget(m_bar, 1);

    layout->addLayout(content);
    layout->addWidget(button);
    setLayout(layout);

    connect(button, SIGNAL(clicked()), this, SLOT(cycleBadges()));
}

NavigationBadgesSettingsEditor::~NavigationBadgesSettingsEditor()
{
}

void NavigationBadgesSettingsEditor::cycleBadges()
{
    static int value = 1;
    m_barBadges->setBadgeCount(1, value);
    m_barBadges->setBadgeText(2, value > 9 ? QStringLiteral("!") : QString());
    m_railBadges->setBadgeCount(1, value + 2);
    m_railBadges->setBadgeText(2, value % 2 ? QStringLiteral("NEW") : QString());
    ++value;
}
