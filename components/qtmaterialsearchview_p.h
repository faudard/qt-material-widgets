#ifndef QTMATERIALSEARCHVIEW_P_H
#define QTMATERIALSEARCHVIEW_P_H

#include <QColor>
#include <QStringList>

class QFrame;
class QLineEdit;
class QListWidget;
class QToolButton;
class QVBoxLayout;
class QHBoxLayout;

class QtMaterialSearchView;

class QtMaterialSearchViewPrivate
{
    Q_DISABLE_COPY(QtMaterialSearchViewPrivate)
    Q_DECLARE_PUBLIC(QtMaterialSearchView)

public:
    explicit QtMaterialSearchViewPrivate(QtMaterialSearchView *q);
    ~QtMaterialSearchViewPrivate();

    void init();
    void applyActiveState();
    QColor resolveBackgroundColor() const;
    QColor resolveTextColor() const;
    QColor resolveDividerColor() const;

    QtMaterialSearchView *const q_ptr;

    bool useThemeColors;
    bool active;
    QColor backgroundColor;
    QColor textColor;
    QColor dividerColor;
    QStringList suggestionItems;

    QFrame *surface;
    QFrame *header;
    QLineEdit *lineEdit;
    QToolButton *backButton;
    QToolButton *clearButton;
    QListWidget *listWidget;
    QVBoxLayout *rootLayout;
    QVBoxLayout *surfaceLayout;
    QHBoxLayout *headerLayout;
};

#endif // QTMATERIALSEARCHVIEW_P_H
