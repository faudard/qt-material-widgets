#include "qtmaterialfabmenu.h"
#include "qtmaterialfabmenu_p.h"
#include "qtmaterialfab.h"

#include <QEvent>
#include <QLabel>
#include <QResizeEvent>
#include <QVBoxLayout>
#include <QGraphicsOpacityEffect>

QtMaterialFabMenuPrivate::QtMaterialFabMenuPrivate(QtMaterialFabMenu *q)
    : q_ptr(q)
{
}

QtMaterialFabMenuPrivate::~QtMaterialFabMenuPrivate()
{
}

void QtMaterialFabMenuPrivate::init()
{
    Q_Q(QtMaterialFabMenu);

    useThemeColors = true;
    expanded = false;
    labelsVisible = true;
    actionSpacing = 12;
    corner = Qt::BottomRightCorner;
    overlayColor = QColor(0, 0, 0, 80);

    q->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    q->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainButton = new QtMaterialFloatingActionButton(QIcon(), q);
    mainButton->setToolTip(QStringLiteral("FAB menu"));
    mainButton->show();

    QObject::connect(mainButton, &QtMaterialFloatingActionButton::clicked,
                     q, &QtMaterialFabMenu::toggleExpanded);

    updatePalette();
    updateGeometry();

    if (q->parentWidget()) {
        q->parentWidget()->installEventFilter(q);
    }
}

void QtMaterialFabMenuPrivate::updatePalette()
{
    Q_Q(QtMaterialFabMenu);

    QColor bg = useThemeColors ? QColor(33, 150, 243) : backgroundColor;
    QColor fg = useThemeColors ? QColor(Qt::white) : foregroundColor;

    if (mainButton) {
        mainButton->setBackgroundColor(bg);
        mainButton->setForegroundColor(fg);
    }

    for (QtMaterialFloatingActionButton *button : actionButtons) {
        if (!button) {
            continue;
        }
        button->setBackgroundColor(bg);
        button->setForegroundColor(fg);
    }

    for (QWidget *labelWidget : labelWidgets) {
        QLabel *label = qobject_cast<QLabel *>(labelWidget);
        if (!label) {
            continue;
        }
        label->setStyleSheet(QStringLiteral(
            "QLabel { background: rgba(40,40,40,220); color: white; "
            "border-radius: 4px; padding: 6px 10px; }"));
        label->setVisible(labelsVisible && expanded);
    }
}

QPoint QtMaterialFabMenuPrivate::anchorPoint() const
{
    Q_Q(const QtMaterialFabMenu);
    const int marginX = 24;
    const int marginY = 24;
    const QSize mainSize = mainButton ? mainButton->sizeHint() : QSize(56, 56);

    switch (corner) {
    case Qt::TopLeftCorner:
        return QPoint(marginX, marginY);
    case Qt::TopRightCorner:
        return QPoint(q->width() - marginX - mainSize.width(), marginY);
    case Qt::BottomLeftCorner:
        return QPoint(marginX, q->height() - marginY - mainSize.height());
    case Qt::BottomRightCorner:
    default:
        return QPoint(q->width() - marginX - mainSize.width(),
                      q->height() - marginY - mainSize.height());
    }
}

QRect QtMaterialFabMenuPrivate::anchorGeometryForIndex(int index) const
{
    const QPoint anchor = anchorPoint();
    const QSize actionSize = mainButton ? mainButton->sizeHint() : QSize(56, 56);
    const int delta = (actionSize.height() + actionSpacing) * (index + 1);

    switch (corner) {
    case Qt::TopLeftCorner:
    case Qt::TopRightCorner:
        return QRect(anchor.x(), anchor.y() + delta, actionSize.width(), actionSize.height());
    case Qt::BottomLeftCorner:
    case Qt::BottomRightCorner:
    default:
        return QRect(anchor.x(), anchor.y() - delta, actionSize.width(), actionSize.height());
    }
}

void QtMaterialFabMenuPrivate::updateGeometry()
{
    Q_Q(QtMaterialFabMenu);

    if (!mainButton) {
        return;
    }

    const QRect mainRect(anchorPoint(), mainButton->sizeHint());
    mainButton->setGeometry(mainRect);

    for (int i = 0; i < actionButtons.size(); ++i) {
        QtMaterialFloatingActionButton *button = actionButtons.at(i);
        QWidget *labelWidget = i < labelWidgets.size() ? labelWidgets.at(i) : 0;
        if (!button) {
            continue;
        }

        const QRect target = anchorGeometryForIndex(i);
        button->setGeometry(expanded ? target : mainRect);
        button->setVisible(expanded);

        if (labelWidget) {
            const QSize hint = labelWidget->sizeHint();
            QRect labelRect(0, 0, hint.width(), hint.height());
            labelRect.moveCenter(target.center());

            if (corner == Qt::TopLeftCorner || corner == Qt::BottomLeftCorner) {
                labelRect.moveLeft(target.right() + 12);
            } else {
                labelRect.moveRight(target.left() - 12);
            }

            labelWidget->setGeometry(labelRect);
            labelWidget->setVisible(labelsVisible && expanded);
        }
    }
}

