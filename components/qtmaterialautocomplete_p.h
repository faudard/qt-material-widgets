#ifndef QTMATERIALAUTOCOMPLETE_P_H
#define QTMATERIALAUTOCOMPLETE_P_H

#include "qtmaterialtextfield_p.h"

#include <QStringList>

class QWidget;
class QVBoxLayout;
class QtMaterialAutoCompleteStateMachine;
class QtMaterialFlatButton;
class QtMaterialAutoComplete;

class QtMaterialAutoCompletePrivate : public QtMaterialTextFieldPrivate
{
    Q_DISABLE_COPY(QtMaterialAutoCompletePrivate)
    Q_DECLARE_PUBLIC(QtMaterialAutoComplete)

public:
    explicit QtMaterialAutoCompletePrivate(QtMaterialAutoComplete *q);
    virtual ~QtMaterialAutoCompletePrivate();

    void init();
    void syncMenuGeometry();
    void updateMenuButtons(const QStringList &results);
    void updateMenuButtonStyles();
    void setHighlightedIndex(int value);
    void activateIndex(int value);

    QWidget *menu;
    QWidget *frame;
    QtMaterialAutoCompleteStateMachine *stateMachine;
    QVBoxLayout *menuLayout;
    QStringList dataSource;
    QStringList visibleResults;
    QList<QtMaterialFlatButton *> buttons;
    int maxWidth;
    int maxVisibleItems;
    int highlightedIndex;
    Qt::CaseSensitivity caseSensitivity;
    int filterMode;
    QColor menuBackgroundColor;
    QColor menuTextColor;
    QColor menuSelectedColor;
};

#endif // QTMATERIALAUTOCOMPLETE_P_H
