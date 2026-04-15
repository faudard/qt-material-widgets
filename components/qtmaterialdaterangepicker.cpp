#include "qtmaterialdaterangepicker.h"
#include "qtmaterialdaterangepicker_p.h"

#include <QDate>
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>

namespace
{
static const int kHeaderHeight = 64;
static const int kMonthHeaderHeight = 28;
static const int kWeekdayHeight = 24;
static const int kCellSize = 36;
static const int kMargin = 16;
static const int kActionHeight = 40;
static const int kMonthGap = 24;
}

QtMaterialDateRangePickerPrivate::QtMaterialDateRangePickerPrivate(QtMaterialDateRangePicker *q)
    : q_ptr(q),
      useThemeColors(true),
      showDualMonth(true),
      minimumDate(QDate(1900, 1, 1)),
      maximumDate(QDate(2100, 12, 31)),
      displayedMonth(QDate::currentDate().addDays(-QDate::currentDate().day() + 1))
{
}

void QtMaterialDateRangePickerPrivate::init()
{
}

QtMaterialDateRangePicker::QtMaterialDateRangePicker(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialDateRangePickerPrivate(this))
{
    Q_D(QtMaterialDateRangePicker);
    d->init();
    setMouseTracking(true);
}

QtMaterialDateRangePicker::~QtMaterialDateRangePicker()
{
}

void QtMaterialDateRangePicker::setUseThemeColors(bool value)
{
    Q_D(QtMaterialDateRangePicker);
    d->useThemeColors = value;
    update();
}

bool QtMaterialDateRangePicker::useThemeColors() const
{
    Q_D(const QtMaterialDateRangePicker);
    return d->useThemeColors;
}

void QtMaterialDateRangePicker::setDateRange(const QDate &start, const QDate &end)
{
    Q_D(QtMaterialDateRangePicker);
    d->startDate = start;
    d->endDate = end;
    if (d->endDate.isValid() && d->startDate.isValid() && d->endDate < d->startDate) {
        qSwap(d->startDate, d->endDate);
    }
    update();
    emit startDateChanged(d->startDate);
    emit endDateChanged(d->endDate);
    emit dateRangeChanged(d->startDate, d->endDate);
}

void QtMaterialDateRangePicker::clearSelection()
{
    Q_D(QtMaterialDateRangePicker);
    d->startDate = QDate();
    d->endDate = QDate();
    update();
}

void QtMaterialDateRangePicker::setStartDate(const QDate &date)
{
    Q_D(QtMaterialDateRangePicker);
    d->startDate = date;
    update();
    emit startDateChanged(d->startDate);
    emit dateRangeChanged(d->startDate, d->endDate);
}

QDate QtMaterialDateRangePicker::startDate() const
{
    Q_D(const QtMaterialDateRangePicker);
    return d->startDate;
}

void QtMaterialDateRangePicker::setEndDate(const QDate &date)
{
    Q_D(QtMaterialDateRangePicker);
    d->endDate = date;
    update();
    emit endDateChanged(d->endDate);
    emit dateRangeChanged(d->startDate, d->endDate);
}

QDate QtMaterialDateRangePicker::endDate() const
{
    Q_D(const QtMaterialDateRangePicker);
    return d->endDate;
}

bool QtMaterialDateRangePicker::hasCompleteRange() const
{
    Q_D(const QtMaterialDateRangePicker);
    return d->startDate.isValid() && d->endDate.isValid();
}

void QtMaterialDateRangePicker::setMinimumDate(const QDate &date)
{
    Q_D(QtMaterialDateRangePicker);
    d->minimumDate = date;
    update();
}

QDate QtMaterialDateRangePicker::minimumDate() const
{
    Q_D(const QtMaterialDateRangePicker);
    return d->minimumDate;
}

void QtMaterialDateRangePicker::setMaximumDate(const QDate &date)
{
    Q_D(QtMaterialDateRangePicker);
    d->maximumDate = date;
    update();
}

