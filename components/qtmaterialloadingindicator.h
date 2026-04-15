#ifndef QTMATERIALLOADINGINDICATOR_H
#define QTMATERIALLOADINGINDICATOR_H

#include <QWidget>
#include <QColor>
#include <QScopedPointer>

class QtMaterialLoadingIndicatorPrivate;

class QtMaterialLoadingIndicator : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor indicatorColor WRITE setIndicatorColor READ indicatorColor)
    Q_PROPERTY(QColor trackColor WRITE setTrackColor READ trackColor)
    Q_PROPERTY(qreal lineWidth WRITE setLineWidth READ lineWidth)
    Q_PROPERTY(int size WRITE setSize READ size)
    Q_PROPERTY(bool indeterminate WRITE setIndeterminate READ isIndeterminate)
    Q_PROPERTY(bool autoStart WRITE setAutoStart READ autoStart)

public:
    explicit QtMaterialLoadingIndicator(QWidget *parent = 0);
    ~QtMaterialLoadingIndicator();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setIndicatorColor(const QColor &color);
    QColor indicatorColor() const;

    void setTrackColor(const QColor &color);
    QColor trackColor() const;

    void setLineWidth(qreal width);
    qreal lineWidth() const;

    void setSize(int size);
    int size() const;

    void setIndeterminate(bool value);
    bool isIndeterminate() const;

    void setAutoStart(bool value);
    bool autoStart() const;

public slots:
    void start();
    void stop();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void showEvent(QShowEvent *event) Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialLoadingIndicatorPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialLoadingIndicator)
    Q_DECLARE_PRIVATE(QtMaterialLoadingIndicator)
};

#endif // QTMATERIALLOADINGINDICATOR_H
