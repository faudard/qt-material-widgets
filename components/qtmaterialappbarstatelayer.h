#ifndef QTMATERIALAPPBARSTATELAYER_H
#define QTMATERIALAPPBARSTATELAYER_H

#include <QWidget>
#include <QColor>

class QtMaterialAppBarStateLayerPrivate;

class QtMaterialAppBarStateLayer : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(QColor baseColor READ baseColor WRITE setBaseColor)
    Q_PROPERTY(QColor scrolledColor READ scrolledColor WRITE setScrolledColor)
    Q_PROPERTY(qreal scrollProgress READ scrollProgress WRITE setScrollProgress)
    Q_PROPERTY(bool liftOnScroll READ liftOnScroll WRITE setLiftOnScroll)

public:
    explicit QtMaterialAppBarStateLayer(QWidget *parent = 0);
    ~QtMaterialAppBarStateLayer();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setBaseColor(const QColor &color);
    QColor baseColor() const;

    void setScrolledColor(const QColor &color);
    QColor scrolledColor() const;

    void setScrollProgress(qreal value);
    qreal scrollProgress() const;

    void setLiftOnScroll(bool value);
    bool liftOnScroll() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialAppBarStateLayer)
    Q_DECLARE_PRIVATE(QtMaterialAppBarStateLayer)
    QtMaterialAppBarStateLayerPrivate *const d_ptr;
};

#endif // QTMATERIALAPPBARSTATELAYER_H
