#ifndef QTMATERIALMENU_INTERNAL_H
#define QTMATERIALMENU_INTERNAL_H

#include <QColor>
#include <QWidget>

class QAction;

class QtMaterialMenuItem : public QWidget
{
    Q_OBJECT

public:
    explicit QtMaterialMenuItem(QAction *action, QWidget *parent = 0);
    ~QtMaterialMenuItem();

    void setDense(bool value);
    void setTextColor(const QColor &color);
    void setSelectedColor(const QColor &color);
    void setDisabledColor(const QColor &color);

    QAction *action() const;
    QSize sizeHint() const Q_DECL_OVERRIDE;

signals:
    void triggered(QAction *action);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void updateFromAction();

private:
    QAction *const m_action;
    QColor m_textColor;
    QColor m_selectedColor;
    QColor m_disabledColor;
    bool m_dense;
    bool m_hovered;
    bool m_pressed;
};

#endif // QTMATERIALMENU_INTERNAL_H
