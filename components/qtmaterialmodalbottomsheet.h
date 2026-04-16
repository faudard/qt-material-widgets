#ifndef QTMATERIALMODALBOTTOMSHEET_H
#define QTMATERIALMODALBOTTOMSHEET_H

#include <QWidget>
#include <QColor>

class QLayout;
class QtMaterialModalBottomSheetPrivate;

class QtMaterialModalBottomSheet : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(bool open READ isOpen WRITE setOpen)
    Q_PROPERTY(bool dismissOnOverlayClick READ dismissOnOverlayClick WRITE setDismissOnOverlayClick)
    Q_PROPERTY(int sheetHeight READ sheetHeight WRITE setSheetHeight)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor overlayColor READ overlayColor WRITE setOverlayColor)

public:
    explicit QtMaterialModalBottomSheet(QWidget *parent = 0);
    ~QtMaterialModalBottomSheet();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setOpen(bool value);
    bool isOpen() const;

    void open();
    void closeSheet();
    void toggle();

    void setDismissOnOverlayClick(bool value);
    bool dismissOnOverlayClick() const;

    void setSheetHeight(int value);
    int sheetHeight() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setOverlayColor(const QColor &color);
    QColor overlayColor() const;

    void setContentLayout(QLayout *layout);
    QLayout *contentLayout() const;

signals:
    void openChanged(bool open);

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialModalBottomSheet)
    Q_DECLARE_PRIVATE(QtMaterialModalBottomSheet)

    QtMaterialModalBottomSheetPrivate *const d_ptr;
};

#endif // QTMATERIALMODALBOTTOMSHEET_H
