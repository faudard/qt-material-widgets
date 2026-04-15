#ifndef QTMATERIALSPEEDDIAL_P_H
#define QTMATERIALSPEEDDIAL_P_H

#include <QColor>
#include <QVector>
#include <QPointer>
#include <QVariant>
#include <QIcon>
#include <QString>

class QtMaterialFloatingActionButton;
class QWidget;

class QtMaterialSpeedDialPrivate
{
public:
    QtMaterialSpeedDialPrivate();

    bool useThemeColors;
    QColor backgroundColor;
    QColor foregroundColor;
    QColor overlayColor;
    bool expanded;
    bool labelsVisible;
    int actionSpacing;
    Qt::Corner anchorCorner;

    struct Item {
        QIcon icon;
        QString text;
        QVariant data;
        QPointer<QtMaterialFloatingActionButton> button;
        QPointer<QWidget> label;
    };

    QVector<Item> items;
    QPointer<QtMaterialFloatingActionButton> mainButton;
};

#endif // QTMATERIALSPEEDDIAL_P_H
