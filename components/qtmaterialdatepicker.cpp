#include "qtmaterialdatepicker.h"
#include "qtmaterialdatepicker_p.h"

#include <QMouseEvent>
#include <QPainter>

QtMaterialDatePickerPrivate::QtMaterialDatePickerPrivate(QtMaterialDatePicker *q)
    : q_ptr(q), useThemeColors(true), selectedDate(QDate::currentDate()),
      displayMonth(QDate::currentDate().addDays(1 - QDate::currentDate().day())),
      minDate(QDate(1900, 1, 1)), maxDate(QDate(2100, 12, 31))
{
}

QtMaterialDatePickerPrivate::~QtMaterialDatePickerPrivate()
{
}

void QtMaterialDatePickerPrivate::init()
{
    rebuildCells();
}

void QtMaterialDatePickerPrivate::rebuildCells()
{
    visibleDates.clear();
    const QDate first(displayMonth.year(), displayMonth.month(), 1);
    const int startOffset = (first.dayOfWeek() + 6) % 7;
    QDate start = first.addDays(-startOffset);
    for (int i = 0; i < 42; ++i) {
        visibleDates.push_back(start.addDays(i));
    }
}

QRect QtMaterialDatePickerPrivate::cellRect(int index, const QRect &gridRect) const
{
    const int col = index % 7;
    const int row = index / 7;
    const int w = gridRect.width() / 7;
    const int h = gridRect.height() / 6;
    return QRect(gridRect.x() + col * w, gridRect.y() + row * h, w, h);
}

int QtMaterialDatePickerPrivate::cellAt(const QPoint &pos, const QRect &gridRect) const
{
    for (int i = 0; i < visibleDates.size(); ++i) {
        if (cellRect(i, gridRect).contains(pos)) {
            return i;
        }
    }
    return -1;
}

QtMaterialDatePicker::QtMaterialDatePicker(QWidget *parent)
    : QWidget(parent), d_ptr(new QtMaterialDatePickerPrivate(this))
{
    Q_D(QtMaterialDatePicker);
    d->init();
    setMinimumSize(320, 360);
}

QtMaterialDatePicker::~QtMaterialDatePicker()
{
}

void QtMaterialDatePicker::setUseThemeColors(bool value)
{
    Q_D(QtMaterialDatePicker);
    d->useThemeColors = value;
    update();
}

bool QtMaterialDatePicker::useThemeColors() const
{
    Q_D(const QtMaterialDatePicker);
    return d->useThemeColors;
}

void QtMaterialDatePicker::setDate(const QDate &date)
{
    Q_D(QtMaterialDatePicker);
    if (!date.isValid() || date == d->selectedDate) {
        return;
    }
    d->selectedDate = date;
    d->displayMonth = QDate(date.year(), date.month(), 1);
    d->rebuildCells();
    emit dateChanged(d->selectedDate);
    update();
}

QDate QtMaterialDatePicker::date() const
{
    Q_D(const QtMaterialDatePicker);
    return d->selectedDate;
}

void QtMaterialDatePicker::setMinimumDate(const QDate &date)
{
    Q_D(QtMaterialDatePicker);
    d->minDate = date;
    update();
}

QDate QtMaterialDatePicker::minimumDate() const
{
    Q_D(const QtMaterialDatePicker);
    return d->minDate;
}

void QtMaterialDatePicker::setMaximumDate(const QDate &date)
{
    Q_D(QtMaterialDatePicker);
    d->maxDate = date;
    update();
}

QDate QtMaterialDatePicker::maximumDate() const
{
    Q_D(const QtMaterialDatePicker);
    return d->maxDate;
}

