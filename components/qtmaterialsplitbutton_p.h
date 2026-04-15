#ifndef QTMATERIALSPLITBUTTON_P_H
#define QTMATERIALSPLITBUTTON_P_H

#include <QColor>
#include <QString>

class QToolButton;
class QMenu;
class QtMaterialSplitButton;

class QtMaterialSplitButtonPrivate
{
    Q_DISABLE_COPY(QtMaterialSplitButtonPrivate)
    Q_DECLARE_PUBLIC(QtMaterialSplitButton)

public:
    explicit QtMaterialSplitButtonPrivate(QtMaterialSplitButton *q);
    ~QtMaterialSplitButtonPrivate();

    void init();
    void setupGeometry();

    QtMaterialSplitButton * const q_ptr;
    QToolButton *mainButton;
    QToolButton *menuButton;
    QMenu *attachedMenu;
    bool useThemeColors;
    bool dense;
    QString text;
    QColor backgroundColor;
    QColor textColor;
    QColor menuButtonColor;
    QColor dividerColor;
};

#endif // QTMATERIALSPLITBUTTON_P_H
