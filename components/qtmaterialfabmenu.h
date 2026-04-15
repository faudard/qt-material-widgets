#ifndef QTMATERIALFABMENU_H
#define QTMATERIALFABMENU_H

#include <QWidget>
#include <QIcon>

class QtMaterialFloatingActionButton;
class QtMaterialFabMenuPrivate;

class QtMaterialFabMenu : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(bool expanded READ isExpanded WRITE setExpanded)
    Q_PROPERTY(bool labelsVisible READ labelsVisible WRITE setLabelsVisible)
    Q_PROPERTY(int actionSpacing READ actionSpacing WRITE setActionSpacing)
    Q_PROPERTY(Qt::Corner corner READ corner WRITE setCorner)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor)
    Q_PROPERTY(QColor overlayColor READ overlayColor WRITE setOverlayColor)

public:
    explicit QtMaterialFabMenu(QWidget *parent = 0);
    ~QtMaterialFabMenu();

    int addAction(const QIcon &icon, const QString &toolTip = QString(), const QString &label = QString());
    void removeAction(int index);
    int count() const;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setExpanded(bool value);
    bool isExpanded() const;

    void expand();
    void collapse();
    void toggleExpanded();

    void setLabelsVisible(bool value);
    bool labelsVisible() const;

    void setActionSpacing(int value);
    int actionSpacing() const;

    void setCorner(Qt::Corner corner);
    Qt::Corner corner() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setForegroundColor(const QColor &color);
    QColor foregroundColor() const;

    void setOverlayColor(const QColor &color);
    QColor overlayColor() const;

signals:
    void expandedChanged(bool expanded);
    void actionTriggered(int index);

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialFabMenu)
    Q_DECLARE_PRIVATE(QtMaterialFabMenu)
    QtMaterialFabMenuPrivate *const d_ptr;
};

#endif // QTMATERIALFABMENU_H