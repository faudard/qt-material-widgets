#ifndef QTMATERIALSEARCHAPPBAR_P_H
#define QTMATERIALSEARCHAPPBAR_P_H

#include <QColor>

class QtMaterialSearchBar;
class QWidget;
class QHBoxLayout;

class QtMaterialSearchAppBarPrivate
{
public:
    QtMaterialSearchAppBarPrivate();

    bool useThemeColors;
    bool active;
    bool showDivider;
    QColor foregroundColor;
    QColor backgroundColor;
    QColor dividerColor;
    QtMaterialSearchBar *searchBar;
    QWidget *leadingContainer;
    QWidget *trailingContainer;
    QHBoxLayout *layout;
};

#endif // QTMATERIALSEARCHAPPBAR_P_H
