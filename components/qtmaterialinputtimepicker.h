#ifndef QTMATERIALINPUTTIMEPICKER_H
#define QTMATERIALINPUTTIMEPICKER_H

#include <QWidget>
#include <QTime>
#include <QScopedPointer>

class QtMaterialInputTimePickerPrivate;

class QtMaterialInputTimePicker : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QTime time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(bool twentyFourHour READ isTwentyFourHour WRITE setTwentyFourHour)

public:
    explicit QtMaterialInputTimePicker(QWidget *parent = 0);
    ~QtMaterialInputTimePicker();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setTime(const QTime &time);
    QTime time() const;

    void setTwentyFourHour(bool value);
    bool isTwentyFourHour() const;

signals:
    void timeChanged(const QTime &time);
    void accepted(const QTime &time);
    void canceled();

private:
    Q_DISABLE_COPY(QtMaterialInputTimePicker)
    Q_DECLARE_PRIVATE(QtMaterialInputTimePicker)
    const QScopedPointer<QtMaterialInputTimePickerPrivate> d_ptr;
};

#endif // QTMATERIALINPUTTIMEPICKER_H
