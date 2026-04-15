#ifndef QTMATERIALDATEPICKER_H
#define QTMATERIALDATEPICKER_H

#include <QDate>
#include <QColor>
#include <QWidget>

class QtMaterialDatePickerPrivate;

class QtMaterialDatePicker : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor headerColor WRITE setHeaderColor READ headerColor)
    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
    Q_PROPERTY(QColor selectedColor WRITE setSelectedColor READ selectedColor)
    Q_PROPERTY(QColor disabledTextColor WRITE setDisabledTextColor READ disabledTextColor)

public:
    explicit QtMaterialDatePicker(QWidget *parent = 0);
    ~QtMaterialDatePicker();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setDate(const QDate &date);
    QDate date() const;

    void setMinimumDate(const QDate &date);
    QDate minimumDate() const;

    void setMaximumDate(const QDate &date);
    QDate maximumDate() const;

    void setHeaderColor(const QColor &color);
    QColor headerColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setSelectedColor(const QColor &color);
    QColor selectedColor() const;

    void setDisabledTextColor(const QColor &color);
    QColor disabledTextColor() const;

signals:
    void dateChanged(const QDate &date);
    void accepted(const QDate &date);
    void canceled();

public slots:
    void showNextMonth();
    void showPreviousMonth();
    void acceptSelection();
    void cancelSelection();

protected:
    QSize sizeHint() const Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialDatePickerPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialDatePicker)
    Q_DECLARE_PRIVATE(QtMaterialDatePicker)
};

#endif // QTMATERIALDATEPICKER_H
