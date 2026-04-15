#ifndef QTMATERIALMENU_P_H
#define QTMATERIALMENU_P_H

#include <QColor>
#include <QList>

class QAction;
class QVBoxLayout;
class QtMaterialMenu;
class QtMaterialMenuItem;
class QtMaterialPaper;

class QtMaterialMenuPrivate
{
    Q_DISABLE_COPY(QtMaterialMenuPrivate)
    Q_DECLARE_PUBLIC(QtMaterialMenu)

public:
    explicit QtMaterialMenuPrivate(QtMaterialMenu *q);
    ~QtMaterialMenuPrivate();

    void init();
    void rebuildMenu();
    void updateMenu();
    void handleTriggered(QAction *action);

    QtMaterialMenu *const q_ptr;
    QtMaterialPaper *paper;
    QVBoxLayout *menuLayout;
    QList<QAction *> actions;
    QList<QtMaterialMenuItem *> items;
    QColor backgroundColor;
    QColor textColor;
    QColor selectedColor;
    QColor disabledColor;
    int elevation;
    bool useThemeColors;
    bool dense;
};

#endif // QTMATERIALMENU_P_H
