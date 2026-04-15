#include "qtmaterialbottomappbar.h"
#include "qtmaterialbottomappbar_p.h"

#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>

QtMaterialBottomAppBarPrivate::QtMaterialBottomAppBarPrivate(QtMaterialBottomAppBar *q)
    : q_ptr(q),
      centerFab(true),
      showFabCradle(true),
      fabDiameter(56),
      cradleColor(),
      contentMargins(16, 8, 16, 8)
{
}

void QtMaterialBottomAppBarPrivate::init()
{
    Q_Q(QtMaterialBottomAppBar);

    q->setUseThemeColors(true);
    q->setBackgroundColor(QColor());
    q->setForegroundColor(QColor());

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(contentMargins);
    layout->setSpacing(8);

    q->setLayout(layout);
    q->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
}

QtMaterialBottomAppBar::QtMaterialBottomAppBar(QWidget *parent)
    : QtMaterialAppBar(parent),
      d_ptr(new QtMaterialBottomAppBarPrivate(this))
{
    Q_D(QtMaterialBottomAppBar);
    d->init();
}

QtMaterialBottomAppBar::~QtMaterialBottomAppBar()
{
}

QSize QtMaterialBottomAppBar::sizeHint() const
{
    return QSize(320, 64);
}

QSize QtMaterialBottomAppBar::minimumSizeHint() const
{
    return QSize(160, 56);
}

void QtMaterialBottomAppBar::setCenterFab(bool value)
{
    Q_D(QtMaterialBottomAppBar);

    if (d->centerFab == value) {
        return;
    }

    d->centerFab = value;
    update();
}

bool QtMaterialBottomAppBar::centerFab() const
{
    Q_D(const QtMaterialBottomAppBar);
    return d->centerFab;
}

void QtMaterialBottomAppBar::setShowFabCradle(bool value)
{
    Q_D(QtMaterialBottomAppBar);

    if (d->showFabCradle == value) {
        return;
    }

    d->showFabCradle = value;
    update();
}

bool QtMaterialBottomAppBar::showFabCradle() const
{
    Q_D(const QtMaterialBottomAppBar);
    return d->showFabCradle;
}

void QtMaterialBottomAppBar::setFabDiameter(int value)
{
    Q_D(QtMaterialBottomAppBar);

    value = qMax(40, value);

    if (d->fabDiameter == value) {
        return;
    }

    d->fabDiameter = value;
    update();
}

int QtMaterialBottomAppBar::fabDiameter() const
{
    Q_D(const QtMaterialBottomAppBar);
    return d->fabDiameter;
}

void QtMaterialBottomAppBar::setCradleColor(const QColor &color)
{
    Q_D(QtMaterialBottomAppBar);

    if (d->cradleColor == color) {
        return;
    }

    d->cradleColor = color;
    update();
}

QColor QtMaterialBottomAppBar::cradleColor() const
{
    Q_D(const QtMaterialBottomAppBar);

    if (useThemeColors() || !d->cradleColor.isValid()) {
        return backgroundColor().isValid() ? backgroundColor() : palette().window().color();
    }

    return d->cradleColor;
}

void QtMaterialBottomAppBar::setContentMargins(const QMargins &margins)
{
    Q_D(QtMaterialBottomAppBar);

    if (d->contentMargins == margins) {
        return;
    }

    d->contentMargins = margins;

    if (QHBoxLayout *layout = bottomAppBarLayout()) {
        layout->setContentsMargins(margins);
    }

    updateGeometry();
    update();
}

QMargins QtMaterialBottomAppBar::contentMargins() const
{
    Q_D(const QtMaterialBottomAppBar);
    return d->contentMargins;
}

void QtMaterialBottomAppBar::paintEvent(QPaintEvent *event)
{
    QtMaterialAppBar::paintEvent(event);

    Q_D(QtMaterialBottomAppBar);

    if (!d->showFabCradle) {
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const int diameter = d->fabDiameter;
    const int radius = diameter / 2;
    const int notchDepth = 12;
    const int centerX = d->centerFab ? width() / 2 : width() - d->contentMargins.right() - radius - 16;
    const QRect notchRect(centerX - radius - 6, -radius + notchDepth, diameter + 12, diameter + 12);

    QPainterPath path;
    path.addEllipse(notchRect);

    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillPath(path, cradleColor());

    Q_UNUSED(event)
}
