#ifndef QTMATERIALSMALLTOPAPPBAR_H
#define QTMATERIALSMALLTOPAPPBAR_H
#include <QWidget>
#include <QColor>
#include <QScopedPointer>
class QtMaterialSmallTopAppBarPrivate;
class QtMaterialSmallTopAppBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(bool showDivider READ showDivider WRITE setShowDivider)
public:
    explicit QtMaterialSmallTopAppBar(QWidget *parent = 0);
    ~QtMaterialSmallTopAppBar();
    void setUseThemeColors(bool value); bool useThemeColors() const;
    void setForegroundColor(const QColor &color); QColor foregroundColor() const;
    void setBackgroundColor(const QColor &color); QColor backgroundColor() const;
    void setShowDivider(bool value); bool showDivider() const;
protected:
    QSize sizeHint() const Q_DECL_OVERRIDE; void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    const QScopedPointer<QtMaterialSmallTopAppBarPrivate> d_ptr;
private:
    Q_DISABLE_COPY(QtMaterialSmallTopAppBar)
    Q_DECLARE_PRIVATE(QtMaterialSmallTopAppBar)
};
#endif
