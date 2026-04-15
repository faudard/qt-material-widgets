#ifndef QTMATERIALCAROUSEL_H
#define QTMATERIALCAROUSEL_H

#include <QWidget>
#include <QColor>
#include <QScopedPointer>

class QStackedLayout;
class QtMaterialCarouselPrivate;

class QtMaterialCarousel : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(bool autoPlay READ autoPlay WRITE setAutoPlay)
    Q_PROPERTY(int autoPlayInterval READ autoPlayInterval WRITE setAutoPlayInterval)
    Q_PROPERTY(bool showIndicators READ showIndicators WRITE setShowIndicators)
    Q_PROPERTY(bool wrap READ wrap WRITE setWrap)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor indicatorColor READ indicatorColor WRITE setIndicatorColor)
    Q_PROPERTY(QColor activeIndicatorColor READ activeIndicatorColor WRITE setActiveIndicatorColor)

public:
    explicit QtMaterialCarousel(QWidget *parent = 0);
    ~QtMaterialCarousel();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setAutoPlay(bool value);
    bool autoPlay() const;

    void setAutoPlayInterval(int msec);
    int autoPlayInterval() const;

    void setShowIndicators(bool value);
    bool showIndicators() const;

    void setWrap(bool value);
    bool wrap() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setIndicatorColor(const QColor &color);
    QColor indicatorColor() const;

    void setActiveIndicatorColor(const QColor &color);
    QColor activeIndicatorColor() const;

    void addSlide(QWidget *widget);
    int count() const;
    int currentIndex() const;
    QWidget *currentWidget() const;

public slots:
    void setCurrentIndex(int index);
    void next();
    void previous();

signals:
    void currentIndexChanged(int index);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialCarousel)
    Q_DECLARE_PRIVATE(QtMaterialCarousel)

    const QScopedPointer<QtMaterialCarouselPrivate> d_ptr;
};

#endif // QTMATERIALCAROUSEL_H
