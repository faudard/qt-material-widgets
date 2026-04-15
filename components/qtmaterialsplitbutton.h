#ifndef QTMATERIALSPLITBUTTON_H
#define QTMATERIALSPLITBUTTON_H

#include <QWidget>
#include <QColor>
#include <QString>

class QToolButton;
class QMenu;
class QtMaterialSplitButtonPrivate;

class QtMaterialSplitButton : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor menuButtonColor READ menuButtonColor WRITE setMenuButtonColor)
    Q_PROPERTY(QColor dividerColor READ dividerColor WRITE setDividerColor)
    Q_PROPERTY(bool dense READ isDense WRITE setDense)

public:
    explicit QtMaterialSplitButton(QWidget *parent = 0);
    ~QtMaterialSplitButton();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setText(const QString &text);
    QString text() const;

    void setMenu(QMenu *menu);
    QMenu *menu() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setMenuButtonColor(const QColor &color);
    QColor menuButtonColor() const;

    void setDividerColor(const QColor &color);
    QColor dividerColor() const;

    void setDense(bool value);
    bool isDense() const;

signals:
    void clicked();
    void menuTriggered();
    void triggered(QAction *action);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void handleMainClicked();
    void handleMenuClicked();
    void handleActionTriggered(QAction *action);

private:
    Q_DISABLE_COPY(QtMaterialSplitButton)
    Q_DECLARE_PRIVATE(QtMaterialSplitButton)

    QtMaterialSplitButtonPrivate * const d_ptr;
};

#endif // QTMATERIALSPLITBUTTON_H
