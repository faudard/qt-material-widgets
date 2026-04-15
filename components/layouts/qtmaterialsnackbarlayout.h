#ifndef QTMATERIALSNACKBARLAYOUT_H
#define QTMATERIALSNACKBARLAYOUT_H

#include <QLayout>
#include <QScopedPointer>

class QtMaterialSnackbarLayoutPrivate;

class QtMaterialSnackbarLayout : public QLayout
{
    Q_OBJECT

    Q_PROPERTY(bool dense WRITE setDense READ isDense)
    Q_PROPERTY(int messageSpacing WRITE setMessageSpacing READ messageSpacing)
    Q_PROPERTY(int singleLineHeight WRITE setSingleLineHeight READ singleLineHeight)
    Q_PROPERTY(int multiLineHeight WRITE setMultiLineHeight READ multiLineHeight)

public:
    explicit QtMaterialSnackbarLayout(QWidget *parent = 0);
    ~QtMaterialSnackbarLayout();

    void addItem(QLayoutItem *item) Q_DECL_OVERRIDE;
    int count() const Q_DECL_OVERRIDE;
    QLayoutItem *itemAt(int index) const Q_DECL_OVERRIDE;
    QLayoutItem *takeAt(int index) Q_DECL_OVERRIDE;

    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSize() const Q_DECL_OVERRIDE;
    Qt::Orientations expandingDirections() const Q_DECL_OVERRIDE;
    bool hasHeightForWidth() const Q_DECL_OVERRIDE;
    int heightForWidth(int width) const Q_DECL_OVERRIDE;
    void setGeometry(const QRect &rect) Q_DECL_OVERRIDE;

    void setDense(bool value);
    bool isDense() const;

    void setMessageSpacing(int value);
    int messageSpacing() const;

    void setSingleLineHeight(int value);
    int singleLineHeight() const;

    void setMultiLineHeight(int value);
    int multiLineHeight() const;

protected:
    const QScopedPointer<QtMaterialSnackbarLayoutPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialSnackbarLayout)
    Q_DECLARE_PRIVATE(QtMaterialSnackbarLayout)
};

#endif // QTMATERIALSNACKBARLAYOUT_H
