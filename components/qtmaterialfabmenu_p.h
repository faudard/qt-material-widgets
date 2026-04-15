#ifndef QTMATERIALFABMENU_P_H
#define QTMATERIALFABMENU_P_H

#include <QColor>
#include <QList>
#include <QString>
#include <QPointer>

class QtMaterialFabMenu;
class QtMaterialFloatingActionButton;
class QLabel;
class QWidget;

class QtMaterialFabMenuPrivate
{
    Q_DISABLE_COPY(QtMaterialFabMenuPrivate)
    Q_DECLARE_PUBLIC(QtMaterialFabMenu)

public:
    explicit QtMaterialFabMenuPrivate(QtMaterialFabMenu *q);
    ~QtMaterialFabMenuPrivate();

    void init();
    void updateGeometry();
    void updatePalette();
    QRect anchorGeometryForIndex(int index) const;
    QPoint anchorPoint() const;

    QtMaterialFabMenu *const q_ptr;
    bool useThemeColors;
    bool expanded;
    bool labelsVisible;
    int actionSpacing;
    Qt::Corner corner;
    QColor backgroundColor;
    QColor foregroundColor;
    QColor overlayColor;

    QPointer<QtMaterialFloatingActionButton> mainButton;
    QList<QtMaterialFloatingActionButton *> actionButtons;
    QList<QWidget *> labelWidgets;
    QList<QString> labelTexts;
};

#endif // QTMATERIALFABMENU_P_H