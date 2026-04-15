#ifndef QTMATERIALSEARCHFIELD_P_H
#define QTMATERIALSEARCHFIELD_P_H

#include <QColor>
#include <QIcon>
#include <QPointer>

class QAction;
class QTimer;
class QtMaterialSearchField;

class QtMaterialSearchFieldPrivate
{
    Q_DISABLE_COPY(QtMaterialSearchFieldPrivate)
    Q_DECLARE_PUBLIC(QtMaterialSearchField)

public:
    QtMaterialSearchFieldPrivate(QtMaterialSearchField *q);
    ~QtMaterialSearchFieldPrivate();

    void init();
    void updateActions();
    void updateMargins();

    QtMaterialSearchField *const q_ptr;

    bool showSearchIcon;
    bool showClearButton;
    int searchDelay;
    QColor iconColor;
    QIcon searchIcon;
    QIcon clearIcon;

    QAction *searchAction;
    QAction *clearAction;
    QTimer *searchTimer;
};

#endif // QTMATERIALSEARCHFIELD_P_H
