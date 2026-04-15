#include "qtmaterialbottomsheet.h"
#include "qtmaterialbottomsheet_p.h"
#include "lib/qtmaterialstyle.h"

#include <QEvent>
#include <QLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QState>
#include <QStateMachine>
#include <QVBoxLayout>
#include <QWidget>

QtMaterialBottomSheetPrivate::QtMaterialBottomSheetPrivate(QtMaterialBottomSheet *q)
    : q_ptr(q),
      sheetWidget(0),
      sheetLayout(0),
      stateMachine(0),
      hiddenState(0),
      visibleState(0),
      offsetAnimation(0),
      useThemeColors(true),
      modal(true),
      dismissOnOverlayClick(true),
      sheetHeight(240),
      offset(1.0)
{
}

QtMaterialBottomSheetPrivate::~QtMaterialBottomSheetPrivate()
{
}

void QtMaterialBottomSheetPrivate::init()
{
    Q_Q(QtMaterialBottomSheet);

    sheetWidget = new QWidget(q);
    sheetWidget->setObjectName("materialBottomSheetSurface");
    sheetWidget->setAttribute(Qt::WA_TransparentForMouseEvents, false);

    QVBoxLayout *layout = new QVBoxLayout(sheetWidget);
    layout->setContentsMargins(24, 24, 24, 24);
    layout->setSpacing(16);
    sheetLayout = layout;

    stateMachine = new QStateMachine(q);
    hiddenState = new QState;
    visibleState = new QState;

    hiddenState->assignProperty(q, "visible", false);
    hiddenState->assignProperty(q, "offset", 1.0);
    visibleState->assignProperty(q, "visible", true);
    visibleState->assignProperty(q, "offset", 0.0);

    offsetAnimation = new QPropertyAnimation(q, "offset", q);
    offsetAnimation->setDuration(220);
    offsetAnimation->setEasingCurve(QEasingCurve::OutCubic);

    hiddenState->addTransition(q, SIGNAL(opened()), visibleState);
    visibleState->addTransition(q, SIGNAL(closed()), hiddenState);

    stateMachine->addState(hiddenState);
    stateMachine->addState(visibleState);
    stateMachine->setInitialState(hiddenState);
    stateMachine->start();

    q->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    q->setVisible(false);
    updateSheetGeometry();
}

QRect QtMaterialBottomSheetPrivate::sheetRect() const
{
    Q_Q(const QtMaterialBottomSheet);
    const QRect r = q->rect();
    const int h = qMin(sheetHeight, r.height());
    const int y = r.bottom() - h + 1 + qRound(offset * h);
    return QRect(r.left(), y, r.width(), h);
}

void QtMaterialBottomSheetPrivate::updateSheetGeometry()
{
    if (sheetWidget) {
        sheetWidget->setGeometry(sheetRect());
        sheetWidget->raise();
    }
}

QtMaterialBottomSheet::QtMaterialBottomSheet(QWidget *parent)
    : QtMaterialOverlayWidget(parent),
      d_ptr(new QtMaterialBottomSheetPrivate(this))
{
    Q_D(QtMaterialBottomSheet);
    d->init();
}

QtMaterialBottomSheet::~QtMaterialBottomSheet()
{
}

void QtMaterialBottomSheet::setUseThemeColors(bool value)
{
    Q_D(QtMaterialBottomSheet);
    if (d->useThemeColors == value)
        return;
    d->useThemeColors = value;
    update();
}

bool QtMaterialBottomSheet::useThemeColors() const
{
    Q_D(const QtMaterialBottomSheet);
    return d->useThemeColors;
}

void QtMaterialBottomSheet::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialBottomSheet);
    d->backgroundColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialBottomSheet::backgroundColor() const
{
    Q_D(const QtMaterialBottomSheet);
    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("canvas");
    }
    return d->backgroundColor;
}

void QtMaterialBottomSheet::setOverlayColor(const QColor &color)
{
    Q_D(QtMaterialBottomSheet);
    d->overlayColor = color;
    update();
}

QColor QtMaterialBottomSheet::overlayColor() const
{
    Q_D(const QtMaterialBottomSheet);
    return d->overlayColor.isValid() ? d->overlayColor : QColor(0, 0, 0, 90);
}

void QtMaterialBottomSheet::setSheetHeight(int height)
{
    Q_D(QtMaterialBottomSheet);
    d->sheetHeight = qMax(0, height);
    d->updateSheetGeometry();
    update();
}

int QtMaterialBottomSheet::sheetHeight() const
{
    Q_D(const QtMaterialBottomSheet);
    return d->sheetHeight;
}

void QtMaterialBottomSheet::setModal(bool value)
{
    Q_D(QtMaterialBottomSheet);
    d->modal = value;
}

bool QtMaterialBottomSheet::isModal() const
{
    Q_D(const QtMaterialBottomSheet);
    return d->modal;
}

void QtMaterialBottomSheet::setDismissOnOverlayClick(bool value)
{
    Q_D(QtMaterialBottomSheet);
    d->dismissOnOverlayClick = value;
}

bool QtMaterialBottomSheet::dismissOnOverlayClick() const
{
    Q_D(const QtMaterialBottomSheet);
    return d->dismissOnOverlayClick;
}

void QtMaterialBottomSheet::setContentLayout(QLayout *layout)
{
    Q_D(QtMaterialBottomSheet);
    if (!layout || d->sheetLayout == layout)
        return;

    if (d->sheetWidget->layout()) {
        delete d->sheetWidget->layout();
    }
    d->sheetWidget->setLayout(layout);
    d->sheetLayout = layout;
    d->updateSheetGeometry();
}

QLayout *QtMaterialBottomSheet::contentLayout() const
{
    Q_D(const QtMaterialBottomSheet);
    return d->sheetLayout;
}

void QtMaterialBottomSheet::showSheet()
{
    setVisible(true);
    raise();
    emit opened();
}

void QtMaterialBottomSheet::hideSheet()
{
    emit closed();
    setVisible(false);
}

bool QtMaterialBottomSheet::eventFilter(QObject *obj, QEvent *event)
{
    Q_D(QtMaterialBottomSheet);

    if (obj == parentWidget() && event->type() == QEvent::Resize) {
        setGeometry(overlayGeometry());
        d->updateSheetGeometry();
    }

    if (event->type() == QEvent::MouseButtonPress && d->dismissOnOverlayClick) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (!d->sheetRect().contains(mouseEvent->pos())) {
            hideSheet();
            return d->modal;
        }
    }

    return QtMaterialOverlayWidget::eventFilter(obj, event);
}

void QtMaterialBottomSheet::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    Q_D(QtMaterialBottomSheet);

    d->updateSheetGeometry();

    QPainter painter(this);
    painter.fillRect(rect(), overlayColor());
    painter.fillRect(d->sheetRect(), backgroundColor());
}

QRect QtMaterialBottomSheet::overlayGeometry() const
{
    if (parentWidget()) {
        return parentWidget()->rect();
    }
    return rect();
}
