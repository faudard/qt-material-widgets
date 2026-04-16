#include "qtmaterialmodalbottomsheet.h"
#include "qtmaterialmodalbottomsheet_p.h"

#include <QEvent>
#include <QFrame>
#include <QLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QResizeEvent>
#include <QVBoxLayout>

QtMaterialModalBottomSheetPrivate::QtMaterialModalBottomSheetPrivate(QtMaterialModalBottomSheet *q)
    : q_ptr(q)
{
}

QtMaterialModalBottomSheetPrivate::~QtMaterialModalBottomSheetPrivate()
{
}

void QtMaterialModalBottomSheetPrivate::init()
{
    Q_Q(QtMaterialModalBottomSheet);

    useThemeColors = true;
    open = false;
    dismissOnOverlayClick = true;
    sheetHeight = 280;
    overlayColor = QColor(0, 0, 0, 96);

    q->setAttribute(Qt::WA_NoSystemBackground, true);
    q->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    q->setVisible(false);

    sheet = new QFrame(q);
    sheet->setObjectName(QStringLiteral("materialModalBottomSheet"));
    sheet->setFrameShape(QFrame::NoFrame);
    sheetLayout = new QVBoxLayout;
    sheetLayout->setContentsMargins(24, 24, 24, 24);
    sheetLayout->setSpacing(16);
    sheet->setLayout(sheetLayout);

    if (q->parentWidget()) {
        q->setGeometry(q->parentWidget()->rect());
        q->parentWidget()->installEventFilter(q);
    }

    updatePalette();
    updateLayoutGeometry();
}

void QtMaterialModalBottomSheetPrivate::updatePalette()
{
    QColor bg = useThemeColors ? QColor(Qt::white) : backgroundColor;

    if (sheet) {
        sheet->setStyleSheet(QStringLiteral(
            "QFrame#materialModalBottomSheet { background: %1; border-top-left-radius: 16px; border-top-right-radius: 16px; }"
        ).arg(bg.name()));
    }
}

void QtMaterialModalBottomSheetPrivate::updateLayoutGeometry()
{
    Q_Q(QtMaterialModalBottomSheet);
    if (!sheet) {
        return;
    }

    const QRect r = q->rect();
    sheet->setGeometry(0, open ? (r.height() - sheetHeight) : r.height(), r.width(), sheetHeight);
}

QtMaterialModalBottomSheet::QtMaterialModalBottomSheet(QWidget *parent)
    : QWidget(parent), d_ptr(new QtMaterialModalBottomSheetPrivate(this))
{
    Q_D(QtMaterialModalBottomSheet);
    d->init();
}

QtMaterialModalBottomSheet::~QtMaterialModalBottomSheet()
{
}

void QtMaterialModalBottomSheet::setUseThemeColors(bool value)
{
    Q_D(QtMaterialModalBottomSheet);
    if (d->useThemeColors == value) {
        return;
    }
    d->useThemeColors = value;
    d->updatePalette();
}

bool QtMaterialModalBottomSheet::useThemeColors() const
{
    Q_D(const QtMaterialModalBottomSheet);
    return d->useThemeColors;
}

void QtMaterialModalBottomSheet::setOpen(bool value)
{
    Q_D(QtMaterialModalBottomSheet);
    if (d->open == value) {
        return;
    }
    d->open = value;
    setVisible(value);
    d->updateLayoutGeometry();
    emit openChanged(value);
}

bool QtMaterialModalBottomSheet::isOpen() const
{
    Q_D(const QtMaterialModalBottomSheet);
    return d->open;
}

void QtMaterialModalBottomSheet::open()
{
    setOpen(true);
}

void QtMaterialModalBottomSheet::closeSheet()
{
    setOpen(false);
}

void QtMaterialModalBottomSheet::toggle()
{
    setOpen(!isOpen());
}

void QtMaterialModalBottomSheet::setDismissOnOverlayClick(bool value)
{
    Q_D(QtMaterialModalBottomSheet);
    d->dismissOnOverlayClick = value;
}

bool QtMaterialModalBottomSheet::dismissOnOverlayClick() const
{
    Q_D(const QtMaterialModalBottomSheet);
    return d->dismissOnOverlayClick;
}

void QtMaterialModalBottomSheet::setSheetHeight(int value)
{
    Q_D(QtMaterialModalBottomSheet);
    d->sheetHeight = qMax(120, value);
    d->updateLayoutGeometry();
}

int QtMaterialModalBottomSheet::sheetHeight() const
{
    Q_D(const QtMaterialModalBottomSheet);
    return d->sheetHeight;
}

void QtMaterialModalBottomSheet::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialModalBottomSheet);
    d->backgroundColor = color;
    d->updatePalette();
}

QColor QtMaterialModalBottomSheet::backgroundColor() const
{
    Q_D(const QtMaterialModalBottomSheet);
    return d->useThemeColors ? QColor(Qt::white) : d->backgroundColor;
}

void QtMaterialModalBottomSheet::setOverlayColor(const QColor &color)
{
    Q_D(QtMaterialModalBottomSheet);
    d->overlayColor = color;
    update();
}

QColor QtMaterialModalBottomSheet::overlayColor() const
{
    Q_D(const QtMaterialModalBottomSheet);
    return d->overlayColor;
}

void QtMaterialModalBottomSheet::setContentLayout(QLayout *layout)
{
    Q_D(QtMaterialModalBottomSheet);
    if (!layout || !d->sheet) {
        return;
    }
    delete d->sheet->layout();
    d->sheet->setLayout(layout);
}

QLayout *QtMaterialModalBottomSheet::contentLayout() const
{
    Q_D(const QtMaterialModalBottomSheet);
    return d->sheet ? d->sheet->layout() : 0;
}

bool QtMaterialModalBottomSheet::eventFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(obj)
    if (parentWidget() && event->type() == QEvent::Resize) {
        setGeometry(parentWidget()->rect());
        Q_D(QtMaterialModalBottomSheet);
        d->updateLayoutGeometry();
    }
    return QWidget::eventFilter(obj, event);
}

void QtMaterialModalBottomSheet::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    Q_D(QtMaterialModalBottomSheet);
    d->updateLayoutGeometry();
}

void QtMaterialModalBottomSheet::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    Q_D(QtMaterialModalBottomSheet);
    QPainter painter(this);
    painter.fillRect(rect(), d->overlayColor);
}
