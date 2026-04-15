#ifndef QTMATERIALEXPANSIONPANEL_P_H
#define QTMATERIALEXPANSIONPANEL_P_H

#include <QColor>
#include <QIcon>
#include <QPointer>

class QVBoxLayout;
class QLayout;
class QWidget;
class QtMaterialExpansionPanel;

class QtMaterialExpansionPanelPrivate
{
    Q_DISABLE_COPY(QtMaterialExpansionPanelPrivate)
    Q_DECLARE_PUBLIC(QtMaterialExpansionPanel)

public:
    explicit QtMaterialExpansionPanelPrivate(QtMaterialExpansionPanel *q);

    void init();
    QColor resolvedBackgroundColor() const;
    QColor resolvedTextColor() const;
    QColor resolvedSecondaryTextColor() const;
    QColor resolvedAccentColor() const;
    int headerHeight() const;
    int bodyHeightHint() const;

    QtMaterialExpansionPanel *const q_ptr;

    bool useThemeColors;
    bool expanded;
    bool collapsible;
    bool showDivider;
    QString title;
    QString subtitle;
    QIcon headerIcon;
    QColor backgroundColor;
    QColor textColor;
    QColor secondaryTextColor;
    QColor accentColor;
    QPointer<QWidget> bodyWidget;
    QVBoxLayout *rootLayout;
    QLayout *contentLayout;
};

#endif // QTMATERIALEXPANSIONPANEL_P_H
