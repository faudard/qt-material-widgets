#include "qtmaterialappbarbehavior.h"
#include "qtmaterialtopappbarscrollcontroller.h"

class QtMaterialAppBarBehavior::Private
{
public:
    Private()
        : controller(0),
          mode(QtMaterialAppBarBehavior::PinnedBehavior),
          revealThreshold(24),
          snap(false),
          lastValue(0),
          accumulatedDelta(0),
          hiddenOffset(0) {}

    QtMaterialTopAppBarScrollController *controller;
    QtMaterialAppBarBehavior::BehaviorMode mode;
    int revealThreshold;
    bool snap;
    int lastValue;
    int accumulatedDelta;
    int hiddenOffset;
};

QtMaterialAppBarBehavior::QtMaterialAppBarBehavior(QObject *parent)
    : QObject(parent),
      d(new Private)
{
}

QtMaterialAppBarBehavior::~QtMaterialAppBarBehavior()
{
    delete d;
}

void QtMaterialAppBarBehavior::setController(QtMaterialTopAppBarScrollController *controller)
{
    d->controller = controller;
}

QtMaterialTopAppBarScrollController *QtMaterialAppBarBehavior::controller() const
{
    return d->controller;
}

void QtMaterialAppBarBehavior::setBehaviorMode(BehaviorMode mode)
{
    if (d->mode == mode) {
        return;
    }

    d->mode = mode;
    emit behaviorModeChanged(mode);
    reset();
}

QtMaterialAppBarBehavior::BehaviorMode QtMaterialAppBarBehavior::behaviorMode() const
{
    return d->mode;
}

void QtMaterialAppBarBehavior::setRevealThreshold(int value)
{
    d->revealThreshold = value < 0 ? 0 : value;
}

int QtMaterialAppBarBehavior::revealThreshold() const
{
    return d->revealThreshold;
}

void QtMaterialAppBarBehavior::setSnap(bool value)
{
    d->snap = value;
}

bool QtMaterialAppBarBehavior::snap() const
{
    return d->snap;
}

void QtMaterialAppBarBehavior::onScrollValueChanged(int value)
{
    if (!d->controller) {
        d->lastValue = value;
        return;
    }

    const int delta = value - d->lastValue;
    d->lastValue = value;

    if (d->mode == PinnedBehavior) {
        d->controller->setCollapsedHeight(d->controller->collapsedHeight());
        d->hiddenOffset = 0;
        emit hiddenOffsetChanged(0);
        return;
    }

    d->accumulatedDelta += delta;
    if (d->accumulatedDelta > d->revealThreshold) {
        d->hiddenOffset = d->controller->collapsedHeight();
        d->accumulatedDelta = 0;
    } else if (d->accumulatedDelta < -d->revealThreshold) {
        d->hiddenOffset = 0;
        d->accumulatedDelta = 0;
    }

    emit hiddenOffsetChanged(d->hiddenOffset);
}

void QtMaterialAppBarBehavior::reset()
{
    d->accumulatedDelta = 0;
    d->hiddenOffset = 0;
    d->lastValue = 0;
    emit hiddenOffsetChanged(0);
}
