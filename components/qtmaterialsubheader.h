#ifndef QTMATERIALSUBHEADER_H
#define QTMATERIALSUBHEADER_H

#include <QScopedPointer>
#include <QWidget>
#include <Qt>

class QColor;
class QtMaterialSubheaderPrivate;

class QtMaterialSubheader : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QString text WRITE setText READ text)
    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
    Q_PROPERTY(int inset WRITE setInset READ inset)
    Q_PROPERTY(bool showDivider WRITE setShowDivider READ showDivider)
    Q_PROPERTY(bool dense WRITE setDense READ isDense)
    Q_PROPERTY(Qt::Alignment alignment WRITE setAlignment READ alignment)

public:
    explicit QtMaterialSubheader(QWidget *parent = 0);
    ~QtMaterialSubheader();

    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setText(const QString &text);
    QString text() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setInset(int value);
    int inset() const;

    void setShowDivider(bool value);
    bool showDivider() const;

    void setDense(bool value);
    bool isDense() const;

    void setAlignment(Qt::Alignment alignment);
    Qt::Alignment alignment() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialSubheaderPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialSubheader)
    Q_DECLARE_PRIVATE(QtMaterialSubheader)
};

#endif // QTMATERIALSUBHEADER_H
