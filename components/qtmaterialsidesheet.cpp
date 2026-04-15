#include "qtmaterialsidesheet.h"
#include "qtmaterialsidesheet_p.h"
#include "lib/qtmaterialstyle.h"

#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QVBoxLayout>

QtMaterialSideSheetPrivate::QtMaterialSideSheetPrivate(QtMaterialSideSheet *q)
    : q_ptr(q), sheet(0), contentLayout(0), useThemeColors(true), sheetWidth(320),
      modal(true), dismissOnOverlayClick(true), edge(QtMaterialSideSheet::Right), opened(false)
{
}

QtMaterialSideSheetPrivate::~QtMaterialSideSheetPrivate()
{
}

void QtMaterialSideSheetPrivate::init()
{
    Q_Q(QtMaterialSideSheet);

    sheet = new QWidget(q);
    sheet->setObjectName("materialSideSheetPanel");
    sheet->setAutoFillBackground(false);
    sheet->installEventFilter(q);
    sheet->show();

    updateSheetGeometry();
    q->hide();
}

void QtMaterialSideSheetPrivate::updateSheetGeometry()
{
    Q_Q(QtMaterialSideSheet);
    if (!sheet) {
        return;
    }

    const int w = qMin(sheetWidth, q->width());
    const int x = (edge == QtMaterialSideSheet::Left) ? 0 : q->width() - w;
    sheet->setGeometry(x, 0, w, q->height());
}

QColor QtMaterialSideSheetPrivate::resolveBackgroundColor() const
{
    if (useThemeColors || !backgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("canvas");
    }
    return backgroundColor;
}

QColor QtMaterialSideSheetPrivate::resolveOverlayColor() const
{
    if (useThemeColors || !overlayColor.isValid()) {
        QColor c(0, 0, 0, 90);
        return c;
    }
    return overlayColor;
}

QtMaterialSideSheet::QtMaterialSideSheet(QWidget *parent)
    : QtMaterialOverlayWidget(parent), d_ptr(new QtMaterialSideSheetPrivate(this))
{
    d_func()->init();
}

QtMaterialSideSheet::~QtMaterialSideSheet()
{
}

void QtMaterialSideSheet::setUseThemeColors(bool value)
{
    Q_D(QtMaterialSideSheet);
    d->useThemeColors = value;
    update();
    if (d->sheet) {
        d->sheet->update();
    }
}

bool QtMaterialSideSheet::useThemeColors() const
{
    Q_D(const QtMaterialSideSheet);
    return d->useThemeColors;
}

void QtMaterialSideSheet::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialSideSheet);
    d->backgroundColor = color;
    update();
    if (d->sheet) {
        d->sheet->update();
    }
}

QColor QtMaterialSideSheet::backgroundColor() const
{
    Q_D(const QtMaterialSideSheet);
    return d->backgroundColor;
}

void QtMaterialSideSheet::setOverlayColor(const QColor &color)
{
    Q_D(QtMaterialSideSheet);
    d->overlayColor = color;
    update();
}

QColor QtMaterialSideSheet::overlayColor() const
{
    Q_D(const QtMaterialSideSheet);
    return d->overlayColor;
}

void QtMaterialSideSheet::setSheetWidth(int width)
{
    Q_D(QtMaterialSideSheet);
    d->sheetWidth = qMax(160, width);
    d->updateSheetGeometry();
}

int QtMaterialSideSheet::sheetWidth() const
{
    Q_D(const QtMaterialSideSheet);
    return d->sheetWidth;
}

void QtMaterialSideSheet::setModal(bool value)
{
    Q_D(QtMaterialSideSheet);
    d->modal = value;
}

bool QtMaterialSideSheet::isModal() const
{
    Q_D(const QtMaterialSideSheet);
    return d->modal;
}

void QtMaterialSideSheet::setDismissOnOverlayClick(bool value)
{
    Q_D(QtMaterialSideSheet);
    d->dismissOnOverlayClick = value;
}

bool QtMaterialSideSheet::dismissOnOverlayClick() const
{
    Q_D(const QtMaterialSideSheet);
    return d->dismissOnOverlayClick;
}

void QtMaterialSideSheet::setEdge(Side side)
{
    Q_D(QtMaterialSideSheet);
    d->edge = side;
    d->updateSheetGeometry();
}

QtMaterialSideSheet::Side QtMaterialSideSheet::edge() const
{
    Q_D(const QtMaterialSideSheet);
    return d->edge;
}

void QtMaterialSideSheet::setContentLayout(QLayout *layout)
{
    Q_D(QtMaterialSideSheet);
    if (d->contentLayout == layout) {
        return;
    }
    if (d->sheet->layout()) {
        delete d->sheet->layout();
    }
    d->contentLayout = layout;
    d->sheet->setLayout(layout);
}

QLayout *QtMaterialSideSheet::contentLayout() const
{
    Q_D(const QtMaterialSideSheet);
    return d->contentLayout;
}

void QtMaterialSideSheet::open()
{
    Q_D(QtMaterialSideSheet);
    d->opened = true;
    show();
    raise();
    emit opened();
}

void QtMaterialSideSheet::closeSheet()
{
    Q_D(QtMaterialSideSheet);
    d->opened = false;
    hide();
    emit closed();
}

bool QtMaterialSideSheet::event(QEvent *event)
{
    return QtMaterialOverlayWidget::event(event);
}

bool QtMaterialSideSheet::eventFilter(QObject *obj, QEvent *event)
{
    Q_D(QtMaterialSideSheet);
    if (obj == d->sheet) {
        if (event->type() == QEvent::Paint) {
            QPainter painter(d->sheet);
            painter.fillRect(d->sheet->rect(), d->resolveBackgroundColor());
            return false;
        }
        return false;
    }

    if (event->type() == QEvent::MouseButtonPress && d->dismissOnOverlayClick) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (!d->sheet->geometry().contains(mouseEvent->pos())) {
            closeSheet();
            return d->modal;
        }
    }
    return QtMaterialOverlayWidget::eventFilter(obj, event);
}

void QtMaterialSideSheet::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    Q_D(QtMaterialSideSheet);
    QPainter painter(this);
    painter.fillRect(rect(), d->resolveOverlayColor());
}

void QtMaterialSideSheet::resizeEvent(QResizeEvent *event)
{
    QtMaterialOverlayWidget::resizeEvent(event);
    d_func()->updateSheetGeometry();
}
