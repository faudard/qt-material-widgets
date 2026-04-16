#ifndef QTMATERIALFULLDIALOG_H
#define QTMATERIALFULLDIALOG_H

#include <QWidget>

class QtMaterialFullScreenDialogPrivate;
class QLayout;

class QtMaterialFullScreenDialog : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor overlayColor READ overlayColor WRITE setOverlayColor)
    Q_PROPERTY(QColor titleColor READ titleColor WRITE setTitleColor)
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(bool dismissOnOverlayClick READ dismissOnOverlayClick WRITE setDismissOnOverlayClick)

public:
    explicit QtMaterialFullScreenDialog(QWidget *parent = 0);
    ~QtMaterialFullScreenDialog();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setOverlayColor(const QColor &color);
    QColor overlayColor() const;

    void setTitleColor(const QColor &color);
    QColor titleColor() const;

    void setTitle(const QString &title);
    QString title() const;

    void setContentLayout(QLayout *layout);
    QLayout *contentLayout() const;

    void setDismissOnOverlayClick(bool value);
    bool dismissOnOverlayClick() const;

public slots:
    void open();
    void close();

signals:
    void opened();
    void closed();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    Q_DISABLE_COPY(QtMaterialFullScreenDialog)
    Q_DECLARE_PRIVATE(QtMaterialFullScreenDialog)
    QtMaterialFullScreenDialogPrivate *d_ptr;
};

#endif // QTMATERIALFULLDIALOG_H
