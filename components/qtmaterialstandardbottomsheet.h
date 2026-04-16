#ifndef QTMATERIALSTANDARDBOTTOMSHEET_H
#define QTMATERIALSTANDARDBOTTOMSHEET_H

#include <QWidget>
#include <QColor>

class QLayout;
class QtMaterialStandardBottomSheetPrivate;

class QtMaterialStandardBottomSheet : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(int sheetHeight READ sheetHeight WRITE setSheetHeight)
    Q_PROPERTY(bool expanded READ isExpanded WRITE setExpanded)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor dividerColor READ dividerColor WRITE setDividerColor)

public:
    explicit QtMaterialStandardBottomSheet(QWidget *parent = 0);
    ~QtMaterialStandardBottomSheet();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setSheetHeight(int value);
    int sheetHeight() const;

    void setExpanded(bool value);
    bool isExpanded() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setDividerColor(const QColor &color);
    QColor dividerColor() const;

    void setContentLayout(QLayout *layout);
    QLayout *contentLayout() const;

signals:
    void expandedChanged(bool expanded);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialStandardBottomSheet)
    Q_DECLARE_PRIVATE(QtMaterialStandardBottomSheet)

    QtMaterialStandardBottomSheetPrivate *const d_ptr;
};

#endif // QTMATERIALSTANDARDBOTTOMSHEET_H
