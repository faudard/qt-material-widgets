#ifndef QTMATERIALBADGE_H
#define QTMATERIALBADGE_H

#include <QWidget>
#include <QColor>
#include <QIcon>

class QtMaterialBadgePrivate;

class QtMaterialBadge : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(int count READ count WRITE setCount)
    Q_PROPERTY(bool countMode READ countMode WRITE setCountMode)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
    Q_PROPERTY(bool outlined READ isOutlined WRITE setOutlined)
    Q_PROPERTY(bool visibleWhenZero READ visibleWhenZero WRITE setVisibleWhenZero)

public:
    explicit QtMaterialBadge(QWidget *parent = 0);
    ~QtMaterialBadge();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setText(const QString &text);
    QString text() const;

    void setCount(int value);
    int count() const;

    void setCountMode(bool value);
    bool countMode() const;

    void setVisibleWhenZero(bool value);
    bool visibleWhenZero() const;

    void setOutlined(bool value);
    bool isOutlined() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setBorderColor(const QColor &color);
    QColor borderColor() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

signals:
    void clicked();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialBadge)
    Q_DECLARE_PRIVATE(QtMaterialBadge)
    QtMaterialBadgePrivate *const d_ptr;
};

#endif // QTMATERIALBADGE_H
