#include "qtmaterialtimepicker.h"
#include "qtmaterialtimepicker_p.h"

#include <QMouseEvent>
#include <QPainter>

QtMaterialTimePickerPrivate::QtMaterialTimePickerPrivate(QtMaterialTimePicker *q)
    : q_ptr(q), useThemeColors(true), hourMode(true), mode24h(false), selectedTime(QTime::currentTime())
{
}

QtMaterialTimePickerPrivate::~QtMaterialTimePickerPrivate()
{
}

void QtMaterialTimePickerPrivate::init()
{
}

QtMaterialTimePicker::QtMaterialTimePicker(QWidget *parent)
    : QWidget(parent), d_ptr(new QtMaterialTimePickerPrivate(this))
{
    Q_D(QtMaterialTimePicker);
    d->init();
    setMinimumSize(320, 360);
}

QtMaterialTimePicker::~QtMaterialTimePicker()
{
}

void QtMaterialTimePicker::setUseThemeColors(bool value)
{
    Q_D(QtMaterialTimePicker);
    d->useThemeColors = value;
    update();
}

bool QtMaterialTimePicker::useThemeColors() const
{
    Q_D(const QtMaterialTimePicker);
    return d->useThemeColors;
}

void QtMaterialTimePicker::setTime(const QTime &time)
{
    Q_D(QtMaterialTimePicker);
    if (!time.isValid() || time == d->selectedTime) {
        return;
    }
    d->selectedTime = time;
    emit timeChanged(d->selectedTime);
    update();
}

QTime QtMaterialTimePicker::time() const
{
    Q_D(const QtMaterialTimePicker);
    return d->selectedTime;
}

void QtMaterialTimePicker::set24HourMode(bool value)
{
    Q_D(QtMaterialTimePicker);
    d->mode24h = value;
    update();
}

bool QtMaterialTimePicker::is24HourMode() const
{
    Q_D(const QtMaterialTimePicker);
    return d->mode24h;
}

void QtMaterialTimePicker::setAccentColor(const QColor &color)
{
    Q_D(QtMaterialTimePicker);
    d->accentColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialTimePicker::accentColor() const
{
    Q_D(const QtMaterialTimePicker);
    return d->accentColor;
}

void QtMaterialTimePicker::setTextColor(const QColor &color)
{
    Q_D(QtMaterialTimePicker);
    d->textColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialTimePicker::textColor() const
{
    Q_D(const QtMaterialTimePicker);
    return d->textColor;
}

void QtMaterialTimePicker::setHourMode()
{
    Q_D(QtMaterialTimePicker);
    d->hourMode = true;
    update();
}

void QtMaterialTimePicker::setMinuteMode()
{
    Q_D(QtMaterialTimePicker);
    d->hourMode = false;
    update();
}

void QtMaterialTimePicker::acceptSelection()
{
    emit accepted(time());
}

void QtMaterialTimePicker::cancelSelection()
{
    emit canceled();
}

QSize QtMaterialTimePicker::sizeHint() const
{
    return QSize(360, 400);
}

void QtMaterialTimePicker::paintEvent(QPaintEvent *)
{
    Q_D(QtMaterialTimePicker);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const QColor accent = d->useThemeColors ? QColor(63, 81, 181) : d->accentColor;
    const QColor text = d->useThemeColors ? QColor(33, 33, 33) : d->textColor;

    painter.fillRect(rect(), Qt::white);
    painter.fillRect(QRect(0, 0, width(), 96), accent);

    painter.setPen(Qt::white);
    const QString hours = d->mode24h ? QString("%1").arg(d->selectedTime.hour(), 2, 10, QLatin1Char('0'))
                                     : QString::number((d->selectedTime.hour() % 12) == 0 ? 12 : (d->selectedTime.hour() % 12));
    const QString minutes = QString("%1").arg(d->selectedTime.minute(), 2, 10, QLatin1Char('0'));
    painter.drawText(QRect(24, 24, width() - 48, 48), Qt::AlignCenter, hours + ":" + minutes);

    const QPoint center(width() / 2, height() / 2 + 12);
    const int radius = 110;
    painter.setBrush(QColor(245, 245, 245));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(center, radius, radius);

    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(accent, 2));
    painter.drawEllipse(center, radius, radius);

    for (int i = 0; i < 12; ++i) {
        const double angle = (-60 + i * 30) * 3.14159265358979323846 / 180.0;
        const QPoint pt(center.x() + int(cos(angle) * (radius - 24)),
                        center.y() + int(sin(angle) * (radius - 24)));
        painter.setPen(text);
        const int value = d->hourMode ? ((i == 0) ? 12 : i) : (i * 5);
        painter.drawText(QRect(pt.x() - 16, pt.y() - 12, 32, 24), Qt::AlignCenter,
                         d->hourMode ? QString::number(value) : QString("%1").arg(value, 2, 10, QLatin1Char('0')));
    }

    painter.setPen(QPen(accent, 3));
    const int currentValue = d->hourMode ? ((d->selectedTime.hour() % 12) == 0 ? 12 : d->selectedTime.hour() % 12)
                                         : (d->selectedTime.minute() / 5) * 5;
    const int index = d->hourMode ? (currentValue % 12) : (currentValue / 5);
    const double selectedAngle = (-60 + index * 30) * 3.14159265358979323846 / 180.0;
    const QPoint hand(center.x() + int(cos(selectedAngle) * (radius - 42)),
                      center.y() + int(sin(selectedAngle) * (radius - 42)));
    painter.drawLine(center, hand);
    painter.setBrush(accent);
    painter.drawEllipse(hand, 8, 8);

    painter.setPen(QColor(150, 150, 150));
    painter.drawText(QRect(16, height() - 36, 64, 24), Qt::AlignLeft | Qt::AlignVCenter, "Cancel");
    painter.setPen(accent);
    painter.drawText(QRect(width() - 80, height() - 36, 64, 24), Qt::AlignRight | Qt::AlignVCenter, "OK");
}

void QtMaterialTimePicker::mousePressEvent(QMouseEvent *event)
{
    Q_D(QtMaterialTimePicker);
    const QPoint center(width() / 2, height() / 2 + 12);
    const QPoint delta = event->pos() - center;
    const double angle = atan2(delta.y(), delta.x()) * 180.0 / 3.14159265358979323846;
    int normalized = int(angle + 450.0) % 360;
    int bucket = (normalized + 15) / 30;
    bucket %= 12;

    if (QRect(0, height() - 44, 96, 36).contains(event->pos())) {
        cancelSelection();
        return;
    }
    if (QRect(width() - 96, height() - 44, 96, 36).contains(event->pos())) {
        acceptSelection();
        return;
    }

    if (event->pos().y() < 96) {
        d->hourMode = event->pos().x() < width() / 2;
        update();
        return;
    }

    QTime t = d->selectedTime;
    if (d->hourMode) {
        int hour = bucket == 0 ? 12 : bucket;
        if (d->mode24h) {
            hour %= 24;
        } else {
            const bool pm = t.hour() >= 12;
            hour %= 12;
            if (pm) {
                hour += 12;
            }
        }
        t.setHMS(hour, t.minute(), 0);
        d->hourMode = false;
    } else {
        t.setHMS(t.hour(), (bucket * 5) % 60, 0);
    }
    setTime(t);
}
