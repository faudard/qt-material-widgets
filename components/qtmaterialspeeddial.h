#ifndef QTMATERIALSPEEDDIAL_H
#define QTMATERIALSPEEDDIAL_H

#include <QWidget>
#include <QColor>
#include <QIcon>
#include <QStringList>
#include <QList>
#include <qvariant.h>

class QtMaterialFloatingActionButton;
class QtMaterialSpeedDialPrivate;

class QtMaterialSpeedDial : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor)
    Q_PROPERTY(QColor overlayColor READ overlayColor WRITE setOverlayColor)
    Q_PROPERTY(bool expanded READ isExpanded WRITE setExpanded)
    Q_PROPERTY(bool labelsVisible READ labelsVisible WRITE setLabelsVisible)
    Q_PROPERTY(int actionSpacing READ actionSpacing WRITE setActionSpacing)
    Q_PROPERTY(Qt::Corner anchorCorner READ anchorCorner WRITE setAnchorCorner)

public:
    explicit QtMaterialSpeedDial(QWidget *parent = 0);
    ~QtMaterialSpeedDial();

    struct ActionSpec {
        QIcon icon;
        QString text;
        QVariant data;
    };

    void addAction(const QIcon &icon, const QString &text, const QVariant &data = QVariant());
    void clearActions();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setForegroundColor(const QColor &color);
    QColor foregroundColor() const;

    void setOverlayColor(const QColor &color);
    QColor overlayColor() const;

    void setExpanded(bool value);
    bool isExpanded() const;

    void setLabelsVisible(bool value);
    bool labelsVisible() const;

    void setActionSpacing(int value);
    int actionSpacing() const;

    void setAnchorCorner(Qt::Corner corner);
    Qt::Corner anchorCorner() const;

signals:
    void actionTriggered(int index, QVariant data);
    void expandedChanged(bool expanded);

public slots:
    void toggle();
    void open();
    void close();

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialSpeedDial)
    Q_DECLARE_PRIVATE(QtMaterialSpeedDial)
    QtMaterialSpeedDialPrivate *const d_ptr;
};

#endif // QTMATERIALSPEEDDIAL_H
