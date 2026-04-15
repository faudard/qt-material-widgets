#ifndef QTMATERIALTOOLBAR_P_H
#define QTMATERIALTOOLBAR_P_H

#include "qtmaterialtoolbar.h"
#include "qtmaterialappbar_p.h"
#include <QtGlobal>
#include <QColor>

class QLabel;
class QWidget;
class QHBoxLayout;
class QVBoxLayout;

class QtMaterialToolBarPrivate : public QtMaterialAppBarPrivate
{
    Q_DISABLE_COPY(QtMaterialToolBarPrivate)
    Q_DECLARE_PUBLIC(QtMaterialToolBar)

public:
    explicit QtMaterialToolBarPrivate(QtMaterialToolBar *q);
    ~QtMaterialToolBarPrivate();

    void init();
    void updateLayout();
    void updateLabels();

    QString title;
    QString subtitle;
    bool dense;
    bool centeredTitle;
    QWidget *titleContainer;
    QLabel *titleLabel;
    QLabel *subtitleLabel;
    QHBoxLayout *leadingLayout;
    QHBoxLayout *actionsLayout;
    QVBoxLayout *titleLayout;
};

#endif // QTMATERIALTOOLBAR_P_H