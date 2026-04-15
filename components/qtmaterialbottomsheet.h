#ifndef QTMATERIALBOTTOMSHEET_H
#define QTMATERIALBOTTOMSHEET_H

#include <QColor>
#include <QPointer>

#include "lib/qtmaterialoverlaywidget.h"

class QLayout;
class QtMaterialBottomSheetPrivate;

class QtMaterialBottomSheet : public QtMaterialOverlayWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor overlayColor READ overlayColor WRITE setOverlayColor)
    Q_PROPERTY(int sheetHeight READ sheetHeight WRITE setSheetHeight)
    Q_PROPERTY(bool modal READ isModal WRITE setModal)
    Q_PROPERTY(bool dismissOnOverlayClick READ dismissOnOverlayClick WRITE setDismissOnOverlayClick)

public:
    explicit QtMaterialBottomSheet(QWidget *parent = 0);
    ~QtMaterialBottomSheet();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setOverlayColor(const QColor &color);
    QColor overlayColor() const;

    void setSheetHeight(int height);
    int sheetHeight() const;

    void setModal(bool value);
    bool isModal() const;

    void setDismissOnOverlayClick(bool value);
    bool dismissOnOverlayClick() const;

    void setContentLayout(QLayout *layout);
    QLayout *contentLayout() const;

public slots:
    void showSheet();
    void hideSheet();

signals:
    void opened();
    void closed();

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    QRect overlayGeometry() const Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialBottomSheet)
    Q_DECLARE_PRIVATE(QtMaterialBottomSheet)

    QtMaterialBottomSheetPrivate *const d_ptr;
};

#endif // QTMATERIALBOTTOMSHEET_H
