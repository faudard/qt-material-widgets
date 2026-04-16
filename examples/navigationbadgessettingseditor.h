#ifndef NAVIGATIONBADGESSETTINGSEDITOR_H
#define NAVIGATIONBADGESSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialNavigationBadgeIntegration;
class QtMaterialNavigationBar;
class QtMaterialNavigationRail;

class NavigationBadgesSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit NavigationBadgesSettingsEditor(QWidget *parent = 0);
    ~NavigationBadgesSettingsEditor();

private slots:
    void cycleBadges();

private:
    QtMaterialNavigationBar *m_bar;
    QtMaterialNavigationRail *m_rail;
    QtMaterialNavigationBadgeIntegration *m_barBadges;
    QtMaterialNavigationBadgeIntegration *m_railBadges;
};

#endif // NAVIGATIONBADGESSETTINGSEDITOR_H
