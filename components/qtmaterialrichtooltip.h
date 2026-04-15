#ifndef QTMATERIALRICHTOOLTIP_H
#define QTMATERIALRICHTOOLTIP_H

#include "qtmaterialtooltip.h"
#include <QColor>
#include <QIcon>

class QtMaterialRichTooltipPrivate;

class QtMaterialRichTooltip : public QtMaterialTooltip
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(QString supportingText READ supportingText WRITE setSupportingText)
    Q_PROPERTY(QString primaryActionText READ primaryActionText WRITE setPrimaryActionText)
    Q_PROPERTY(QString secondaryActionText READ secondaryActionText WRITE setSecondaryActionText)
    Q_PROPERTY(QIcon icon READ icon WRITE setIcon)
    Q_PROPERTY(bool showIcon READ showIcon WRITE setShowIcon)
    Q_PROPERTY(int maximumTextWidth READ maximumTextWidth WRITE setMaximumTextWidth)
    Q_PROPERTY(QColor surfaceColor READ surfaceColor WRITE setSurfaceColor)
    Q_PROPERTY(QColor titleColor READ titleColor WRITE setTitleColor)
    Q_PROPERTY(QColor supportingTextColor READ supportingTextColor WRITE setSupportingTextColor)
    Q_PROPERTY(QColor actionColor READ actionColor WRITE setActionColor)

public:
    explicit QtMaterialRichTooltip(QWidget *parent = 0);
    ~QtMaterialRichTooltip();

    void setTitle(const QString &title);
    QString title() const;

    void setSupportingText(const QString &text);
    QString supportingText() const;

    void setPrimaryActionText(const QString &text);
    QString primaryActionText() const;

    void setSecondaryActionText(const QString &text);
    QString secondaryActionText() const;

    void setIcon(const QIcon &icon);
    QIcon icon() const;

    void setShowIcon(bool value);
    bool showIcon() const;

    void setMaximumTextWidth(int value);
    int maximumTextWidth() const;

    void setSurfaceColor(const QColor &color);
    QColor surfaceColor() const;

    void setTitleColor(const QColor &color);
    QColor titleColor() const;

    void setSupportingTextColor(const QColor &color);
    QColor supportingTextColor() const;

    void setActionColor(const QColor &color);
    QColor actionColor() const;

signals:
    void primaryActionTriggered();
    void secondaryActionTriggered();

protected:
    QSize sizeHint() const Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialRichTooltip)
    Q_DECLARE_PRIVATE(QtMaterialRichTooltip)

    const QScopedPointer<QtMaterialRichTooltipPrivate> d_ptr;
};

#endif  // QTMATERIALRICHTOOLTIP_H
