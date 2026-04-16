#ifndef QTMATERIALSHEETHANDLE_H
#define QTMATERIALSHEETHANDLE_H

#include <QWidget>
#include <QColor>
#include <QScopedPointer>

class QtMaterialSheetHandlePrivate;

class QtMaterialSheetHandle : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(int handleWidth READ handleWidth WRITE setHandleWidth)
    Q_PROPERTY(int handleHeight READ handleHeight WRITE setHandleHeight)
    Q_PROPERTY(int hitTargetSize READ hitTargetSize WRITE setHitTargetSize)
    Q_PROPERTY(bool cycleDetentsOnClick READ cycleDetentsOnClick WRITE setCycleDetentsOnClick)

public:
    explicit QtMaterialSheetHandle(QWidget *parent = 0);
    ~QtMaterialSheetHandle();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setColor(const QColor &color);
    QColor color() const;

    void setHandleWidth(int value);
    int handleWidth() const;

    void setHandleHeight(int value);
    int handleHeight() const;

    void setHitTargetSize(int value);
    int hitTargetSize() const;

    void setCycleDetentsOnClick(bool value);
    bool cycleDetentsOnClick() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

signals:
    void clicked();
    void cycleRequested();
    void dragStarted();
    void dragDeltaChanged(const QPoint &delta);
    void dragFinished();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialSheetHandle)
    Q_DECLARE_PRIVATE(QtMaterialSheetHandle)
    const QScopedPointer<QtMaterialSheetHandlePrivate> d_ptr;
};

#endif // QTMATERIALSHEETHANDLE_H
