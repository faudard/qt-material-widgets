#ifndef QTMATERIALSEARCHBAR_H
#define QTMATERIALSEARCHBAR_H

#include <QWidget>
#include <QColor>

class QAction;
class QLayout;
class QStringList;
class QtMaterialSearchField;
class QtMaterialSearchBarPrivate;

class QtMaterialSearchBar : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(QString placeholderText READ placeholderText WRITE setPlaceholderText)
    Q_PROPERTY(bool active READ isActive WRITE setActive)
    Q_PROPERTY(bool collapsible READ isCollapsible WRITE setCollapsible)
    Q_PROPERTY(bool showLeadingNavigationIcon READ showLeadingNavigationIcon WRITE setShowLeadingNavigationIcon)
    Q_PROPERTY(bool showTrailingActions READ showTrailingActions WRITE setShowTrailingActions)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor placeholderColor READ placeholderColor WRITE setPlaceholderColor)
    Q_PROPERTY(QColor iconColor READ iconColor WRITE setIconColor)
    Q_PROPERTY(QColor dividerColor READ dividerColor WRITE setDividerColor)

public:
    explicit QtMaterialSearchBar(QWidget *parent = 0);
    ~QtMaterialSearchBar();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setPlaceholderText(const QString &text);
    QString placeholderText() const;

    void setActive(bool value);
    bool isActive() const;

    void setCollapsible(bool value);
    bool isCollapsible() const;

    void setShowLeadingNavigationIcon(bool value);
    bool showLeadingNavigationIcon() const;

    void setShowTrailingActions(bool value);
    bool showTrailingActions() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setPlaceholderColor(const QColor &color);
    QColor placeholderColor() const;

    void setIconColor(const QColor &color);
    QColor iconColor() const;

    void setDividerColor(const QColor &color);
    QColor dividerColor() const;

    void setSuggestions(const QStringList &suggestions);
    QStringList suggestions() const;

    void setSearchDelay(int msec);
    int searchDelay() const;

    void setInputLayout(QLayout *layout);
    QLayout *inputLayout() const;

    QtMaterialSearchField *searchField() const;

    QAction *addTrailingAction(const QIcon &icon, const QString &toolTip = QString());
    void clearTrailingActions();

signals:
    void searchRequested(const QString &text);
    void textChanged(const QString &text);
    void cleared();
    void activated();
    void collapsed();

public slots:
    void clear();
    void expand();
    void collapse();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    Q_DISABLE_COPY(QtMaterialSearchBar)
    Q_DECLARE_PRIVATE(QtMaterialSearchBar)
    QtMaterialSearchBarPrivate *const d_ptr;
};

#endif // QTMATERIALSEARCHBAR_H
