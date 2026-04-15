#ifndef QTMATERIALPULLTOREFRESH_H
#define QTMATERIALPULLTOREFRESH_H

#include <QWidget>
#include <QColor>
#include <QScopedPointer>

class QtMaterialPullToRefreshPrivate;

class QtMaterialPullToRefresh : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor indicatorColor WRITE setIndicatorColor READ indicatorColor)
    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
    Q_PROPERTY(int triggerDistance WRITE setTriggerDistance READ triggerDistance)
    Q_PROPERTY(bool refreshing READ isRefreshing)

public:
    explicit QtMaterialPullToRefresh(QWidget *parent = 0);
    ~QtMaterialPullToRefresh();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setIndicatorColor(const QColor &color);
    QColor indicatorColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setLabelText(const QString &text);
    QString labelText() const;

    void setRefreshingText(const QString &text);
    QString refreshingText() const;

    void setTriggerDistance(int value);
    int triggerDistance() const;

    bool isRefreshing() const;

public slots:
    void beginRefresh();
    void endRefresh();

signals:
    void refreshRequested();

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialPullToRefreshPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialPullToRefresh)
    Q_DECLARE_PRIVATE(QtMaterialPullToRefresh)
};

#endif // QTMATERIALPULLTOREFRESH_H
