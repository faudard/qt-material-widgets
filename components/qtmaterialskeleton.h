#ifndef QTMATERIALSKELETON_H
#define QTMATERIALSKELETON_H

#include <QScopedPointer>
#include <QWidget>

class QColor;
class QtMaterialSkeletonPrivate;

class QtMaterialSkeleton : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor highlightColor WRITE setHighlightColor READ highlightColor)
    Q_PROPERTY(bool animationEnabled WRITE setAnimationEnabled READ animationEnabled)
    Q_PROPERTY(bool useThemeColors WRITE setUseThemeColors READ useThemeColors)
    Q_PROPERTY(int cornerRadius WRITE setCornerRadius READ cornerRadius)
    Q_PROPERTY(int lineCount WRITE setLineCount READ lineCount)
    Q_PROPERTY(bool circular WRITE setCircular READ isCircular)

public:
    explicit QtMaterialSkeleton(QWidget *parent = 0);
    ~QtMaterialSkeleton();

    enum DisplayMode {
        SingleBlock,
        TextLines
    };
    Q_ENUM(DisplayMode)

    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setHighlightColor(const QColor &color);
    QColor highlightColor() const;

    void setAnimationEnabled(bool value);
    bool animationEnabled() const;

    void setCornerRadius(int value);
    int cornerRadius() const;

    void setLineCount(int value);
    int lineCount() const;

    void setCircular(bool value);
    bool isCircular() const;

    void setDisplayMode(DisplayMode mode);
    DisplayMode displayMode() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialSkeletonPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialSkeleton)
    Q_DECLARE_PRIVATE(QtMaterialSkeleton)
};

#endif // QTMATERIALSKELETON_H
