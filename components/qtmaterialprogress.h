#ifndef QTMATERIALPROGRESS_H
#define QTMATERIALPROGRESS_H

#include <QProgressBar>
#include <QScopedPointer>
#include "lib/qtmaterialtheme.h"

class QtMaterialProgressPrivate;

class QtMaterialProgress : public QProgressBar
{
    Q_OBJECT

    Q_PROPERTY(QColor progressColor WRITE setProgressColor READ progressColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
    Q_PROPERTY(qreal trackThickness WRITE setTrackThickness READ trackThickness)
    Q_PROPERTY(bool roundedCaps WRITE setRoundedCaps READ hasRoundedCaps)
    Q_PROPERTY(bool showPercentage WRITE setShowPercentage READ showPercentage)

public:
    explicit QtMaterialProgress(QWidget *parent = 0);
    ~QtMaterialProgress();

    void setProgressType(Material::ProgressType type);
    Material::ProgressType progressType() const;

    void setUseThemeColors(bool state);
    bool useThemeColors() const;

    void setProgressColor(const QColor &color);
    QColor progressColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setTrackThickness(qreal value);
    qreal trackThickness() const;

    void setRoundedCaps(bool value);
    bool hasRoundedCaps() const;

    void setShowPercentage(bool value);
    bool showPercentage() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialProgressPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialProgress)
    Q_DECLARE_PRIVATE(QtMaterialProgress)
};

#endif // QTMATERIALPROGRESS_H
