#ifndef QTMATERIALBOTTOMSHEET_P_H
#define QTMATERIALBOTTOMSHEET_P_H

#include <QColor>
#include <QPointer>
#include <QRect>

class QWidget;
class QLayout;
class QPropertyAnimation;
class QStateMachine;
class QState;
class QtMaterialBottomSheet;

class QtMaterialBottomSheetPrivate
{
    Q_DISABLE_COPY(QtMaterialBottomSheetPrivate)
    Q_DECLARE_PUBLIC(QtMaterialBottomSheet)

public:
    explicit QtMaterialBottomSheetPrivate(QtMaterialBottomSheet *q);
    ~QtMaterialBottomSheetPrivate();

    void init();
    QRect sheetRect() const;
    void updateSheetGeometry();

    QtMaterialBottomSheet *const q_ptr;
    QWidget *sheetWidget;
    QLayout *sheetLayout;
    QStateMachine *stateMachine;
    QState *hiddenState;
    QState *visibleState;
    QPropertyAnimation *offsetAnimation;
    QColor backgroundColor;
    QColor overlayColor;
    bool useThemeColors;
    bool modal;
    bool dismissOnOverlayClick;
    int sheetHeight;
    qreal offset;
};

#endif // QTMATERIALBOTTOMSHEET_P_H
