#ifndef QTMATERIALEXPANSIONPANEL_H
#define QTMATERIALEXPANSIONPANEL_H

#include <QWidget>
#include <QScopedPointer>
#include <QIcon>

class QLayout;
class QtMaterialExpansionPanelPrivate;

class QtMaterialExpansionPanel : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(QString subtitle READ subtitle WRITE setSubtitle)
    Q_PROPERTY(bool expanded READ isExpanded WRITE setExpanded)
    Q_PROPERTY(bool collapsible READ isCollapsible WRITE setCollapsible)
    Q_PROPERTY(bool showDivider READ showDivider WRITE setShowDivider)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor secondaryTextColor READ secondaryTextColor WRITE setSecondaryTextColor)
    Q_PROPERTY(QColor accentColor READ accentColor WRITE setAccentColor)

public:
    explicit QtMaterialExpansionPanel(QWidget *parent = 0);
    ~QtMaterialExpansionPanel();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setTitle(const QString &title);
    QString title() const;

    void setSubtitle(const QString &subtitle);
    QString subtitle() const;

    void setHeaderIcon(const QIcon &icon);
    QIcon headerIcon() const;

    void setContentLayout(QLayout *layout);
    QLayout *contentLayout() const;

    void setExpanded(bool value);
    bool isExpanded() const;

    void expand();
    void collapse();
    void toggle();

    void setCollapsible(bool value);
    bool isCollapsible() const;

    void setShowDivider(bool value);
    bool showDivider() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setSecondaryTextColor(const QColor &color);
    QColor secondaryTextColor() const;

    void setAccentColor(const QColor &color);
    QColor accentColor() const;

Q_SIGNALS:
    void expandedChanged(bool expanded);
    void headerClicked();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialExpansionPanel)
    Q_DECLARE_PRIVATE(QtMaterialExpansionPanel)
    const QScopedPointer<QtMaterialExpansionPanelPrivate> d_ptr;
};

#endif // QTMATERIALEXPANSIONPANEL_H
