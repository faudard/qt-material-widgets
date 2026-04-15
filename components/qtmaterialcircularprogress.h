#ifndef QTMATERIALCIRCULARPROGRESS_H
#define QTMATERIALCIRCULARPROGRESS_H

#include <QProgressBar>
#include <QScopedPointer>
#include "lib/qtmaterialtheme.h"

class QtMaterialCircularProgressPrivate;

class QtMaterialCircularProgress : public QProgressBar
{
    Q_OBJECT

    Q_PROPERTY(qreal lineWidth WRITE setLineWidth READ lineWidth)
    Q_PROPERTY(qreal size WRITE setSize READ size)
    Q_PROPERTY(QColor color WRITE setColor READ color)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(bool showPercentage WRITE setShowPercentage READ showPercentage)
    Q_PROPERTY(bool roundedCaps WRITE setRoundedCaps READ hasRoundedCaps)

public:
    explicit QtMaterialCircularProgress(QWidget *parent = 0);
    ~QtMaterialCircularProgress();

    void setProgressType(Material::ProgressType type);
    Material::ProgressType progressType() const;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setLineWidth(qreal width);
    qreal lineWidth() const;

    void setSize(int size);
    int size() const;

    void setColor(const QColor &color);
    QColor color() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setShowPercentage(bool value);
    bool showPercentage() const;

    void setRoundedCaps(bool value);
    bool hasRoundedCaps() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialCircularProgressPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialCircularProgress)
    Q_DECLARE_PRIVATE(QtMaterialCircularProgress)
};

#endif // QTMATERIALCIRCULARPROGRESS_H
