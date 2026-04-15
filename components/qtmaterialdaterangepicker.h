#ifndef QTMATERIALDATERANGEPICKER_H
#define QTMATERIALDATERANGEPICKER_H

#include <QColor>
#include <QDate>
#include <QScopedPointer>
#include <QWidget>

class QtMaterialDateRangePickerPrivate;

class QtMaterialDateRangePicker : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QDate startDate WRITE setStartDate READ startDate)
    Q_PROPERTY(QDate endDate WRITE setEndDate READ endDate)
    Q_PROPERTY(QDate minimumDate WRITE setMinimumDate READ minimumDate)
    Q_PROPERTY(QDate maximumDate WRITE setMaximumDate READ maximumDate)
    Q_PROPERTY(QColor headerColor WRITE setHeaderColor READ headerColor)
    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
    Q_PROPERTY(QColor selectedColor WRITE setSelectedColor READ selectedColor)
    Q_PROPERTY(QColor rangeColor WRITE setRangeColor READ rangeColor)
    Q_PROPERTY(QColor disabledTextColor WRITE setDisabledTextColor READ disabledTextColor)
    Q_PROPERTY(bool showDualMonth WRITE setShowDualMonth READ showDualMonth)

public:
    explicit QtMaterialDateRangePicker(QWidget *parent = 0);
    ~QtMaterialDateRangePicker();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setDateRange(const QDate &start, const QDate &end);
    void clearSelection();

    void setStartDate(const QDate &date);
    QDate startDate() const;

    void setEndDate(const QDate &date);
    QDate endDate() const;

    bool hasCompleteRange() const;

    void setMinimumDate(const QDate &date);
    QDate minimumDate() const;

    void setMaximumDate(const QDate &date);
    QDate maximumDate() const;

    void setDisplayedMonth(const QDate &month);
    QDate displayedMonth() const;

    void showNextMonth();
    void showPreviousMonth();

    void setShowDualMonth(bool value);
    bool showDualMonth() const;

    void setHeaderColor(const QColor &color);
    QColor headerColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setSelectedColor(const QColor &color);
    QColor selectedColor() const;

    void setRangeColor(const QColor &color);
    QColor rangeColor() const;

    void setDisabledTextColor(const QColor &color);
    QColor disabledTextColor() const;

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

signals:
    void startDateChanged(const QDate &date);
    void endDateChanged(const QDate &date);
    void dateRangeChanged(const QDate &start, const QDate &end);
    void accepted(const QDate &start, const QDate &end);
    void canceled();

public slots:
    void accept();
    void cancel();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialDateRangePickerPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialDateRangePicker)
    Q_DECLARE_PRIVATE(QtMaterialDateRangePicker)
};

#endif // QTMATERIALDATERANGEPICKER_H
