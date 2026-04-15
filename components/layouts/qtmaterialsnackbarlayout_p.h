#ifndef QTMATERIALSNACKBARLAYOUT_P_H
#define QTMATERIALSNACKBARLAYOUT_P_H

#include <QList>
#include <QRect>

class QLayoutItem;
class QtMaterialSnackbarLayout;

class QtMaterialSnackbarLayoutPrivate
{
    Q_DISABLE_COPY(QtMaterialSnackbarLayoutPrivate)
    Q_DECLARE_PUBLIC(QtMaterialSnackbarLayout)

public:
    explicit QtMaterialSnackbarLayoutPrivate(QtMaterialSnackbarLayout *q);
    ~QtMaterialSnackbarLayoutPrivate();

    int doLayout(const QRect &rect, bool testOnly) const;
    QSize calculatedSize() const;

    QtMaterialSnackbarLayout *const q_ptr;
    QList<QLayoutItem *> items;
    bool dense;
    int messageSpacing;
    int singleLineHeight;
    int multiLineHeight;
};

#endif // QTMATERIALSNACKBARLAYOUT_P_H
