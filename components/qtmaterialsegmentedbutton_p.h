#ifndef QTMATERIALSEGMENTEDBUTTON_P_H
#define QTMATERIALSEGMENTEDBUTTON_P_H

#include <QColor>
#include <QIcon>
#include <QList>
#include <QString>

class QtMaterialSegmentedButton;
class QtMaterialFlatButton;
class QButtonGroup;
class QHBoxLayout;

class QtMaterialSegmentedButtonPrivate
{
    Q_DISABLE_COPY(QtMaterialSegmentedButtonPrivate)
    Q_DECLARE_PUBLIC(QtMaterialSegmentedButton)

public:
    explicit QtMaterialSegmentedButtonPrivate(QtMaterialSegmentedButton *q);
    ~QtMaterialSegmentedButtonPrivate();

    void init();
    void rebuild();
    void applyStyle(QtMaterialFlatButton *button, int index);
    void updateButtons();
    QColor resolvedBackgroundColor() const;
    QColor resolvedTextColor() const;
    QColor resolvedSelectedColor() const;
    QColor resolvedSelectedTextColor() const;
    QColor resolvedOutlineColor() const;

    struct Segment {
        QString text;
        QIcon icon;
        QtMaterialFlatButton *button;
        Segment() : button(0) {}
    };

    QtMaterialSegmentedButton *const q_ptr;
    QButtonGroup *group;
    QHBoxLayout *layout;
    QList<Segment> segments;
    bool useThemeColors;
    bool exclusive;
    bool showIcons;
    int currentIndex;
    QColor backgroundColor;
    QColor textColor;
    QColor selectedColor;
    QColor selectedTextColor;
    QColor outlineColor;
};

#endif // QTMATERIALSEGMENTEDBUTTON_P_H
