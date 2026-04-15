#ifndef QTMATERIALRANGESLIDER_H
#define QTMATERIALRANGESLIDER_H

#include <QColor>
#include <QScopedPointer>
#include <QWidget>

class QtMaterialRangeSliderPrivate;

class QtMaterialRangeSlider : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor thumbColor WRITE setThumbColor READ thumbColor)
    Q_PROPERTY(QColor trackColor WRITE setTrackColor READ trackColor)
    Q_PROPERTY(QColor fillColor WRITE setFillColor READ fillColor)
    Q_PROPERTY(QColor disabledColor WRITE setDisabledColor READ disabledColor)
    Q_PROPERTY(bool stepMode WRITE setStepMode READ stepMode)
    Q_PROPERTY(bool showTickMarks WRITE setShowTickMarks READ showTickMarks)
    Q_PROPERTY(bool showValueLabels WRITE setShowValueLabels READ showValueLabels)

public:
    explicit QtMaterialRangeSlider(QWidget *parent = 0);
    ~QtMaterialRangeSlider();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setThumbColor(const QColor &color);
    QColor thumbColor() const;

    void setTrackColor(const QColor &color);
    QColor trackColor() const;

    void setFillColor(const QColor &color);
    QColor fillColor() const;

    void setDisabledColor(const QColor &color);
    QColor disabledColor() const;

    void setRange(int minimum, int maximum);
    int minimum() const;
    int maximum() const;

    void setLowerValue(int value);
    int lowerValue() const;

    void setUpperValue(int value);
    int upperValue() const;

    void setValues(int lower, int upper);

    void setSingleStep(int step);
    int singleStep() const;

    void setStepMode(bool value);
    bool stepMode() const;

    void setShowTickMarks(bool value);
    bool showTickMarks() const;

    void setShowValueLabels(bool value);
    bool showValueLabels() const;

    void setInvertedAppearance(bool value);
    bool invertedAppearance() const;

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

signals:
    void lowerValueChanged(int value);
    void upperValueChanged(int value);
    void rangeChanged(int lower, int upper);
    void sliderPressed();
    void sliderReleased();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialRangeSliderPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialRangeSlider)
    Q_DECLARE_PRIVATE(QtMaterialRangeSlider)
};

#endif // QTMATERIALRANGESLIDER_H
