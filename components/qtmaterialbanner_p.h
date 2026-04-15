#ifndef QTMATERIALBANNER_P_H
#define QTMATERIALBANNER_P_H

#include <QColor>
#include <QIcon>

class QLabel;
class QToolButton;
class QHBoxLayout;
class QVBoxLayout;

class QtMaterialBanner;

class QtMaterialBannerPrivate
{
    Q_DISABLE_COPY(QtMaterialBannerPrivate)
    Q_DECLARE_PUBLIC(QtMaterialBanner)

public:
    QtMaterialBannerPrivate(QtMaterialBanner *q);
    ~QtMaterialBannerPrivate();

    void init();

    QtMaterialBanner             *const q_ptr;
    bool                          useThemeColors;
    bool                          showLeadingIcon;
    bool                          dismissible;
    QString                       text;
    QString                       supportingText;
    QString                       primaryActionText;
    QString                       secondaryActionText;
    QIcon                         leadingIcon;
    QColor                        backgroundColor;
    QColor                        textColor;
    QColor                        supportingTextColor;
    QColor                        accentColor;
    QLabel                       *iconLabel;
    QLabel                       *textLabel;
    QLabel                       *supportingLabel;
    QToolButton                  *primaryButton;
    QToolButton                  *secondaryButton;
    QToolButton                  *dismissButton;
    QHBoxLayout                  *mainLayout;
    QVBoxLayout                  *textLayout;
};

#endif // QTMATERIALBANNER_P_H
