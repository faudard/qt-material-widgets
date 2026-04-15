#ifndef QTMATERIALDOCKEDTOOLBAR_H
#define QTMATERIALDOCKEDTOOLBAR_H

#include <QWidget>
#include <QColor>
#include <QScopedPointer>

class QtMaterialDockedToolBarPrivate;

class QtMaterialDockedToolBar : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor dividerColor READ dividerColor WRITE setDividerColor)
    Q_PROPERTY(bool showDivider READ showDivider WRITE setShowDivider)
    Q_PROPERTY(int contentPadding READ contentPadding WRITE setContentPadding)

public:
    explicit QtMaterialDockedToolBar(QWidget *parent = 0);
    ~QtMaterialDockedToolBar();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setDividerColor(const QColor &color);
    QColor dividerColor() const;

    void setShowDivider(bool value);
    bool showDivider() const;

    void setContentPadding(int value);
    int contentPadding() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialDockedToolBar)
    Q_DECLARE_PRIVATE(QtMaterialDockedToolBar)
    const QScopedPointer<QtMaterialDockedToolBarPrivate> d_ptr;
};

#endif // QTMATERIALDOCKEDTOOLBAR_H
