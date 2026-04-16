#ifndef QTMATERIALSMALLTOPAPPBAR_P_H
#define QTMATERIALSMALLTOPAPPBAR_P_H
#include <QtGlobal>
#include <QColor>
class QtMaterialSmallTopAppBar;
class QtMaterialSmallTopAppBarPrivate {
    Q_DISABLE_COPY(QtMaterialSmallTopAppBarPrivate)
    Q_DECLARE_PUBLIC(QtMaterialSmallTopAppBar)
public:
    explicit QtMaterialSmallTopAppBarPrivate(QtMaterialSmallTopAppBar *q); ~QtMaterialSmallTopAppBarPrivate(); void init();
    QtMaterialSmallTopAppBar *const q_ptr; bool useThemeColors; QColor foregroundColor; QColor backgroundColor; bool showDivider;
};
#endif
