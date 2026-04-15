#ifndef QTMATERIALFLOATINGTOOLBAR_H
#define QTMATERIALFLOATINGTOOLBAR_H

#include <QWidget>
#include <QColor>
#include <QScopedPointer>

class QtMaterialFloatingToolBarPrivate;

class QtMaterialFloatingToolBar : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(int radius READ radius WRITE setRadius)
    Q_PROPERTY(int contentPadding READ contentPadding WRITE setContentPadding)

public:
    explicit QtMaterialFloatingToolBar(QWidget *parent = 0);
    ~QtMaterialFloatingToolBar();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setRadius(int value);
    int radius() const;

    void setContentPadding(int value);
    int contentPadding() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialFloatingToolBar)
    Q_DECLARE_PRIVATE(QtMaterialFloatingToolBar)
    const QScopedPointer<QtMaterialFloatingToolBarPrivate> d_ptr;
};

#endif // QTMATERIALFLOATINGTOOLBAR_H
