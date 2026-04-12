#ifndef QTMATERIALTABLE_H
#define QTMATERIALTABLE_H

#include <QColor>
#include <QScopedPointer>
#include <QTableView>

class QtMaterialTablePrivate;

class QtMaterialTable : public QTableView
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors WRITE setUseThemeColors READ useThemeColors)
    Q_PROPERTY(bool dense WRITE setDense READ isDense)
    Q_PROPERTY(QColor headerColor WRITE setHeaderColor READ headerColor)
    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor alternateBackgroundColor WRITE setAlternateBackgroundColor READ alternateBackgroundColor)
    Q_PROPERTY(QColor gridColor WRITE setGridColor READ gridColor)
    Q_PROPERTY(QColor selectedRowColor WRITE setSelectedRowColor READ selectedRowColor)
    Q_PROPERTY(QColor hoverRowColor WRITE setHoverRowColor READ hoverRowColor)

public:
    explicit QtMaterialTable(QWidget *parent = 0);
    ~QtMaterialTable();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setDense(bool value);
    bool isDense() const;

    void setHeaderColor(const QColor &color);
    QColor headerColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setAlternateBackgroundColor(const QColor &color);
    QColor alternateBackgroundColor() const;

    void setGridColor(const QColor &color);
    QColor gridColor() const;

    void setSelectedRowColor(const QColor &color);
    QColor selectedRowColor() const;

    void setHoverRowColor(const QColor &color);
    QColor hoverRowColor() const;

    int hoveredRow() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialTablePrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialTable)
    Q_DECLARE_PRIVATE(QtMaterialTable)
};

#endif // QTMATERIALTABLE_H
