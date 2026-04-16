#include "qtmaterialtopappbarscrollcontroller.h"
#include "qtmaterialtopappbarscrollcontroller_p.h"

#include <QAbstractScrollArea>
#include <QScrollBar>
#include <QWidget>

QtMaterialTopAppBarScrollControllerPrivate::QtMaterialTopAppBarScrollControllerPrivate()
    : target(0)
    , scrollArea(0)
    , expandedHeight(152)
    , collapsedHeight(64)
    , colorShiftEnabled(true)
    , collapseProgress(0)
{
}

QtMaterialTopAppBarScrollController::QtMaterialTopAppBarScrollController(QObject *parent)
    : QObject(parent)
    , d_ptr(new QtMaterialTopAppBarScrollControllerPrivate)
{
}

QtMaterialTopAppBarScrollController::~QtMaterialTopAppBarScrollController()
{
}

void QtMaterialTopAppBarScrollController::setScrollArea(QAbstractScrollArea *area)
{
    Q_D(QtMaterialTopAppBarScrollController);

    if (d->scrollArea == area) {
        return;
    }

    if (d->scrollArea) {
        disconnect(d->scrollArea->verticalScrollBar(), 0, this, 0);
    }

    d->scrollArea = area;

    if (d->scrollArea) {
        connect(d->scrollArea->verticalScrollBar(), SIGNAL(valueChanged(int)),
                this, SLOT(updateFromScrollPosition(int)));
    }
}

QAbstractScrollArea *QtMaterialTopAppBarScrollController::scrollArea() const
{
    Q_D(const QtMaterialTopAppBarScrollController);
    return d->scrollArea;
}

void QtMaterialTopAppBarScrollController::setTarget(QWidget *target)
{
    Q_D(QtMaterialTopAppBarScrollController);
    d->target = target;
}

QWidget *QtMaterialTopAppBarScrollController::target() const
{
    Q_D(const QtMaterialTopAppBarScrollController);
    return d->target;
}

void QtMaterialTopAppBarScrollController::setExpandedHeight(int value)
{
    Q_D(QtMaterialTopAppBarScrollController);
    d->expandedHeight = value;
}

int QtMaterialTopAppBarScrollController::expandedHeight() const
{
    Q_D(const QtMaterialTopAppBarScrollController);
    return d->expandedHeight;
}

void QtMaterialTopAppBarScrollController::setCollapsedHeight(int value)
{
    Q_D(QtMaterialTopAppBarScrollController);
    d->collapsedHeight = value;
}

int QtMaterialTopAppBarScrollController::collapsedHeight() const
{
    Q_D(const QtMaterialTopAppBarScrollController);
    return d->collapsedHeight;
}

void QtMaterialTopAppBarScrollController::setColorShiftEnabled(bool value)
{
    Q_D(QtMaterialTopAppBarScrollController);
    d->colorShiftEnabled = value;
}

bool QtMaterialTopAppBarScrollController::colorShiftEnabled() const
{
    Q_D(const QtMaterialTopAppBarScrollController);
    return d->colorShiftEnabled;
}

qreal QtMaterialTopAppBarScrollController::collapseProgress() const
{
    Q_D(const QtMaterialTopAppBarScrollController);
    return d->collapseProgress;
}

void QtMaterialTopAppBarScrollController::updateFromScrollPosition(int value)
{
    Q_D(QtMaterialTopAppBarScrollController);

    const int delta = qMax(1, d->expandedHeight - d->collapsedHeight);
    const qreal progress = qBound<qreal>(0, qreal(value) / qreal(delta), 1);

    if (qFuzzyCompare(progress, d->collapseProgress)) {
        return;
    }

    d->collapseProgress = progress;

    if (d->target) {
        const int height = d->expandedHeight - qRound(delta * progress);
        d->target->setMinimumHeight(height);
        d->target->setMaximumHeight(height);
        d->target->update();
    }

    emit collapseProgressChanged(progress);
}
