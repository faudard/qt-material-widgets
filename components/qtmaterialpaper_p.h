#ifndef QTMATERIALPAPER_P_H
#define QTMATERIALPAPER_P_H

#include <QColor>
#include <QGraphicsDropShadowEffect>

class QtMaterialPaper;

class QtMaterialPaperPrivate
{
    Q_DISABLE_COPY(QtMaterialPaperPrivate)
    Q_DECLARE_PUBLIC(QtMaterialPaper)

public:
    explicit QtMaterialPaperPrivate(QtMaterialPaper *q);
    ~QtMaterialPaperPrivate();

    void init();
    void updateDropShadow();
    int frameMargin() const;

    QtMaterialPaper *const q_ptr;
    QGraphicsDropShadowEffect *shadowEffect;
    QColor backgroundColor;
    QColor outlineColor;
    qreal cornerRadius;
    int elevation;
    bool useThemeColors;
};

#endif // QTMATERIALPAPER_P_H
