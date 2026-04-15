#ifndef QTMATERIALSEARCHVIEW_H
#define QTMATERIALSEARCHVIEW_H

#include <QWidget>
#include <QColor>
#include <QStringList>

class QLineEdit;
class QListWidget;
class QToolButton;
class QListWidgetItem;

class QtMaterialSearchViewPrivate;

class QtMaterialSearchView : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor dividerColor READ dividerColor WRITE setDividerColor)
    Q_PROPERTY(bool active READ isActive WRITE setActive)

public:
    explicit QtMaterialSearchView(QWidget *parent = 0);
    ~QtMaterialSearchView();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setDividerColor(const QColor &color);
    QColor dividerColor() const;

    void setPlaceholderText(const QString &text);
    QString placeholderText() const;

    void setSuggestions(const QStringList &items);
    QStringList suggestions() const;

    void setActive(bool value);
    bool isActive() const;

    QString text() const;
    void clear();

signals:
    void searchRequested(const QString &text);
    void suggestionSelected(const QString &text);
    void activeChanged(bool active);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void updateSuggestions(const QString &text);
    void handleReturnPressed();
    void handleSuggestionClicked(QListWidgetItem *item);

private:
    Q_DISABLE_COPY(QtMaterialSearchView)

    QtMaterialSearchViewPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QtMaterialSearchView)
};

#endif // QTMATERIALSEARCHVIEW_H
