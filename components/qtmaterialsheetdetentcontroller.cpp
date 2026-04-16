#include "qtmaterialsheetdetentcontroller.h"
#include "qtmaterialsheetdetentcontroller_p.h"

#include <QWidget>
#include <QtMath>

QtMaterialSheetDetentControllerPrivate::QtMaterialSheetDetentControllerPrivate(QtMaterialSheetDetentController *q)
    : q_ptr(q),
      orientation(QtMaterialSheetDetentController::BottomSheet),
      currentDetent(QtMaterialSheetDetentController::CollapsedDetent),
      halfExpandedEnabled(true),
      collapsedExtent(72),
      halfExpandedExtent(320),
      expandedExtent(560)
{
}

QtMaterialSheetDetentControllerPrivate::~QtMaterialSheetDetentControllerPrivate()
{
}

int QtMaterialSheetDetentControllerPrivate::currentExtentForDetent(QtMaterialSheetDetentController::Detent detent) const
{
    switch (detent) {
    case QtMaterialSheetDetentController::CollapsedDetent:
        return collapsedExtent;
    case QtMaterialSheetDetentController::HalfExpandedDetent:
        return halfExpandedEnabled ? halfExpandedExtent : expandedExtent;
    case QtMaterialSheetDetentController::ExpandedDetent:
    default:
        return expandedExtent;
    }
}

void QtMaterialSheetDetentControllerPrivate::updateTargetGeometry()
{
    if (!target) {
        return;
    }

    const int extent = currentExtentForDetent(currentDetent);
    QRect r = target->geometry();

    if (orientation == QtMaterialSheetDetentController::BottomSheet) {
        r.setHeight(extent);
    } else {
        r.setWidth(extent);
    }

    target->setGeometry(r);
}

QtMaterialSheetDetentController::QtMaterialSheetDetentController(QObject *parent)
    : QObject(parent),
      d_ptr(new QtMaterialSheetDetentControllerPrivate(this))
{
}

QtMaterialSheetDetentController::~QtMaterialSheetDetentController()
{
}

void QtMaterialSheetDetentController::setTarget(QWidget *target)
{
    Q_D(QtMaterialSheetDetentController);
    d->target = target;
    d->updateTargetGeometry();
}

QWidget *QtMaterialSheetDetentController::target() const
{
    Q_D(const QtMaterialSheetDetentController);
    return d->target;
}

void QtMaterialSheetDetentController::setOrientation(Orientation value)
{
    Q_D(QtMaterialSheetDetentController);
    if (d->orientation == value) {
        return;
    }
    d->orientation = value;
    d->updateTargetGeometry();
}

QtMaterialSheetDetentController::Orientation QtMaterialSheetDetentController::orientation() const
{
    Q_D(const QtMaterialSheetDetentController);
    return d->orientation;
}

void QtMaterialSheetDetentController::setHalfExpandedEnabled(bool value)
{
    Q_D(QtMaterialSheetDetentController);
    d->halfExpandedEnabled = value;
}

bool QtMaterialSheetDetentController::halfExpandedEnabled() const
{
    Q_D(const QtMaterialSheetDetentController);
    return d->halfExpandedEnabled;
}

void QtMaterialSheetDetentController::setCollapsedExtent(int value)
{
    Q_D(QtMaterialSheetDetentController);
    d->collapsedExtent = qMax(0, value);
    d->updateTargetGeometry();
}

int QtMaterialSheetDetentController::collapsedExtent() const
{
    Q_D(const QtMaterialSheetDetentController);
    return d->collapsedExtent;
}

void QtMaterialSheetDetentController::setHalfExpandedExtent(int value)
{
    Q_D(QtMaterialSheetDetentController);
    d->halfExpandedExtent = qMax(d->collapsedExtent, value);
    d->updateTargetGeometry();
}

int QtMaterialSheetDetentController::halfExpandedExtent() const
{
    Q_D(const QtMaterialSheetDetentController);
    return d->halfExpandedExtent;
}

void QtMaterialSheetDetentController::setExpandedExtent(int value)
{
    Q_D(QtMaterialSheetDetentController);
    d->expandedExtent = qMax(d->halfExpandedExtent, value);
    d->updateTargetGeometry();
}

int QtMaterialSheetDetentController::expandedExtent() const
{
    Q_D(const QtMaterialSheetDetentController);
    return d->expandedExtent;
}

void QtMaterialSheetDetentController::setCurrentDetent(Detent value)
{
    Q_D(QtMaterialSheetDetentController);
    if (d->currentDetent == value) {
        return;
    }
    if (!d->halfExpandedEnabled && value == HalfExpandedDetent) {
        value = ExpandedDetent;
    }
    d->currentDetent = value;
    d->updateTargetGeometry();
    emit currentDetentChanged(value);
    emit detentProgressChanged(detentProgress());
}

QtMaterialSheetDetentController::Detent QtMaterialSheetDetentController::currentDetent() const
{
    Q_D(const QtMaterialSheetDetentController);
    return d->currentDetent;
}

qreal QtMaterialSheetDetentController::detentProgress() const
{
    Q_D(const QtMaterialSheetDetentController);
    const int min = d->collapsedExtent;
    const int max = qMax(min + 1, d->expandedExtent);
    const int current = d->currentExtentForDetent(d->currentDetent);
    return qreal(current - min) / qreal(max - min);
}

void QtMaterialSheetDetentController::snapToNearestDetent(int currentExtent)
{
    Q_D(QtMaterialSheetDetentController);

    QList<QPair<Detent, int> > candidates;
    candidates << qMakePair(CollapsedDetent, d->collapsedExtent);
    if (d->halfExpandedEnabled) {
        candidates << qMakePair(HalfExpandedDetent, d->halfExpandedExtent);
    }
    candidates << qMakePair(ExpandedDetent, d->expandedExtent);

    Detent bestDetent = candidates.first().first;
    int bestDelta = qAbs(currentExtent - candidates.first().second);

    for (int i = 1; i < candidates.size(); ++i) {
        const int delta = qAbs(currentExtent - candidates.at(i).second);
        if (delta < bestDelta) {
            bestDelta = delta;
            bestDetent = candidates.at(i).first;
        }
    }

    setCurrentDetent(bestDetent);
}

void QtMaterialSheetDetentController::applyCurrentDetent()
{
    Q_D(QtMaterialSheetDetentController);
    d->updateTargetGeometry();
    emit detentProgressChanged(detentProgress());
}