QtMaterialFabMenu::QtMaterialFabMenu(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialFabMenuPrivate(this))
{
    Q_D(QtMaterialFabMenu);
    d->init();
}

QtMaterialFabMenu::~QtMaterialFabMenu()
{
}

int QtMaterialFabMenu::addAction(const QIcon &icon, const QString &toolTip, const QString &label)
{
    Q_D(QtMaterialFabMenu);

    QtMaterialFloatingActionButton *button = new QtMaterialFloatingActionButton(icon, this);
    button->setMini(true);
    button->setToolTip(toolTip);
    button->hide();

    QLabel *labelWidget = new QLabel(label, this);
    labelWidget->hide();

    const int index = d->actionButtons.size();
    d->actionButtons << button;
    d->labelWidgets << labelWidget;
    d->labelTexts << label;

    connect(button, &QtMaterialFloatingActionButton::clicked, this, [this, index]() {
        emit actionTriggered(index);
        collapse();
    });

    d->updatePalette();
    d->updateGeometry();
    return index;
}

void QtMaterialFabMenu::removeAction(int index)
{
    Q_D(QtMaterialFabMenu);
    if (index < 0 || index >= d->actionButtons.size()) {
        return;
    }

    delete d->actionButtons.takeAt(index);
    delete d->labelWidgets.takeAt(index);
    d->labelTexts.removeAt(index);
    d->updateGeometry();
}

int QtMaterialFabMenu::count() const
{
    Q_D(const QtMaterialFabMenu);
    return d->actionButtons.size();
}

void QtMaterialFabMenu::setUseThemeColors(bool value)
{
    Q_D(QtMaterialFabMenu);
    if (d->useThemeColors == value) {
        return;
    }
    d->useThemeColors = value;
    d->updatePalette();
    update();
}

bool QtMaterialFabMenu::useThemeColors() const
{
    Q_D(const QtMaterialFabMenu);
    return d->useThemeColors;
}

void QtMaterialFabMenu::setExpanded(bool value)
{
    Q_D(QtMaterialFabMenu);
    if (d->expanded == value) {
        return;
    }
    d->expanded = value;
    d->updateGeometry();
    emit expandedChanged(value);
    update();
}

bool QtMaterialFabMenu::isExpanded() const
{
    Q_D(const QtMaterialFabMenu);
    return d->expanded;
}

void QtMaterialFabMenu::expand()
{
    setExpanded(true);
}

void QtMaterialFabMenu::collapse()
{
    setExpanded(false);
}

void QtMaterialFabMenu::toggleExpanded()
{
    setExpanded(!isExpanded());
}

void QtMaterialFabMenu::setLabelsVisible(bool value)
{
    Q_D(QtMaterialFabMenu);
    if (d->labelsVisible == value) {
        return;
    }
    d->labelsVisible = value;
    d->updatePalette();
    d->updateGeometry();
}

bool QtMaterialFabMenu::labelsVisible() const
{
    Q_D(const QtMaterialFabMenu);
    return d->labelsVisible;
}

void QtMaterialFabMenu::setActionSpacing(int value)
{
    Q_D(QtMaterialFabMenu);
    if (d->actionSpacing == value) {
        return;
    }
    d->actionSpacing = value;
    d->updateGeometry();
}

int QtMaterialFabMenu::actionSpacing() const
{
    Q_D(const QtMaterialFabMenu);
    return d->actionSpacing;
}

void QtMaterialFabMenu::setCorner(Qt::Corner corner)
{
    Q_D(QtMaterialFabMenu);
    if (d->corner == corner) {
        return;
    }
    d->corner = corner;
    d->updateGeometry();
}

Qt::Corner QtMaterialFabMenu::corner() const
{
    Q_D(const QtMaterialFabMenu);
    return d->corner;
}

void QtMaterialFabMenu::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialFabMenu);
    d->backgroundColor = color;
    d->useThemeColors = false;
    d->updatePalette();
}

QColor QtMaterialFabMenu::backgroundColor() const
{
    Q_D(const QtMaterialFabMenu);
    return d->useThemeColors ? QColor(33, 150, 243) : d->backgroundColor;
}

void QtMaterialFabMenu::setForegroundColor(const QColor &color)
{
    Q_D(QtMaterialFabMenu);
    d->foregroundColor = color;
    d->useThemeColors = false;
    d->updatePalette();
}

QColor QtMaterialFabMenu::foregroundColor() const
{
    Q_D(const QtMaterialFabMenu);
    return d->useThemeColors ? QColor(Qt::white) : d->foregroundColor;
}

void QtMaterialFabMenu::setOverlayColor(const QColor &color)
{
    Q_D(QtMaterialFabMenu);
    d->overlayColor = color;
    update();
}

QColor QtMaterialFabMenu::overlayColor() const
{
    Q_D(const QtMaterialFabMenu);
    return d->overlayColor;
}

bool QtMaterialFabMenu::eventFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(obj)
    switch (event->type()) {
    case QEvent::Resize:
    case QEvent::Move:
        d_func()->updateGeometry();
        break;
    default:
        break;
    }
    return QWidget::eventFilter(obj, event);
}

void QtMaterialFabMenu::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    d_func()->updateGeometry();
}