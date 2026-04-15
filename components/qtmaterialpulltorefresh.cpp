#include "qtmaterialpulltorefresh.h"
#include "qtmaterialpulltorefresh_p.h"
#include "qtmaterialloadingindicator.h"

#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollBar>

QtMaterialPullToRefreshPrivate::QtMaterialPullToRefreshPrivate(QtMaterialPullToRefresh *q)
    : q_ptr(q),
      target(0),
      indicator(0),
      useThemeColors(true),
      refreshing(false),
      tracking(false),
      triggerDistance(72),
      currentOffset(0)
{
}

void QtMaterialPullToRefreshPrivate::init()
{
    Q_Q(QtMaterialPullToRefresh);

    target = q->parentWidget();
    if (target) {
        target->installEventFilter(q);
    }

    indicator = new QtMaterialLoadingIndicator(q);
    indicator->setAutoStart(false);
    indicator->hide();

    labelText = QStringLiteral("Pull to refresh");
    refreshingText = QStringLiteral("Refreshing...");

    q->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    q->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

QtMaterialPullToRefresh::QtMaterialPullToRefresh(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialPullToRefreshPrivate(this))
{
    d_func()->init();
}

QtMaterialPullToRefresh::~QtMaterialPullToRefresh()
{
}

void QtMaterialPullToRefresh::setUseThemeColors(bool value)
{
    Q_D(QtMaterialPullToRefresh);
    d->useThemeColors = value;
    update();
}

bool QtMaterialPullToRefresh::useThemeColors() const
{
    Q_D(const QtMaterialPullToRefresh);
    return d->useThemeColors;
}

void QtMaterialPullToRefresh::setIndicatorColor(const QColor &color)
{
    Q_D(QtMaterialPullToRefresh);
    d->indicatorColor = color;
    d->useThemeColors = false;
    d->indicator->setIndicatorColor(color);
    update();
}

QColor QtMaterialPullToRefresh::indicatorColor() const
{
    Q_D(const QtMaterialPullToRefresh);
    return d->useThemeColors ? palette().highlight().color() : d->indicatorColor;
}

void QtMaterialPullToRefresh::setTextColor(const QColor &color)
{
    Q_D(QtMaterialPullToRefresh);
    d->textColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialPullToRefresh::textColor() const
{
    Q_D(const QtMaterialPullToRefresh);
    return d->useThemeColors ? palette().windowText().color() : d->textColor;
}

void QtMaterialPullToRefresh::setLabelText(const QString &text)
{
    Q_D(QtMaterialPullToRefresh);
    d->labelText = text;
    update();
}

QString QtMaterialPullToRefresh::labelText() const
{
    Q_D(const QtMaterialPullToRefresh);
    return d->labelText;
}

void QtMaterialPullToRefresh::setRefreshingText(const QString &text)
{
    Q_D(QtMaterialPullToRefresh);
    d->refreshingText = text;
    update();
}

QString QtMaterialPullToRefresh::refreshingText() const
{
    Q_D(const QtMaterialPullToRefresh);
    return d->refreshingText;
}

void QtMaterialPullToRefresh::setTriggerDistance(int value)
{
    Q_D(QtMaterialPullToRefresh);
    d->triggerDistance = value;
    updateGeometry();
}

int QtMaterialPullToRefresh::triggerDistance() const
{
    Q_D(const QtMaterialPullToRefresh);
    return d->triggerDistance;
}

bool QtMaterialPullToRefresh::isRefreshing() const
{
    Q_D(const QtMaterialPullToRefresh);
    return d->refreshing;
}

void QtMaterialPullToRefresh::beginRefresh()
{
    Q_D(QtMaterialPullToRefresh);
    d->refreshing = true;
    d->currentOffset = d->triggerDistance;
    d->indicator->show();
    d->indicator->start();
    update();
}

void QtMaterialPullToRefresh::endRefresh()
{
    Q_D(QtMaterialPullToRefresh);
    d->refreshing = false;
    d->currentOffset = 0;
    d->tracking = false;
    d->indicator->stop();
    d->indicator->hide();
    update();
}

bool QtMaterialPullToRefresh::eventFilter(QObject *watched, QEvent *event)
{
    Q_D(QtMaterialPullToRefresh);

    if (watched != d->target || d->refreshing) {
        return QWidget::eventFilter(watched, event);
    }

    switch (event->type()) {
    case QEvent::MouseButtonPress: {
        QMouseEvent *e = static_cast<QMouseEvent *>(event);
        d->pressPos = e->pos();
        d->tracking = true;
        break;
    }
    case QEvent::MouseMove: {
        if (!d->tracking) {
            break;
        }
        QMouseEvent *e = static_cast<QMouseEvent *>(event);
        const int dy = qMax(0, e->pos().y() - d->pressPos.y());
        d->currentOffset = qMin(dy / 2, d->triggerDistance + 32);
        if (d->currentOffset > 0) {
            d->indicator->show();
            d->indicator->move(width()/2 - d->indicator->width()/2, qMax(4, d->currentOffset/2 - d->indicator->height()/2));
        }
        update();
        break;
    }
    case QEvent::MouseButtonRelease: {
        if (d->tracking && d->currentOffset >= d->triggerDistance) {
            beginRefresh();
            emit refreshRequested();
        } else {
            d->currentOffset = 0;
            d->indicator->hide();
            update();
        }
        d->tracking = false;
        break;
    }
    default:
        break;
    }

    return QWidget::eventFilter(watched, event);
}

void QtMaterialPullToRefresh::paintEvent(QPaintEvent *)
{
    Q_D(QtMaterialPullToRefresh);

    if (d->currentOffset <= 0 && !d->refreshing) {
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), palette().window().color());

    painter.setPen(textColor());
    const QString text = d->refreshing ? d->refreshingText : d->labelText;
    painter.drawText(rect().adjusted(0, d->triggerDistance/2, 0, 0), Qt::AlignHCenter | Qt::AlignTop, text);
}

QSize QtMaterialPullToRefresh::sizeHint() const
{
    Q_D(const QtMaterialPullToRefresh);
    return QSize(200, d->triggerDistance + 24);
}
