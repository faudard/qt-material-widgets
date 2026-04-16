#ifndef QTMATERIALMEDIUMTOPAPPBAR_P_H
#define QTMATERIALMEDIUMTOPAPPBAR_P_H
#include <QtGlobal>
#include <QColor>
#include <QString>
class QtMaterialMediumTopAppBar;
class QtMaterialMediumTopAppBarPrivate { Q_DISABLE_COPY(QtMaterialMediumTopAppBarPrivate) Q_DECLARE_PUBLIC(QtMaterialMediumTopAppBar)
public: explicit QtMaterialMediumTopAppBarPrivate(QtMaterialMediumTopAppBar *q); ~QtMaterialMediumTopAppBarPrivate(); void init(); QtMaterialMediumTopAppBar *const q_ptr; bool useThemeColors; QColor foregroundColor; QColor backgroundColor; QString title; QString subtitle; };
#endif
