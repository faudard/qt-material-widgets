#ifndef QTMATERIALSEARCHBAR_P_H
#define QTMATERIALSEARCHBAR_P_H

#include <QColor>
#include <QList>
#include <QStringList>

class QAction;
class QHBoxLayout;
class QFrame;
class QToolButton;
class QtMaterialSearchField;
class QtMaterialSearchBar;

class QtMaterialSearchBarPrivate
{
    Q_DISABLE_COPY(QtMaterialSearchBarPrivate)
    Q_DECLARE_PUBLIC(QtMaterialSearchBar)

public:
    explicit QtMaterialSearchBarPrivate(QtMaterialSearchBar *q);
    ~QtMaterialSearchBarPrivate();

    void init();
    void updateColors();
    void updateVisibility();

    QtMaterialSearchBar *const q_ptr;
    QtMaterialSearchField *field;
    QFrame *surface;
    QToolButton *leadingButton;
    QToolButton *clearButton;
    QHBoxLayout *layout;
    QHBoxLayout *inputLayout;

    QList<QAction *> trailingActions;
    QStringList suggestions;

    QColor backgroundColor;
    QColor textColor;
    QColor placeholderColor;
    QColor iconColor;
    QColor dividerColor;

    QString placeholderText;
    bool useThemeColors;
    bool active;
    bool collapsible;
    bool showLeadingNavigationIcon;
    bool showTrailingActions;
    int searchDelay;
};

#endif // QTMATERIALSEARCHBAR_P_H
