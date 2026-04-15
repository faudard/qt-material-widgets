#ifndef QTMATERIALTOOLTIP_H
#define QTMATERIALTOOLTIP_H

#include "lib/qtmaterialoverlaywidget.h"

class QtMaterialTooltipPrivate;

class QtMaterialTooltip : public QtMaterialOverlayWidget
{
    Q_OBJECT

public:
    explicit QtMaterialTooltip(QWidget *parent = 0);
    ~QtMaterialTooltip();

    void setText(const QString &text);
    QString text() const;

    void setTarget(QWidget *widget);
    QWidget *target() const;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setFontSize(qreal size);
    qreal fontSize() const;

    void setPadding(int value);
    int padding() const;

    void setAutoHideDuration(int msec);
    int autoHideDuration() const;

public slots:
    void showTooltip();
    void hideTooltip();

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    QRect overlayGeometry() const Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialTooltipPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialTooltip)
    Q_DECLARE_PRIVATE(QtMaterialTooltip)
};

#endif // QTMATERIALTOOLTIP_H
