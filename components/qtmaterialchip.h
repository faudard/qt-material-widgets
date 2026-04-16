#ifndef QTMATERIALCHIP_H
#define QTMATERIALCHIP_H

#include <QAbstractButton>
#include <QColor>
#include <QIcon>
#include <QScopedPointer>

class QtMaterialChipPrivate;

class QtMaterialChip : public QAbstractButton
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors WRITE setUseThemeColors READ useThemeColors)
    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor selectedColor WRITE setSelectedColor READ selectedColor)
    Q_PROPERTY(QColor disabledColor WRITE setDisabledColor READ disabledColor)
    Q_PROPERTY(bool showLeadingIcon WRITE setShowLeadingIcon READ showLeadingIcon)
    Q_PROPERTY(bool showTrailingIcon WRITE setShowTrailingIcon READ showTrailingIcon)
    Q_PROPERTY(bool closable WRITE setClosable READ isClosable)

public:
    explicit QtMaterialChip(QWidget *parent = 0);
    explicit QtMaterialChip(const QString &text, QWidget *parent = 0);
    ~QtMaterialChip();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setSelectedColor(const QColor &color);
    QColor selectedColor() const;

    void setDisabledColor(const QColor &color);
    QColor disabledColor() const;

    void setShowLeadingIcon(bool value);
    bool showLeadingIcon() const;

    void setLeadingIcon(const QIcon &icon);
    QIcon leadingIcon() const;

    void setShowTrailingIcon(bool value);
    bool showTrailingIcon() const;

    void setTrailingIcon(const QIcon &icon);
    QIcon trailingIcon() const;

    void setClosable(bool value);
    bool isClosable() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;

signals:
    void closeClicked();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialChipPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialChip)
    Q_DECLARE_PRIVATE(QtMaterialChip)
};

#endif // QTMATERIALCHIP_H
