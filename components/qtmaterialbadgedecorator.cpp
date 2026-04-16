#include "qtmaterialbadgedecorator.h"
#include "qtmaterialbadgedecorator_p.h"
#include "qtmaterialbadge.h"

#include <QWidget>
#include <QEvent>

QtMaterialBadgeDecoratorPrivate::QtMaterialBadgeDecoratorPrivate()
    : offset(-4, 4),
      autoHideWhenZero(true)
{
}

QtMaterialBadgeDecorator::QtMaterialBadgeDecorator(QObject *parent)
    : QObject(parent),
      d_ptr(new QtMaterialBadgeDecoratorPrivate)
{
}

QtMaterialBadgeDecorator::QtMaterialBadgeDecorator(QWidget *target, QObject *parent)
    : QObject(parent),
      d_ptr(new QtMaterialBadgeDecoratorPrivate)
{
    setTarget(target);
}

QtMaterialBadgeDecorator::~QtMaterialBadgeDecorator()
{
    delete d_ptr;
}

void QtMaterialBadgeDecorator::setTarget(QWidget *target)
{
    if (d_ptr->target) {
        d_ptr->target->removeEventFilter(this);
    }
    d_ptr->target = target;
    if (target) {
        target->installEventFilter(this);
        if (!d_ptr->badge) {
            d_ptr->badge = new QtMaterialBadge(target);
            d_ptr->badge->show();
        } else {
            d_ptr->badge->setParent(target);
        }
        updateBadgeGeometry();
    }
}

QWidget *QtMaterialBadgeDecorator::target() const { return d_ptr->target; }

void QtMaterialBadgeDecorator::setBadge(QtMaterialBadge *badge)
{
    d_ptr->badge = badge;
    if (d_ptr->badge && d_ptr->target) {
        d_ptr->badge->setParent(d_ptr->target);
        updateBadgeGeometry();
    }
}

QtMaterialBadge *QtMaterialBadgeDecorator::badge() const { return d_ptr->badge; }

void QtMaterialBadgeDecorator::setText(const QString &text) { if (d_ptr->badge) d_ptr->badge->setText(text); }
QString QtMaterialBadgeDecorator::text() const { return d_ptr->badge ? d_ptr->badge->text() : QString(); }

void QtMaterialBadgeDecorator::setCount(int value)
{
    if (d_ptr->badge) {
        d_ptr->badge->setCount(value);
        if (d_ptr->autoHideWhenZero && value == 0)
            d_ptr->badge->hide();
        else
            d_ptr->badge->show();
        updateBadgeGeometry();
    }
}

int QtMaterialBadgeDecorator::count() const { return d_ptr->badge ? d_ptr->badge->count() : 0; }

void QtMaterialBadgeDecorator::setCountMode(bool value) { if (d_ptr->badge) d_ptr->badge->setCountMode(value); }
bool QtMaterialBadgeDecorator::countMode() const { return d_ptr->badge ? d_ptr->badge->countMode() : false; }

void QtMaterialBadgeDecorator::setOffset(const QPoint &offset) { d_ptr->offset = offset; updateBadgeGeometry(); }
QPoint QtMaterialBadgeDecorator::offset() const { return d_ptr->offset; }

void QtMaterialBadgeDecorator::setAutoHideWhenZero(bool value) { d_ptr->autoHideWhenZero = value; }
bool QtMaterialBadgeDecorator::autoHideWhenZero() const { return d_ptr->autoHideWhenZero; }

bool QtMaterialBadgeDecorator::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == d_ptr->target && (event->type() == QEvent::Resize || event->type() == QEvent::Show)) {
        updateBadgeGeometry();
    }
    return QObject::eventFilter(watched, event);
}

void QtMaterialBadgeDecorator::updateBadgeGeometry()
{
    if (!d_ptr->target || !d_ptr->badge)
        return;
    QSize sz = d_ptr->badge->sizeHint();
    int x = d_ptr->target->width() - sz.width() + d_ptr->offset.x();
    int y = d_ptr->offset.y();
    d_ptr->badge->setGeometry(x, y, sz.width(), sz.height());
    d_ptr->badge->raise();
}
