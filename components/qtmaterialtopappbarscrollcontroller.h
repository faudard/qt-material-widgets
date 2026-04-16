#ifndef QTMATERIALTOPAPPBARSCROLLCONTROLLER_H
#define QTMATERIALTOPAPPBARSCROLLCONTROLLER_H

#include <QObject>
#include <QScopedPointer>
#include <QColor>

class QAbstractScrollArea;
class QtMaterialTopAppBarScrollControllerPrivate;

class QtMaterialTopAppBarScrollController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal collapseProgress READ collapseProgress NOTIFY collapseProgressChanged)
    Q_PROPERTY(int expandedHeight READ expandedHeight WRITE setExpandedHeight)
    Q_PROPERTY(int collapsedHeight READ collapsedHeight WRITE setCollapsedHeight)
    Q_PROPERTY(bool colorShiftEnabled READ colorShiftEnabled WRITE setColorShiftEnabled)

public:
    explicit QtMaterialTopAppBarScrollController(QObject *parent = 0);
    ~QtMaterialTopAppBarScrollController();

    void setScrollArea(QAbstractScrollArea *area);
    QAbstractScrollArea *scrollArea() const;

    void setTarget(QWidget *target);
    QWidget *target() const;

    void setExpandedHeight(int value);
    int expandedHeight() const;

    void setCollapsedHeight(int value);
    int collapsedHeight() const;

    void setColorShiftEnabled(bool value);
    bool colorShiftEnabled() const;

    qreal collapseProgress() const;

signals:
    void collapseProgressChanged(qreal value);

public slots:
    void updateFromScrollPosition(int value);

protected:
    const QScopedPointer<QtMaterialTopAppBarScrollControllerPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialTopAppBarScrollController)
    Q_DECLARE_PRIVATE(QtMaterialTopAppBarScrollController)
};

#endif // QTMATERIALTOPAPPBARSCROLLCONTROLLER_H
