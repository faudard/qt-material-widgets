#ifndef BADGESETTINGSEDITOR_H
#define BADGESETTINGSEDITOR_H

#include <QWidget>

class QtMaterialBadge;
class QtMaterialIconButton;
class QtMaterialBadgeDecorator;

class BadgeSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit BadgeSettingsEditor(QWidget *parent = 0);

private slots:
    void updateBadge();

private:
    QtMaterialBadge *m_badge;
    QtMaterialIconButton *m_targetButton;
    QtMaterialBadgeDecorator *m_decorator;
};

#endif // BADGESETTINGSEDITOR_H
