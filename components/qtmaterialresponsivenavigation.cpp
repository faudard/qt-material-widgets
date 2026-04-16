#include "qtmaterialresponsivenavigation.h"
#include "qtmaterialresponsivenavigation_p.h"

#include <QResizeEvent>
#include <QStackedLayout>
#include <QWidget>

QtMaterialResponsiveNavigationPrivate::QtMaterialResponsiveNavigationPrivate(QtMaterialResponsiveNavigation *q)
    : q_ptr(q)
      , useThemeColors(true)
      , compactBreakpoint(600)
      , mediumBreakpoint(1024)
      , currentIndex(0)
      , forcedMode(-1)
      , stack(0)
      , bottomBar(0)
      , rail(0)
      , drawer(0)
{
}

QtMaterialResponsiveNavigationPrivate::~QtMaterialResponsiveNavigationPrivate()
{
}

void QtMaterialResponsiveNavigationPrivate::init()
{
  Q_Q(QtMaterialResponsiveNavigation);

  stack = new QStackedLayout;
  stack->setContentsMargins(0, 0, 0, 0);
  q->setLayout(stack);

  // Placeholder widgets until real components exist.
  bottomBar = new QWidget(q);
  rail      = new QWidget(q);
  drawer    = new QWidget(q);

  stack->addWidget(bottomBar);
  stack->addWidget(rail);
  stack->addWidget(drawer);

  applyMode(q->width());
}

void QtMaterialResponsiveNavigationPrivate::syncSelection(int index)
{
  Q_UNUSED(index)
  // Placeholder: forward selected item when real components exist.
}

void QtMaterialResponsiveNavigationPrivate::rebuildNavigation()
{
  // Placeholder: populate bottom bar / rail / drawer when real components exist.
}

void QtMaterialResponsiveNavigationPrivate::applyMode(int width)
{
  Q_Q(QtMaterialResponsiveNavigation);

  QtMaterialResponsiveNavigation::NavigationMode mode = QtMaterialResponsiveNavigation::BottomBarMode;

  if (forcedMode >= 0) {
    mode = static_cast<QtMaterialResponsiveNavigation::NavigationMode>(forcedMode);
  } else if (width < compactBreakpoint) {
    mode = QtMaterialResponsiveNavigation::BottomBarMode;
  } else if (width < mediumBreakpoint) {
    mode = QtMaterialResponsiveNavigation::RailMode;
  } else {
    mode = QtMaterialResponsiveNavigation::DrawerMode;
  }

  if (stack) {
    stack->setCurrentIndex(static_cast<int>(mode));
  }
  emit q->modeChanged(mode);
}

QtMaterialResponsiveNavigation::QtMaterialResponsiveNavigation(QWidget *parent)
    : QWidget(parent)
      , d_ptr(new QtMaterialResponsiveNavigationPrivate(this))
{
  Q_D(QtMaterialResponsiveNavigation);
  d->init();
}

QtMaterialResponsiveNavigation::~QtMaterialResponsiveNavigation()
{
}

void QtMaterialResponsiveNavigation::setUseThemeColors(bool value)
{
  Q_D(QtMaterialResponsiveNavigation);
  d->useThemeColors = value;
  update();
}

bool QtMaterialResponsiveNavigation::useThemeColors() const
{
  Q_D(const QtMaterialResponsiveNavigation);
  return d->useThemeColors;
}

void QtMaterialResponsiveNavigation::setCompactBreakpoint(int value)
{
  Q_D(QtMaterialResponsiveNavigation);
  d->compactBreakpoint = value;
  d->applyMode(width());
}

int QtMaterialResponsiveNavigation::compactBreakpoint() const
{
  Q_D(const QtMaterialResponsiveNavigation);
  return d->compactBreakpoint;
}

void QtMaterialResponsiveNavigation::setMediumBreakpoint(int value)
{
  Q_D(QtMaterialResponsiveNavigation);
  d->mediumBreakpoint = value;
  d->applyMode(width());
}

int QtMaterialResponsiveNavigation::mediumBreakpoint() const
{
  Q_D(const QtMaterialResponsiveNavigation);
  return d->mediumBreakpoint;
}

void QtMaterialResponsiveNavigation::setBackgroundColor(const QColor &color)
{
  Q_D(QtMaterialResponsiveNavigation);
  d->backgroundColor = color;
  update();
}

QColor QtMaterialResponsiveNavigation::backgroundColor() const
{
  Q_D(const QtMaterialResponsiveNavigation);
  return d->backgroundColor;
}

void QtMaterialResponsiveNavigation::addItem(const QIcon &icon, const QString &text)
{
  Q_D(QtMaterialResponsiveNavigation);
  d->icons.push_back(icon);
  d->texts.push_back(text);
  d->rebuildNavigation();
}

int QtMaterialResponsiveNavigation::currentIndex() const
{
  Q_D(const QtMaterialResponsiveNavigation);
  return d->currentIndex;
}

void QtMaterialResponsiveNavigation::setCurrentIndex(int index)
{
  Q_D(QtMaterialResponsiveNavigation);

  if (d->currentIndex == index) {
    return;
  }

  d->currentIndex = index;
  d->syncSelection(index);
  emit currentChanged(index);
}

QtMaterialResponsiveNavigation::NavigationMode QtMaterialResponsiveNavigation::navigationMode() const
{
  Q_D(const QtMaterialResponsiveNavigation);
  const int current = d->forcedMode >= 0 ? d->forcedMode
                                         : (d->stack ? d->stack->currentIndex() : 0);
  return static_cast<NavigationMode>(current);
}

void QtMaterialResponsiveNavigation::setNavigationMode(QtMaterialResponsiveNavigation::NavigationMode mode)
{
  Q_D(QtMaterialResponsiveNavigation);
  d->forcedMode = static_cast<int>(mode);
  d->applyMode(width());
}

void QtMaterialResponsiveNavigation::updateForAvailableWidth(int width)
{
  Q_D(QtMaterialResponsiveNavigation);
  d->forcedMode = -1;
  d->applyMode(width);
}

void QtMaterialResponsiveNavigation::resizeEvent(QResizeEvent *event)
{
  QWidget::resizeEvent(event);

  Q_D(QtMaterialResponsiveNavigation);
  if (d->forcedMode < 0) {
    d->applyMode(event->size().width());
  }
}