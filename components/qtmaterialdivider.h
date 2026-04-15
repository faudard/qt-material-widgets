#ifndef QTMATERIALDIVIDER_H
#define QTMATERIALDIVIDER_H

#include <QtWidgets/QWidget>
#include <QColor>
#include <QScopedPointer>
#include <QSize>

#include "lib/qtmaterialtheme.h"

class QtMaterialDividerPrivate;

class QtMaterialDivider : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors WRITE setUseThemeColors READ useThemeColors)
    Q_PROPERTY(QColor color WRITE setColor READ color)
    Q_PROPERTY(int thickness WRITE setThickness READ thickness)
    Q_PROPERTY(int insetStart WRITE setInsetStart READ insetStart)
    Q_PROPERTY(int insetEnd WRITE setInsetEnd READ insetEnd)

public:
    explicit QtMaterialDivider(QWidget *parent = 0);
    ~QtMaterialDivider();

    void setUseThemeColors(bool state);
    bool useThemeColors() const;

    void setColor(const QColor &color);
    QColor color() const;

    void setThickness(int thickness);
    int thickness() const;

    void setInsetStart(int inset);
    int insetStart() const;

    void setInsetEnd(int inset);
    int insetEnd() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialDividerPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialDivider)
    Q_DECLARE_PRIVATE(QtMaterialDivider)
};

#endif // QTMATERIALDIVIDER_H
