#ifndef QTMATERIALAUTOCOMPLETE_H
#define QTMATERIALAUTOCOMPLETE_H

#include "qtmaterialtextfield.h"

class QtMaterialAutoCompletePrivate;

class QtMaterialAutoComplete : public QtMaterialTextField
{
    Q_OBJECT

    Q_PROPERTY(int maxVisibleItems WRITE setMaxVisibleItems READ maxVisibleItems)
    Q_PROPERTY(Qt::CaseSensitivity caseSensitivity WRITE setCaseSensitivity READ caseSensitivity)
    Q_PROPERTY(FilterMode filterMode WRITE setFilterMode READ filterMode)
    Q_PROPERTY(QColor menuBackgroundColor WRITE setMenuBackgroundColor READ menuBackgroundColor)
    Q_PROPERTY(QColor menuTextColor WRITE setMenuTextColor READ menuTextColor)
    Q_PROPERTY(QColor menuSelectedColor WRITE setMenuSelectedColor READ menuSelectedColor)

public:
    enum FilterMode {
        StartsWithFilter,
        ContainsFilter
    };
    Q_ENUM(FilterMode)

    explicit QtMaterialAutoComplete(QWidget *parent = 0);
    ~QtMaterialAutoComplete();

    void setDataSource(const QStringList &data);
    QStringList dataSource() const;

    void setMaxVisibleItems(int value);
    int maxVisibleItems() const;

    void setCaseSensitivity(Qt::CaseSensitivity value);
    Qt::CaseSensitivity caseSensitivity() const;

    void setFilterMode(FilterMode value);
    FilterMode filterMode() const;

    void setMenuBackgroundColor(const QColor &color);
    QColor menuBackgroundColor() const;

    void setMenuTextColor(const QColor &color);
    QColor menuTextColor() const;

    void setMenuSelectedColor(const QColor &color);
    QColor menuSelectedColor() const;

signals:
    void itemSelected(QString);

protected slots:
    void updateResults(QString text);

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialAutoComplete)
    Q_DECLARE_PRIVATE(QtMaterialAutoComplete)
};

#endif // QTMATERIALAUTOCOMPLETE_H
