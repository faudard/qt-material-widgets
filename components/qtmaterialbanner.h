#ifndef QTMATERIALBANNER_H
#define QTMATERIALBANNER_H

#include <QWidget>
#include <QColor>
#include <QIcon>
#include <QScopedPointer>

class QtMaterialBannerPrivate;
class QAbstractButton;
class QLabel;
class QHBoxLayout;

class QtMaterialBanner : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QString supportingText READ supportingText WRITE setSupportingText)
    Q_PROPERTY(bool dismissible READ isDismissible WRITE setDismissible)
    Q_PROPERTY(bool showLeadingIcon READ showLeadingIcon WRITE setShowLeadingIcon)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor supportingTextColor READ supportingTextColor WRITE setSupportingTextColor)
    Q_PROPERTY(QColor accentColor READ accentColor WRITE setAccentColor)

public:
    explicit QtMaterialBanner(QWidget *parent = 0);
    ~QtMaterialBanner();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setText(const QString &text);
    QString text() const;

    void setSupportingText(const QString &text);
    QString supportingText() const;

    void setLeadingIcon(const QIcon &icon);
    QIcon leadingIcon() const;

    void setShowLeadingIcon(bool value);
    bool showLeadingIcon() const;

    void setDismissible(bool value);
    bool isDismissible() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setSupportingTextColor(const QColor &color);
    QColor supportingTextColor() const;

    void setAccentColor(const QColor &color);
    QColor accentColor() const;

    void setPrimaryActionText(const QString &text);
    QString primaryActionText() const;

    void setSecondaryActionText(const QString &text);
    QString secondaryActionText() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

signals:
    void primaryActionTriggered();
    void secondaryActionTriggered();
    void dismissed();

public slots:
    void dismiss();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private slots:
    void updateLayoutState();

private:
    Q_DISABLE_COPY(QtMaterialBanner)
    Q_DECLARE_PRIVATE(QtMaterialBanner)
    const QScopedPointer<QtMaterialBannerPrivate> d_ptr;
};

#endif // QTMATERIALBANNER_H
