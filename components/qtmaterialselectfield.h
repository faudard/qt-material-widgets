#ifndef QTMATERIALSELECTFIELD_H
#define QTMATERIALSELECTFIELD_H

#include "qtmaterialtextfield.h"
#include <QColor>
#include <QStringList>

class QListWidget;
class QFrame;
class QtMaterialSelectFieldPrivate;

class QtMaterialSelectField : public QtMaterialTextField
{
    Q_OBJECT

    Q_PROPERTY(bool showDropdownIndicator READ showDropdownIndicator WRITE setShowDropdownIndicator)
    Q_PROPERTY(bool editableSelection READ editableSelection WRITE setEditableSelection)
    Q_PROPERTY(QColor popupBackgroundColor READ popupBackgroundColor WRITE setPopupBackgroundColor)
    Q_PROPERTY(QColor popupTextColor READ popupTextColor WRITE setPopupTextColor)
    Q_PROPERTY(QColor popupSelectedColor READ popupSelectedColor WRITE setPopupSelectedColor)

public:
    explicit QtMaterialSelectField(QWidget *parent = 0);
    ~QtMaterialSelectField();

    void setItems(const QStringList &items);
    QStringList items() const;

    void setCurrentIndex(int index);
    int currentIndex() const;

    void setCurrentText(const QString &text);
    QString currentText() const;

    void setPlaceholderOption(const QString &text);
    QString placeholderOption() const;

    void setEditableSelection(bool value);
    bool editableSelection() const;

    void setShowDropdownIndicator(bool value);
    bool showDropdownIndicator() const;

    void setPopupBackgroundColor(const QColor &color);
    QColor popupBackgroundColor() const;

    void setPopupTextColor(const QColor &color);
    QColor popupTextColor() const;

    void setPopupSelectedColor(const QColor &color);
    QColor popupSelectedColor() const;

public slots:
    void openMenu();
    void closeMenu();

signals:
    void currentIndexChanged(int index);
    void currentTextChanged(const QString &text);

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialSelectField)
    Q_DECLARE_PRIVATE(QtMaterialSelectField)
};

#endif // QTMATERIALSELECTFIELD_H