QDate QtMaterialDateRangePicker::maximumDate() const
{
    Q_D(const QtMaterialDateRangePicker);
    return d->maximumDate;
}

void QtMaterialDateRangePicker::setDisplayedMonth(const QDate &month)
{
    Q_D(QtMaterialDateRangePicker);
    d->displayedMonth = QDate(month.year(), month.month(), 1);
    update();
}

QDate QtMaterialDateRangePicker::displayedMonth() const
{
    Q_D(const QtMaterialDateRangePicker);
    return d->displayedMonth;
}

void QtMaterialDateRangePicker::showNextMonth()
{
    Q_D(QtMaterialDateRangePicker);
    d->displayedMonth = d->displayedMonth.addMonths(1);
    update();
}

void QtMaterialDateRangePicker::showPreviousMonth()
{
    Q_D(QtMaterialDateRangePicker);
    d->displayedMonth = d->displayedMonth.addMonths(-1);
    update();
}

void QtMaterialDateRangePicker::setShowDualMonth(bool value)
{
    Q_D(QtMaterialDateRangePicker);
    d->showDualMonth = value;
    updateGeometry();
    update();
}

bool QtMaterialDateRangePicker::showDualMonth() const
{
    Q_D(const QtMaterialDateRangePicker);
    return d->showDualMonth;
}

