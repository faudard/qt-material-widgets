#ifndef QTMATERIALSEARCHAPPBAR_H
#define QTMATERIALSEARCHAPPBAR_H

#include <QWidget>
#include <QScopedPointer>
#include <QColor>

class QtMaterialSearchAppBarPrivate;
class QtMaterialSearchBar;

class QtMaterialSearchAppBar : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor foregroundColor WRITE setForegroundColor READ foregroundColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor dividerColor WRITE setDividerColor READ dividerColor)
    Q_PROPERTY(bool active WRITE setActive READ isActive)
    Q_PROPERTY(bool showDivider WRITE setShowDivider READ showDivider)

public:
    explicit QtMaterialSearchAppBar(QWidget *parent = 0);
    ~QtMaterialSearchAppBar();

    QSize sizeHint() const Q_DECL_OVERRIDE;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setForegroundColor(const QColor &color);
    QColor foregroundColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setDividerColor(const QColor &color);
    QColor dividerColor() const;

    void setActive(bool value);
    bool isActive() const;

    void setShowDivider(bool value);
    bool showDivider() const;

    QtMaterialSearchBar *searchBar() const;
    QWidget *leadingContainer() const;
    QWidget *trailingContainer() const;

signals:
    void activeChanged(bool value);
    void searchRequested(const QString &text);
    void backClicked();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialSearchAppBarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialSearchAppBar)
    Q_DECLARE_PRIVATE(QtMaterialSearchAppBar)
};

#endif // QTMATERIALSEARCHAPPBAR_H
