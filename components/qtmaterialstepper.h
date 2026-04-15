#ifndef QTMATERIALSTEPPER_H
#define QTMATERIALSTEPPER_H

#include <QColor>
#include <QScopedPointer>
#include <QStringList>
#include <QWidget>

class QtMaterialStepperPrivate;

class QtMaterialStepper : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation)
    Q_PROPERTY(int currentStep READ currentStep WRITE setCurrentStep NOTIFY currentStepChanged)
    Q_PROPERTY(bool clickable READ isClickable WRITE setClickable)
    Q_PROPERTY(bool showLabels READ showLabels WRITE setShowLabels)
    Q_PROPERTY(QColor activeColor READ activeColor WRITE setActiveColor)
    Q_PROPERTY(QColor completedColor READ completedColor WRITE setCompletedColor)
    Q_PROPERTY(QColor inactiveColor READ inactiveColor WRITE setInactiveColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)

public:
    explicit QtMaterialStepper(QWidget *parent = 0);
    ~QtMaterialStepper();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setOrientation(Qt::Orientation orientation);
    Qt::Orientation orientation() const;

    void setCurrentStep(int step);
    int currentStep() const;

    void setClickable(bool value);
    bool isClickable() const;

    void setShowLabels(bool value);
    bool showLabels() const;

    void setStepLabels(const QStringList &labels);
    QStringList stepLabels() const;
    void addStep(const QString &label);
    int stepCount() const;

    void setActiveColor(const QColor &color);
    QColor activeColor() const;

    void setCompletedColor(const QColor &color);
    QColor completedColor() const;

    void setInactiveColor(const QColor &color);
    QColor inactiveColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

signals:
    void currentStepChanged(int step);
    void stepClicked(int step);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialStepperPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialStepper)
    Q_DECLARE_PRIVATE(QtMaterialStepper)
};

#endif // QTMATERIALSTEPPER_H