void QtMaterialDateRangePicker::setHeaderColor(const QColor &color)
{
    Q_D(QtMaterialDateRangePicker);
    d->headerColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialDateRangePicker::headerColor() const
{
    Q_D(const QtMaterialDateRangePicker);
    return d->headerColor.isValid() ? d->headerColor : QColor(63, 81, 181);
}

void QtMaterialDateRangePicker::setTextColor(const QColor &color)
{
    Q_D(QtMaterialDateRangePicker);
    d->textColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialDateRangePicker::textColor() const
{
    Q_D(const QtMaterialDateRangePicker);
    return d->textColor.isValid() ? d->textColor : palette().color(QPalette::Text);
}

void QtMaterialDateRangePicker::setSelectedColor(const QColor &color)
{
    Q_D(QtMaterialDateRangePicker);
    d->selectedColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialDateRangePicker::selectedColor() const
{
    Q_D(const QtMaterialDateRangePicker);
    return d->selectedColor.isValid() ? d->selectedColor : QColor(63, 81, 181);
}

void QtMaterialDateRangePicker::setRangeColor(const QColor &color)
{
    Q_D(QtMaterialDateRangePicker);
    d->rangeColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialDateRangePicker::rangeColor() const
{
    Q_D(const QtMaterialDateRangePicker);
    return d->rangeColor.isValid() ? d->rangeColor : QColor(63, 81, 181, 60);
}

void QtMaterialDateRangePicker::setDisabledTextColor(const QColor &color)
{
    Q_D(QtMaterialDateRangePicker);
    d->disabledTextColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialDateRangePicker::disabledTextColor() const
{
    Q_D(const QtMaterialDateRangePicker);
    return d->disabledTextColor.isValid() ? d->disabledTextColor : QColor(0, 0, 0, 90);
}

QSize QtMaterialDateRangePicker::minimumSizeHint() const
{
    return QSize(350, 380);
}

QSize QtMaterialDateRangePicker::sizeHint() const
{
    int months = showDualMonth() ? 2 : 1;
    return QSize(kMargin * 2 + months * 7 * kCellSize + (months - 1) * kMonthGap,
                 kHeaderHeight + kMonthHeaderHeight + kWeekdayHeight + 6 * kCellSize + kActionHeight + kMargin * 2);
}

void QtMaterialDateRangePicker::accept()
{
    emit accepted(startDate(), endDate());
}

void QtMaterialDateRangePicker::cancel()
{
    emit canceled();
}

bool QtMaterialDateRangePicker::event(QEvent *event)
{
    return QWidget::event(event);
}

static QRect monthRectForIndex(const QRect &contentRect, int index, bool dual)
{
    int monthWidth = 7 * kCellSize;
    int x = contentRect.left() + index * (monthWidth + (dual ? kMonthGap : 0));
    return QRect(x, contentRect.top(), monthWidth, kMonthHeaderHeight + kWeekdayHeight + 6 * kCellSize);
}

static QDate dateAtPosition(const QRect &monthRect, const QDate &month, const QPoint &pos)
{
    QRect gridRect(monthRect.left(), monthRect.top() + kMonthHeaderHeight + kWeekdayHeight, 7 * kCellSize, 6 * kCellSize);
    if (!gridRect.contains(pos)) {
        return QDate();
    }
    int column = (pos.x() - gridRect.left()) / kCellSize;
    int row = (pos.y() - gridRect.top()) / kCellSize;

    QDate first(month.year(), month.month(), 1);
    int offset = (first.dayOfWeek() + 6) % 7;
    int cellIndex = row * 7 + column;
    int dayNumber = cellIndex - offset + 1;
    if (dayNumber < 1 || dayNumber > first.daysInMonth()) {
        return QDate();
    }
    return QDate(month.year(), month.month(), dayNumber);
}

void QtMaterialDateRangePicker::mousePressEvent(QMouseEvent *event)
{
    Q_D(QtMaterialDateRangePicker);
    QRect contentRect = rect().adjusted(kMargin, kHeaderHeight + kMargin / 2, -kMargin, -kActionHeight - kMargin / 2);
    int months = d->showDualMonth ? 2 : 1;
    for (int i = 0; i < months; ++i) {
        QDate month = d->displayedMonth.addMonths(i);
        QRect monthRect = monthRectForIndex(contentRect, i, d->showDualMonth);
        QDate clicked = dateAtPosition(monthRect, month, event->pos());
        if (!clicked.isValid()) {
            continue;
        }
        if (clicked < d->minimumDate || clicked > d->maximumDate) {
            return;
        }
        if (!d->startDate.isValid() || d->endDate.isValid()) {
            d->startDate = clicked;
            d->endDate = QDate();
        } else if (clicked < d->startDate) {
            d->endDate = d->startDate;
            d->startDate = clicked;
        } else {
            d->endDate = clicked;
        }
        update();
        emit startDateChanged(d->startDate);
        emit endDateChanged(d->endDate);
        emit dateRangeChanged(d->startDate, d->endDate);
        return;
    }
    QWidget::mousePressEvent(event);
}

void QtMaterialDateRangePicker::mouseMoveEvent(QMouseEvent *event)
{
    Q_D(QtMaterialDateRangePicker);
    d->hoverDate = QDate();
    QRect contentRect = rect().adjusted(kMargin, kHeaderHeight + kMargin / 2, -kMargin, -kActionHeight - kMargin / 2);
    int months = d->showDualMonth ? 2 : 1;
    for (int i = 0; i < months; ++i) {
        QDate month = d->displayedMonth.addMonths(i);
        QRect monthRect = monthRectForIndex(contentRect, i, d->showDualMonth);
        QDate hovered = dateAtPosition(monthRect, month, event->pos());
        if (hovered.isValid()) {
            d->hoverDate = hovered;
            break;
        }
    }
    update();
    QWidget::mouseMoveEvent(event);
}

void QtMaterialDateRangePicker::leaveEvent(QEvent *event)
{
    Q_D(QtMaterialDateRangePicker);
    d->hoverDate = QDate();
    update();
    QWidget::leaveEvent(event);
}

static bool dateInRange(const QDate &date, const QDate &start, const QDate &end)
{
    return start.isValid() && end.isValid() && date >= start && date <= end;
}

void QtMaterialDateRangePicker::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialDateRangePicker);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), palette().color(QPalette::Base));

    QRect header = QRect(0, 0, width(), kHeaderHeight);
    painter.fillRect(header, headerColor());
    painter.setPen(Qt::white);
    QFont titleFont(font());
    titleFont.setBold(true);
    titleFont.setPointSize(titleFont.pointSize() + 2);
    painter.setFont(titleFont);
    QString headerText;
    if (d->startDate.isValid() && d->endDate.isValid()) {
        headerText = d->startDate.toString("dd MMM yyyy") + " — " + d->endDate.toString("dd MMM yyyy");
    } else if (d->startDate.isValid()) {
        headerText = d->startDate.toString("dd MMM yyyy") + " — …";
    } else {
        headerText = tr("Select date range");
    }
    painter.drawText(header.adjusted(kMargin, 0, -kMargin, 0), Qt::AlignVCenter | Qt::AlignLeft, headerText);

    QRect contentRect = rect().adjusted(kMargin, kHeaderHeight + kMargin / 2, -kMargin, -kActionHeight - kMargin / 2);
    static const char *weekdays[] = {"M", "T", "W", "T", "F", "S", "S"};

    int months = d->showDualMonth ? 2 : 1;
    for (int m = 0; m < months; ++m) {
        QDate month = d->displayedMonth.addMonths(m);
        QRect monthRect = monthRectForIndex(contentRect, m, d->showDualMonth);

        painter.setPen(textColor());
        painter.setFont(font());
        painter.drawText(QRect(monthRect.left(), monthRect.top(), monthRect.width(), kMonthHeaderHeight),
                         Qt::AlignCenter,
                         month.toString("MMMM yyyy"));

        for (int i = 0; i < 7; ++i) {
            QRect wRect(monthRect.left() + i * kCellSize, monthRect.top() + kMonthHeaderHeight, kCellSize, kWeekdayHeight);
            painter.setPen(disabledTextColor());
            painter.drawText(wRect, Qt::AlignCenter, QString::fromLatin1(weekdays[i]));
        }

        QDate first(month.year(), month.month(), 1);
        int offset = (first.dayOfWeek() + 6) % 7;
        for (int day = 1; day <= first.daysInMonth(); ++day) {
            int index = offset + day - 1;
            int row = index / 7;
            int col = index % 7;
            QRect cell(monthRect.left() + col * kCellSize,
                       monthRect.top() + kMonthHeaderHeight + kWeekdayHeight + row * kCellSize,
                       kCellSize, kCellSize);

            QDate current(month.year(), month.month(), day);
            bool disabled = current < d->minimumDate || current > d->maximumDate;
            bool selectedEdge = current == d->startDate || current == d->endDate;
            bool ranged = dateInRange(current, d->startDate, d->endDate);
            bool hovered = current == d->hoverDate;

            if (ranged) {
                painter.fillRect(cell.adjusted(2, 8, -2, -8), rangeColor());
            }
            if (selectedEdge) {
                painter.setBrush(selectedColor());
                painter.setPen(Qt::NoPen);
                painter.drawEllipse(cell.adjusted(4, 4, -4, -4));
            }

            painter.setPen(disabled ? disabledTextColor()
                                    : (selectedEdge ? Qt::white : textColor()));
            if (hovered && !selectedEdge && !ranged && !disabled) {
                painter.setPen(QPen(selectedColor(), 1));
                painter.setBrush(Qt::NoBrush);
                painter.drawEllipse(cell.adjusted(6, 6, -6, -6));
                painter.setPen(textColor());
            }
            painter.drawText(cell, Qt::AlignCenter, QString::number(day));
        }
    }

    QRect actionRect(0, height() - kActionHeight, width(), kActionHeight);
    painter.setPen(disabledTextColor());
    painter.drawLine(actionRect.topLeft(), actionRect.topRight());
    painter.setPen(selectedColor());
    painter.drawText(actionRect.adjusted(kMargin, 0, -100, 0), Qt::AlignVCenter | Qt::AlignRight, tr("CANCEL"));
    painter.drawText(actionRect.adjusted(0, 0, -kMargin, 0), Qt::AlignVCenter | Qt::AlignRight, tr("OK"));
}
