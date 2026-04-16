#include "qtmaterialsheethandle.h"
#include "qtmaterialsheethandle_p.h"

#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>

QtMaterialSheetHandlePrivate::QtMaterialSheetHandlePrivate(QtMaterialSheetHandle *q)
    : q_ptr(q)
{
}

QtMaterialSheetHandlePrivate::~QtMaterialSheetHandlePrivate()
{
}

void QtMaterialSheetHandlePrivate::init()
{
    useThemeColors = true;
    color = QColor(0, 0, 0, 90);
    handleWidth = 32;
    handleHeight = 4;
    hitTargetSize = 48;
    cycleDetentsOnClick = true;
    pressed = false;
    dragging = false;
}

QtMaterialSheetHandle::QtMaterialSheetHandle(QWidget *parent)
    : QWidget(parent), d_ptr(new QtMaterialSheetHandlePrivate(this))
{
    Q_D(QtMaterialSheetHandle);
    d->init();
    setFocusPolicy(Qt::StrongFocus);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    setCursor(Qt::SizeVerCursor);
}

QtMaterialSheetHandle::~QtMaterialSheetHandle()
{
}

void QtMaterialSheetHandle::setUseThemeColors(bool value)
{
    Q_D(QtMaterialSheetHandle);
    if (d->useThemeColors == value) return;
    d->useThemeColors = value;
    update();
}

bool QtMaterialSheetHandle::useThemeColors() const
{
    Q_D(const QtMaterialSheetHandle);
    return d->useThemeColors;
}

void QtMaterialSheetHandle::setColor(const QColor &color)
{
    Q_D(QtMaterialSheetHandle);
    d->color = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialSheetHandle::color() const
{
    Q_D(const QtMaterialSheetHandle);
    return d->color;
}

void QtMaterialSheetHandle::setHandleWidth(int value)
{
    Q_D(QtMaterialSheetHandle);
    d->handleWidth = qMax(8, value);
    updateGeometry();
    update();
}

int QtMaterialSheetHandle::handleWidth() const
{
    Q_D(const QtMaterialSheetHandle);
    return d->handleWidth;
}

void QtMaterialSheetHandle::setHandleHeight(int value)
{
    Q_D(QtMaterialSheetHandle);
    d->handleHeight = qMax(2, value);
    updateGeometry();
    update();
}

int QtMaterialSheetHandle::handleHeight() const
{
    Q_D(const QtMaterialSheetHandle);
    return d->handleHeight;
}

void QtMaterialSheetHandle::setHitTargetSize(int value)
{
    Q_D(QtMaterialSheetHandle);
    d->hitTargetSize = qMax(24, value);
    updateGeometry();
}

int QtMaterialSheetHandle::hitTargetSize() const
{
    Q_D(const QtMaterialSheetHandle);
    return d->hitTargetSize;
}

void QtMaterialSheetHandle::setCycleDetentsOnClick(bool value)
{
    Q_D(QtMaterialSheetHandle);
    d->cycleDetentsOnClick = value;
}

bool QtMaterialSheetHandle::cycleDetentsOnClick() const
{
    Q_D(const QtMaterialSheetHandle);
    return d->cycleDetentsOnClick;
}

QSize QtMaterialSheetHandle::sizeHint() const
{
    Q_D(const QtMaterialSheetHandle);
    return QSize(qMax(d->hitTargetSize, d->handleWidth + 16), d->hitTargetSize);
}

QSize QtMaterialSheetHandle::minimumSizeHint() const
{
    return sizeHint();
}

void QtMaterialSheetHandle::paintEvent(QPaintEvent *)
{
    Q_D(QtMaterialSheetHandle);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor c = d->color;
    if (!isEnabled()) {
        c.setAlpha(50);
    } else if (d->pressed) {
        c.setAlpha(qMin(255, c.alpha() + 50));
    }

    QRect r((width() - d->handleWidth) / 2,
            (height() - d->handleHeight) / 2,
            d->handleWidth,
            d->handleHeight);
    painter.setPen(Qt::NoPen);
    painter.setBrush(c);
    painter.drawRoundedRect(r, d->handleHeight / 2.0, d->handleHeight / 2.0);
}

void QtMaterialSheetHandle::mousePressEvent(QMouseEvent *event)
{
    Q_D(QtMaterialSheetHandle);
    if (event->button() != Qt::LeftButton) {
        QWidget::mousePressEvent(event);
        return;
    }
    d->pressed = true;
    d->pressPos = event->pos();
    emit dragStarted();
    update();
}

void QtMaterialSheetHandle::mouseMoveEvent(QMouseEvent *event)
{
    Q_D(QtMaterialSheetHandle);
    if (!d->pressed) {
        QWidget::mouseMoveEvent(event);
        return;
    }
    d->dragging = true;
    emit dragDeltaChanged(event->pos() - d->pressPos);
}

void QtMaterialSheetHandle::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(QtMaterialSheetHandle);
    if (!d->pressed || event->button() != Qt::LeftButton) {
        QWidget::mouseReleaseEvent(event);
        return;
    }
    bool wasDragging = d->dragging;
    d->pressed = false;
    d->dragging = false;
    update();

    if (!wasDragging) {
        emit clicked();
        if (d->cycleDetentsOnClick) {
            emit cycleRequested();
        }
    }
    emit dragFinished();
}

void QtMaterialSheetHandle::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Space:
    case Qt::Key_Return:
    case Qt::Key_Enter:
        emit clicked();
        emit cycleRequested();
        event->accept();
        return;
    default:
        break;
    }
    QWidget::keyPressEvent(event);
}
