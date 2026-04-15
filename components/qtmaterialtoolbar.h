#ifndef QTMATERIALTOOLBAR_H
#define QTMATERIALTOOLBAR_H

#include "qtmaterialappbar.h"

class QtMaterialToolBarPrivate;
class QLabel;
class QHBoxLayout;

class QtMaterialToolBar : public QtMaterialAppBar
{
    Q_OBJECT

    Q_PROPERTY(QString title WRITE setTitle READ title)
    Q_PROPERTY(QString subtitle WRITE setSubtitle READ subtitle)
    Q_PROPERTY(bool dense WRITE setDense READ isDense)
    Q_PROPERTY(bool centeredTitle WRITE setCenteredTitle READ centeredTitle)

public:
    explicit QtMaterialToolBar(QWidget *parent = 0);
    ~QtMaterialToolBar();

    QSize sizeHint() const Q_DECL_OVERRIDE;

    void setTitle(const QString &title);
    QString title() const;

    void setSubtitle(const QString &subtitle);
    QString subtitle() const;

    void setDense(bool value);
    bool isDense() const;

    void setCenteredTitle(bool value);
    bool centeredTitle() const;

    QHBoxLayout *leadingLayout() const;
    QHBoxLayout *actionsLayout() const;

private:
    Q_DISABLE_COPY(QtMaterialToolBar)
    Q_DECLARE_PRIVATE(QtMaterialToolBar)
};

#endif // QTMATERIALTOOLBAR_H