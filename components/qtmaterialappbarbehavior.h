#ifndef QTMATERIALAPPBARBEHAVIOR_H
#define QTMATERIALAPPBARBEHAVIOR_H

#include <QObject>

class QtMaterialTopAppBarScrollController;

class QtMaterialAppBarBehavior : public QObject
{
    Q_OBJECT

    Q_PROPERTY(BehaviorMode behaviorMode READ behaviorMode WRITE setBehaviorMode)
    Q_PROPERTY(int revealThreshold READ revealThreshold WRITE setRevealThreshold)
    Q_PROPERTY(bool snap READ snap WRITE setSnap)

public:
    enum BehaviorMode {
        PinnedBehavior,
        EnterAlwaysBehavior
    };
    Q_ENUM(BehaviorMode)

    explicit QtMaterialAppBarBehavior(QObject *parent = 0);
    ~QtMaterialAppBarBehavior();

    void setController(QtMaterialTopAppBarScrollController *controller);
    QtMaterialTopAppBarScrollController *controller() const;

    void setBehaviorMode(BehaviorMode mode);
    BehaviorMode behaviorMode() const;

    void setRevealThreshold(int value);
    int revealThreshold() const;

    void setSnap(bool value);
    bool snap() const;

public slots:
    void onScrollValueChanged(int value);
    void reset();

signals:
    void behaviorModeChanged(BehaviorMode mode);
    void hiddenOffsetChanged(int value);

private:
    class Private;
    Private *d;
};

#endif // QTMATERIALAPPBARBEHAVIOR_H
