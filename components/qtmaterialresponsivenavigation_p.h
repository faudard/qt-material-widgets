#ifndef QTMATERIALRESPONSIVENAVIGATION_P_H
#define QTMATERIALRESPONSIVENAVIGATION_P_H

#include <QObject>
#include <QColor>
#include <QStringList>
#include <QVector>
#include <QIcon>

class QStackedLayout;
class QWidget;
class QtMaterialResponsiveNavigation;

class QtMaterialResponsiveNavigationPrivate
{
  Q_DISABLE_COPY(QtMaterialResponsiveNavigationPrivate)
  Q_DECLARE_PUBLIC(QtMaterialResponsiveNavigation)

public:
  QtMaterialResponsiveNavigationPrivate(QtMaterialResponsiveNavigation *q);
  ~QtMaterialResponsiveNavigationPrivate();

  void init();
  void syncSelection(int index);
  void rebuildNavigation();
  void applyMode(int width);

  QtMaterialResponsiveNavigation *const q_ptr;

  bool useThemeColors;
  int compactBreakpoint;
  int mediumBreakpoint;
  QColor backgroundColor;
  int currentIndex;
  int forcedMode;

  QVector<QIcon> icons;
  QStringList texts;

  QStackedLayout *stack;
  QWidget *bottomBar;
  QWidget *rail;
  QWidget *drawer;
};

#endif // QTMATERIALRESPONSIVENAVIGATION_P_H