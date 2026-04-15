#ifndef QTMATERIALSIDESHEET_H
#define QTMATERIALSIDESHEET_H

#include <QLayout>
#include <QScopedPointer>
#include "lib/qtmaterialoverlaywidget.h"

class QtMaterialSideSheetPrivate;

class QtMaterialSideSheet : public QtMaterialOverlayWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor overlayColor READ overlayColor WRITE setOverlayColor)
    Q_PROPERTY(int sheetWidth READ sheetWidth WRITE setSheetWidth)
    Q_PROPERTY(bool modal READ isModal WRITE setModal)
    Q_PROPERTY(bool dismissOnOverlayClick READ dismissOnOverlayClick WRITE setDismissOnOverlayClick)
    Q_PROPERTY(Side edge READ edge WRITE setEdge)

public:
    enum Side {
        Left,
        Right
    };
    Q_ENUM(Side)

    explicit QtMaterialSideSheet(QWidget *parent = 0);
    ~QtMaterialSideSheet();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setOverlayColor(const QColor &color);
    QColor overlayColor() const;

    void setSheetWidth(int width);
    int sheetWidth() const;

    void setModal(bool value);
    bool isModal() const;

    void setDismissOnOverlayClick(bool value);
    bool dismissOnOverlayClick() const;

    void setEdge(Side side);
    Side edge() const;

    void setContentLayout(QLayout *layout);
    QLayout *contentLayout() const;

public slots:
    void open();
    void closeSheet();

signals:
    void opened();
    void closed();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialSideSheet)
    Q_DECLARE_PRIVATE(QtMaterialSideSheet)
    const QScopedPointer<QtMaterialSideSheetPrivate> d_ptr;
};

#endif // QTMATERIALSIDESHEET_H
