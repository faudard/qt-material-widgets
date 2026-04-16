#ifndef QTMATERIALRESPONSIVENAVIGATION_H
#define QTMATERIALRESPONSIVENAVIGATION_H

#include <QWidget>
#include <QColor>
#include <QScopedPointer>

class QtMaterialResponsiveNavigationPrivate;
class QtMaterialNavigationBar;
class QtMaterialNavigationRail;
class QtMaterialStandardNavigationDrawer;

class QtMaterialResponsiveNavigation : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(int compactBreakpoint READ compactBreakpoint WRITE setCompactBreakpoint)
    Q_PROPERTY(int mediumBreakpoint READ mediumBreakpoint WRITE setMediumBreakpoint)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)

public:
    explicit QtMaterialResponsiveNavigation(QWidget *parent = 0);
    ~QtMaterialResponsiveNavigation();

    enum NavigationMode {
        BottomBarMode,
        RailMode,
        DrawerMode,
    };
    Q_ENUM(NavigationMode)

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setCompactBreakpoint(int value);
    int compactBreakpoint() const;

    void setMediumBreakpoint(int value);
    int mediumBreakpoint() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void addItem(const QIcon &icon, const QString &text);
    int currentIndex() const;
    void setCurrentIndex(int index);

    NavigationMode navigationMode() const;
    void setNavigationMode(NavigationMode mode);
    void updateForAvailableWidth(int width);

signals:
    void currentChanged(int index);
    void modeChanged(QtMaterialResponsiveNavigation::NavigationMode mode);

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialResponsiveNavigation)
    Q_DECLARE_PRIVATE(QtMaterialResponsiveNavigation)
    const QScopedPointer<QtMaterialResponsiveNavigationPrivate> d_ptr;
};

#endif // QTMATERIALRESPONSIVENAVIGATION_H
