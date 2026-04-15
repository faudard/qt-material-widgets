#ifndef QTMATERIALSEARCHFIELD_H
#define QTMATERIALSEARCHFIELD_H

#include "qtmaterialtextfield.h"

class QtMaterialSearchFieldPrivate;

/*!
 * \brief Material-style search field built on top of QtMaterialTextField.
 *
 * First-pass scope:
 *  - leading search icon
 *  - optional clear button
 *  - delayed search emission
 *  - placeholder / label support inherited from QtMaterialTextField
 */
class QtMaterialSearchField : public QtMaterialTextField
{
    Q_OBJECT

    Q_PROPERTY(bool showSearchIcon READ hasSearchIcon WRITE setShowSearchIcon)
    Q_PROPERTY(bool showClearButton READ hasClearButton WRITE setShowClearButton)
    Q_PROPERTY(int searchDelay READ searchDelay WRITE setSearchDelay)
    Q_PROPERTY(QColor iconColor READ iconColor WRITE setIconColor)

public:
    explicit QtMaterialSearchField(QWidget *parent = 0);
    ~QtMaterialSearchField();

    void setShowSearchIcon(bool value);
    bool hasSearchIcon() const;

    void setShowClearButton(bool value);
    bool hasClearButton() const;

    void setSearchDelay(int msec);
    int searchDelay() const;

    void setIconColor(const QColor &color);
    QColor iconColor() const;

    void setSearchIcon(const QIcon &icon);
    QIcon searchIcon() const;

    void setClearIcon(const QIcon &icon);
    QIcon clearIcon() const;

signals:
    void searchRequested(const QString &text);
    void cleared();

protected slots:
    void queueSearch(const QString &text);
    void emitSearch();
    void handleClearButtonClicked();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialSearchField)
    Q_DECLARE_PRIVATE(QtMaterialSearchField)

    const QScopedPointer<QtMaterialSearchFieldPrivate> d_ptr;
};

#endif // QTMATERIALSEARCHFIELD_H
