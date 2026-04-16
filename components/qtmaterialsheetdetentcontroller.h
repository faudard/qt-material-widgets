#ifndef QTMATERIALSHEETDETENTCONTROLLER_H
#define QTMATERIALSHEETDETENTCONTROLLER_H

#include <QObject>
#include <QScopedPointer>

class QWidget;
class QtMaterialSheetDetentControllerPrivate;

class QtMaterialSheetDetentController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Orientation orientation READ orientation WRITE setOrientation)
    Q_PROPERTY(bool halfExpandedEnabled READ halfExpandedEnabled WRITE setHalfExpandedEnabled)
    Q_PROPERTY(int collapsedExtent READ collapsedExtent WRITE setCollapsedExtent)
    Q_PROPERTY(int halfExpandedExtent READ halfExpandedExtent WRITE setHalfExpandedExtent)
    Q_PROPERTY(int expandedExtent READ expandedExtent WRITE setExpandedExtent)
    Q_PROPERTY(Detent currentDetent READ currentDetent WRITE setCurrentDetent NOTIFY currentDetentChanged)
    Q_PROPERTY(qreal detentProgress READ detentProgress NOTIFY detentProgressChanged)

public:
    enum Orientation {
        BottomSheet,
        SideSheet
    };
    Q_ENUM(Orientation)

    enum Detent {
        CollapsedDetent,
        HalfExpandedDetent,
        ExpandedDetent
    };
    Q_ENUM(Detent)

    explicit QtMaterialSheetDetentController(QObject *parent = 0);
    ~QtMaterialSheetDetentController();

    void setTarget(QWidget *target);
    QWidget *target() const;

    void setOrientation(Orientation value);
    Orientation orientation() const;

    void setHalfExpandedEnabled(bool value);
    bool halfExpandedEnabled() const;

    void setCollapsedExtent(int value);
    int collapsedExtent() const;

    void setHalfExpandedExtent(int value);
    int halfExpandedExtent() const;

    void setExpandedExtent(int value);
    int expandedExtent() const;

    void setCurrentDetent(Detent value);
    Detent currentDetent() const;

    qreal detentProgress() const;

public slots:
    void snapToNearestDetent(int currentExtent);
    void applyCurrentDetent();

signals:
    void currentDetentChanged(Detent value);
    void detentProgressChanged(qreal value);

protected:
    const QScopedPointer<QtMaterialSheetDetentControllerPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialSheetDetentController)
    Q_DECLARE_PRIVATE(QtMaterialSheetDetentController)
};

#endif // QTMATERIALSHEETDETENTCONTROLLER_H
