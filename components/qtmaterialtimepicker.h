#ifndef QTMATERIALTIMEPICKER_H
#define QTMATERIALTIMEPICKER_H

#include <QColor>
#include <QTime>
#include <QWidget>

class QtMaterialTimePickerPrivate;

class QtMaterialTimePicker : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor accentColor WRITE setAccentColor READ accentColor)
    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)

public:
    explicit QtMaterialTimePicker(QWidget *parent = 0);
    ~QtMaterialTimePicker();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setTime(const QTime &time);
    QTime time() const;

    void set24HourMode(bool value);
    bool is24HourMode() const;

    void setAccentColor(const QColor &color);
    QColor accentColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

signals:
    void timeChanged(const QTime &time);
    void accepted(const QTime &time);
    void canceled();

public slots:
    void setHourMode();
    void setMinuteMode();
    void acceptSelection();
    void cancelSelection();

protected:
    QSize sizeHint() const Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialTimePickerPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialTimePicker)
    Q_DECLARE_PRIVATE(QtMaterialTimePicker)
};

#endif // QTMATERIALTIMEPICKER_H
