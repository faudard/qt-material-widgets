#ifndef QTMATERIALMODALSIDESHEET_H
#define QTMATERIALMODALSIDESHEET_H

#include <QColor>
#include <QWidget>

class QtMaterialModalSideSheetPrivate;

class QtMaterialModalSideSheet : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor overlayColor READ overlayColor WRITE setOverlayColor)
    Q_PROPERTY(int sheetWidth READ sheetWidth WRITE setSheetWidth)

public:
    enum Side {
        LeftSide,
        RightSide
    };
    Q_ENUM(Side)

    explicit QtMaterialModalSideSheet(QWidget *parent = 0);
    ~QtMaterialModalSideSheet();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setOverlayColor(const QColor &color);
    QColor overlayColor() const;

    void setSheetWidth(int width);
    int sheetWidth() const;

    void setSide(Side side);
    Side side() const;

    void setDismissOnOverlayClick(bool value);
    bool dismissOnOverlayClick() const;

    void setContentLayout(QLayout *layout);
    QLayout *contentLayout() const;

public slots:
    void open();
    void closeSheet();

signals:
    void opened();
    void closed();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Q_DISABLE_COPY(QtMaterialModalSideSheet)
    Q_DECLARE_PRIVATE(QtMaterialModalSideSheet)
    QtMaterialModalSideSheetPrivate *const d_ptr;
};

#endif // QTMATERIALMODALSIDESHEET_H
