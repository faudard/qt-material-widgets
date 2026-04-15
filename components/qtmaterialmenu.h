#ifndef QTMATERIALMENU_H
#define QTMATERIALMENU_H

#include <QColor>
#include <QIcon>
#include <QScopedPointer>
#include <QWidget>

class QAction;
class QtMaterialMenuPrivate;

class QtMaterialMenu : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
    Q_PROPERTY(QColor selectedColor WRITE setSelectedColor READ selectedColor)
    Q_PROPERTY(int elevation WRITE setElevation READ elevation)

public:
    explicit QtMaterialMenu(QWidget *parent = 0);
    ~QtMaterialMenu();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setDense(bool value);
    bool isDense() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setSelectedColor(const QColor &color);
    QColor selectedColor() const;

    void setElevation(int value);
    int elevation() const;

    QAction *addMenuItem(const QString &text);
    QAction *addMenuItem(const QIcon &icon, const QString &text);
    QAction *addSeparator();
    void clearMenuItems();
    int itemCount() const;

public slots:
    void popup(const QPoint &pos);

signals:
    void triggered(QAction *action);

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialMenuPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialMenu)
    Q_DECLARE_PRIVATE(QtMaterialMenu)
};

#endif // QTMATERIALMENU_H
