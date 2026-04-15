#ifndef QTMATERIALSELECTFIELD_P_H
#define QTMATERIALSELECTFIELD_P_H

#include "qtmaterialtextfield_p.h"
#include <QtGlobal>
#include <QColor>
#include <QStringList>
#include <QPointer>

class QListWidget;
class QFrame;
class QtMaterialSelectField;

class QtMaterialSelectFieldPrivate : public QtMaterialTextFieldPrivate
{
    Q_DISABLE_COPY(QtMaterialSelectFieldPrivate)
    Q_DECLARE_PUBLIC(QtMaterialSelectField)

public:
    explicit QtMaterialSelectFieldPrivate(QtMaterialSelectField *q);
    ~QtMaterialSelectFieldPrivate();

    void init();
    void updatePopupGeometry();
    void syncSelection();
    void applyReadOnlyState();

    QStringList itemList;
    QString placeholder;
    int index;
    bool editable;
    bool showIndicator;
    QColor popupBackgroundColor;
    QColor popupTextColor;
    QColor popupSelectedColor;
    QPointer<QFrame> popup;
    QPointer<QListWidget> listWidget;
};

#endif // QTMATERIALSELECTFIELD_P_H