void QtMaterialDatePicker::setHeaderColor(const QColor &color)
{
    Q_D(QtMaterialDatePicker);
    d->headerColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialDatePicker::headerColor() const
{
    Q_D(const QtMaterialDatePicker);
    return d->headerColor;
}

void QtMaterialDatePicker::setTextColor(const QColor &color)
{
    Q_D(QtMaterialDatePicker);
    d->textColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialDatePicker::textColor() const
{
    Q_D(const QtMaterialDatePicker);
    return d->textColor;
}

void QtMaterialDatePicker::setSelectedColor(const QColor &color)
{
    Q_D(QtMaterialDatePicker);
    d->selectedColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialDatePicker::selectedColor() const
{
    Q_D(const QtMaterialDatePicker);
    return d->selectedColor;
}

void QtMaterialDatePicker::setDisabledTextColor(const QColor &color)
{
    Q_D(QtMaterialDatePicker);
    d->disabledTextColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialDatePicker::disabledTextColor() const
{
    Q_D(const QtMaterialDatePicker);
    return d->disabledTextColor;
}

void QtMaterialDatePicker::showNextMonth()
{
    Q_D(QtMaterialDatePicker);
    d->displayMonth = d->displayMonth.addMonths(1);
    d->rebuildCells();
    update();
}

void QtMaterialDatePicker::showPreviousMonth()
{
    Q_D(QtMaterialDatePicker);
    d->displayMonth = d->displayMonth.addMonths(-1);
    d->rebuildCells();
    update();
}

void QtMaterialDatePicker::acceptSelection()
{
    emit accepted(date());
}

void QtMaterialDatePicker::cancelSelection()
{
    emit canceled();
}

QSize QtMaterialDatePicker::sizeHint() const
{
    return QSize(360, 400);
}

void QtMaterialDatePicker::paintEvent(QPaintEvent *)
{
    Q_D(QtMaterialDatePicker);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const QColor header = d->useThemeColors ? QColor(63, 81, 181) : d->headerColor;
    const QColor text = d->useThemeColors ? QColor(33, 33, 33) : d->textColor;
    const QColor selected = d->useThemeColors ? QColor(63, 81, 181) : d->selectedColor;
    const QColor disabled = d->useThemeColors ? QColor(160, 160, 160) : d->disabledTextColor;

    painter.fillRect(rect(), Qt::white);
    painter.fillRect(QRect(0, 0, width(), 72), header);
    painter.setPen(Qt::white);
    painter.drawText(QRect(16, 12, width() - 32, 22), Qt::AlignLeft | Qt::AlignVCenter,
                     d->displayMonth.toString("MMMM yyyy"));
    painter.drawText(QRect(16, 36, width() - 32, 24), Qt::AlignLeft | Qt::AlignVCenter,
                     d->selectedDate.toString("ddd, MMM d"));

    const QStringList days = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    const QRect dayRect(16, 88, width() - 32, 20);
    for (int i = 0; i < 7; ++i) {
        QRect r(dayRect.x() + i * (dayRect.width() / 7), dayRect.y(), dayRect.width() / 7, dayRect.height());
        painter.setPen(disabled);
        painter.drawText(r, Qt::AlignCenter, days.at(i));
    }

    const QRect gridRect(16, 116, width() - 32, height() - 164);
    for (int i = 0; i < d->visibleDates.size(); ++i) {
        const QDate day = d->visibleDates.at(i);
        const QRect cell = d->cellRect(i, gridRect);
        const bool currentMonth = day.month() == d->displayMonth.month();
        const bool enabled = day >= d->minDate && day <= d->maxDate;
        const bool selectedDay = day == d->selectedDate;

        if (selectedDay) {
            painter.setBrush(selected);
            painter.setPen(Qt::NoPen);
            painter.drawEllipse(cell.adjusted(8, 6, -8, -6));
        }

        painter.setPen(!enabled || !currentMonth ? disabled : (selectedDay ? Qt::white : text));
        painter.drawText(cell, Qt::AlignCenter, QString::number(day.day()));
    }

    painter.setPen(disabled);
    painter.drawText(QRect(16, height() - 36, 64, 24), Qt::AlignLeft | Qt::AlignVCenter, "Cancel");
    painter.setPen(selected);
    painter.drawText(QRect(width() - 80, height() - 36, 64, 24), Qt::AlignRight | Qt::AlignVCenter, "OK");
}

void QtMaterialDatePicker::mousePressEvent(QMouseEvent *event)
{
    Q_D(QtMaterialDatePicker);
    const QRect gridRect(16, 116, width() - 32, height() - 164);
    const int index = d->cellAt(event->pos(), gridRect);
    if (index >= 0 && index < d->visibleDates.size()) {
        const QDate chosen = d->visibleDates.at(index);
        if (chosen >= d->minDate && chosen <= d->maxDate) {
            setDate(chosen);
        }
        return;
    }

    if (QRect(0, height() - 44, 96, 36).contains(event->pos())) {
        cancelSelection();
    } else if (QRect(width() - 96, height() - 44, 96, 36).contains(event->pos())) {
        acceptSelection();
    } else if (event->pos().y() < 72 && event->pos().x() > width() / 2) {
        showNextMonth();
    } else if (event->pos().y() < 72) {
        showPreviousMonth();
    }
}
