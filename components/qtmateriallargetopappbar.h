#ifndef QTMATERIALLARGETOPAPPBAR_H
#define QTMATERIALLARGETOPAPPBAR_H
#include <QWidget>
#include <QColor>
#include <QScopedPointer>
class QtMaterialLargeTopAppBarPrivate;
class QtMaterialLargeTopAppBar : public QWidget {
    Q_OBJECT
    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(QString subtitle READ subtitle WRITE setSubtitle)
public:
    explicit QtMaterialLargeTopAppBar(QWidget *parent = 0); ~QtMaterialLargeTopAppBar();
    void setUseThemeColors(bool value); bool useThemeColors() const;
    void setForegroundColor(const QColor &color); QColor foregroundColor() const;
    void setBackgroundColor(const QColor &color); QColor backgroundColor() const;
    void setTitle(const QString &text); QString title() const;
    void setSubtitle(const QString &text); QString subtitle() const;
protected:
    QSize sizeHint() const Q_DECL_OVERRIDE; void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    const QScopedPointer<QtMaterialLargeTopAppBarPrivate> d_ptr;
private:
    Q_DISABLE_COPY(QtMaterialLargeTopAppBar)
    Q_DECLARE_PRIVATE(QtMaterialLargeTopAppBar)
};
#endif
