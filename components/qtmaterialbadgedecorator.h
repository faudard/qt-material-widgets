#ifndef QTMATERIALBADGEDECORATOR_H
#define QTMATERIALBADGEDECORATOR_H

#include <QObject>
#include <QPointer>
#include <QColor>

class QWidget;
class QtMaterialBadge;
class QtMaterialBadgeDecoratorPrivate;

class QtMaterialBadgeDecorator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QPoint offset READ offset WRITE setOffset)
    Q_PROPERTY(bool autoHideWhenZero READ autoHideWhenZero WRITE setAutoHideWhenZero)

public:
    explicit QtMaterialBadgeDecorator(QObject *parent = 0);
    explicit QtMaterialBadgeDecorator(QWidget *target, QObject *parent = 0);
    ~QtMaterialBadgeDecorator();

    void setTarget(QWidget *target);
    QWidget *target() const;

    void setBadge(QtMaterialBadge *badge);
    QtMaterialBadge *badge() const;

    void setText(const QString &text);
    QString text() const;

    void setCount(int value);
    int count() const;

    void setCountMode(bool value);
    bool countMode() const;

    void setOffset(const QPoint &offset);
    QPoint offset() const;

    void setAutoHideWhenZero(bool value);
    bool autoHideWhenZero() const;

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
    void updateBadgeGeometry();

    Q_DISABLE_COPY(QtMaterialBadgeDecorator)
    QtMaterialBadgeDecoratorPrivate *const d_ptr;
};

#endif // QTMATERIALBADGEDECORATOR_H
