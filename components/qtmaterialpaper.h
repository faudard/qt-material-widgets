#ifndef QTMATERIALPAPER_H
#define QTMATERIALPAPER_H

#include <QColor>
#include <QScopedPointer>
#include <QWidget>

class QtMaterialPaperPrivate;

class QtMaterialPaper : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor outlineColor WRITE setOutlineColor READ outlineColor)
    Q_PROPERTY(qreal cornerRadius WRITE setCornerRadius READ cornerRadius)
    Q_PROPERTY(int elevation WRITE setElevation READ elevation)

public:
    explicit QtMaterialPaper(QWidget *parent = 0);
    ~QtMaterialPaper();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setOutlineColor(const QColor &color);
    QColor outlineColor() const;

    void setCornerRadius(qreal radius);
    qreal cornerRadius() const;

    void setElevation(int value);
    int elevation() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialPaperPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialPaper)
    Q_DECLARE_PRIVATE(QtMaterialPaper)
};

#endif // QTMATERIALPAPER_H
