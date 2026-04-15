#ifndef QTMATERIALDOCKEDDATEPICKER_H
#define QTMATERIALDOCKEDDATEPICKER_H

#include <QWidget>
#include <QDate>
#include <QColor>
#include <QScopedPointer>

class QtMaterialDockedDatePickerPrivate;

class QtMaterialDockedDatePicker : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor overlayColor WRITE setOverlayColor READ overlayColor)
    Q_PROPERTY(bool useThemeColors WRITE setUseThemeColors READ useThemeColors)

public:
    explicit QtMaterialDockedDatePicker(QWidget *parent = 0);
    ~QtMaterialDockedDatePicker();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setDate(const QDate &date);
    QDate date() const;

    void setMinimumDate(const QDate &date);
    QDate minimumDate() const;

    void setMaximumDate(const QDate &date);
    QDate maximumDate() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setOverlayColor(const QColor &color);
    QColor overlayColor() const;

public slots:
    void open();
    void close();

signals:
    void dateSelected(const QDate &date);
    void accepted(const QDate &date);
    void canceled();

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    const QScopedPointer<QtMaterialDockedDatePickerPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialDockedDatePicker)
    Q_DECLARE_PRIVATE(QtMaterialDockedDatePicker)
};

#endif // QTMATERIALDOCKEDDATEPICKER_H
