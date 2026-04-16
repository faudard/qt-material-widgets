#ifndef QTMATERIALSTANDARDSIDESHEET_H
#define QTMATERIALSTANDARDSIDESHEET_H

#include <QColor>
#include <QWidget>

class QtMaterialStandardSideSheetPrivate;

class QtMaterialStandardSideSheet : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(int sheetWidth READ sheetWidth WRITE setSheetWidth)
    Q_PROPERTY(bool expanded READ isExpanded WRITE setExpanded)

public:
    explicit QtMaterialStandardSideSheet(QWidget *parent = 0);
    ~QtMaterialStandardSideSheet();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setSheetWidth(int width);
    int sheetWidth() const;

    void setExpanded(bool value);
    bool isExpanded() const;

    void setContentLayout(QLayout *layout);
    QLayout *contentLayout() const;

signals:
    void expandedChanged(bool expanded);

protected:
    void paintEvent(QPaintEvent *event) override;
    QSize sizeHint() const override;

private:
    Q_DISABLE_COPY(QtMaterialStandardSideSheet)
    Q_DECLARE_PRIVATE(QtMaterialStandardSideSheet)
    QtMaterialStandardSideSheetPrivate *const d_ptr;
};

#endif // QTMATERIALSTANDARDSIDESHEET_H
