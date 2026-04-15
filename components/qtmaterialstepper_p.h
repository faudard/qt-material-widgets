#ifndef QTMATERIALSTEPPER_P_H
#define QTMATERIALSTEPPER_P_H

#include <QColor>
#include <QObject>
#include <QRect>
#include <QStringList>
#include <QVector>

class QtMaterialStepper;

class QtMaterialStepperPrivate
{
    Q_DISABLE_COPY(QtMaterialStepperPrivate)
    Q_DECLARE_PUBLIC(QtMaterialStepper)

public:
    explicit QtMaterialStepperPrivate(QtMaterialStepper *q);
    ~QtMaterialStepperPrivate();

    void init();
    QColor themeColor(const QString &key) const;
    QVector<QPointF> stepCenters() const;
    QRectF stepRect(int index) const;
    int stepAt(const QPoint &pos) const;

    QtMaterialStepper *const q_ptr;

    bool useThemeColors;
    Qt::Orientation orientation;
    int currentStep;
    bool clickable;
    bool labelsVisible;
    QStringList labels;

    QColor activeColor;
    QColor completedColor;
    QColor inactiveColor;
    QColor textColor;

    int circleDiameter;
    int lineThickness;
    int sideMargin;
    int labelSpacing;
    int labelHeight;
};

#endif // QTMATERIALSTEPPER_P_H
