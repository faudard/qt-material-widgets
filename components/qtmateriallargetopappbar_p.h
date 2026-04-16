#ifndef QTMATERIALLARGETOPAPPBAR_P_H
#define QTMATERIALLARGETOPAPPBAR_P_H
#include <QtGlobal>
#include <QColor>
#include <QString>
class QtMaterialLargeTopAppBar;
class QtMaterialLargeTopAppBarPrivate { Q_DISABLE_COPY(QtMaterialLargeTopAppBarPrivate) Q_DECLARE_PUBLIC(QtMaterialLargeTopAppBar)
public: explicit QtMaterialLargeTopAppBarPrivate(QtMaterialLargeTopAppBar *q); ~QtMaterialLargeTopAppBarPrivate(); void init(); QtMaterialLargeTopAppBar *const q_ptr; bool useThemeColors; QColor foregroundColor; QColor backgroundColor; QString title; QString subtitle; };
#endif
