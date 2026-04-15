#ifndef QTMATERIALCAROUSEL_P_H
#define QTMATERIALCAROUSEL_P_H

#include <QColor>
#include <QBasicTimer>
#include <QPoint>

class QStackedLayout;
class QWidget;

class QtMaterialCarousel;

class QtMaterialCarouselPrivate
{
    Q_DISABLE_COPY(QtMaterialCarouselPrivate)
    Q_DECLARE_PUBLIC(QtMaterialCarousel)

public:
    QtMaterialCarouselPrivate(QtMaterialCarousel *q);
    ~QtMaterialCarouselPrivate();

    void init();
    void updateAutoPlay();
    QRect indicatorRect(int index, const QSize &size) const;

    QtMaterialCarousel *const q_ptr;
    QStackedLayout *stack;
    QBasicTimer timer;
    bool useThemeColors;
    bool autoPlay;
    int autoPlayInterval;
    bool showIndicators;
    bool wrap;
    QColor backgroundColor;
    QColor indicatorColor;
    QColor activeIndicatorColor;
    int indicatorDiameter;
    int indicatorSpacing;
    int bottomPadding;
};

#endif // QTMATERIALCAROUSEL_P_H
