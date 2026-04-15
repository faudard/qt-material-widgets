#ifndef QTMATERIALBOTTOMAPPBAR_H
#define QTMATERIALBOTTOMAPPBAR_H

#include <QScopedPointer>
#include <QColor>
#include <QHBoxLayout>
#include <QMargins>
#include "qtmaterialappbar.h"

class QtMaterialBottomAppBarPrivate;

class QtMaterialBottomAppBar : public QtMaterialAppBar
{
    Q_OBJECT

    Q_PROPERTY(bool centerFab WRITE setCenterFab READ centerFab)
    Q_PROPERTY(bool showFabCradle WRITE setShowFabCradle READ showFabCradle)
    Q_PROPERTY(int fabDiameter WRITE setFabDiameter READ fabDiameter)
    Q_PROPERTY(QColor cradleColor WRITE setCradleColor READ cradleColor)
    Q_PROPERTY(QMargins contentMargins WRITE setContentMargins READ contentMargins)

public:
    explicit QtMaterialBottomAppBar(QWidget *parent = 0);
    ~QtMaterialBottomAppBar();

    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

    void setCenterFab(bool value);
    bool centerFab() const;

    void setShowFabCradle(bool value);
    bool showFabCradle() const;

    void setFabDiameter(int value);
    int fabDiameter() const;

    void setCradleColor(const QColor &color);
    QColor cradleColor() const;

    void setContentMargins(const QMargins &margins);
    QMargins contentMargins() const;

    inline QHBoxLayout *bottomAppBarLayout() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialBottomAppBarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialBottomAppBar)
    Q_DECLARE_PRIVATE(QtMaterialBottomAppBar)
};

inline QHBoxLayout *QtMaterialBottomAppBar::bottomAppBarLayout() const
{
    return static_cast<QHBoxLayout *>(layout());
}

#endif // QTMATERIALBOTTOMAPPBAR_H
