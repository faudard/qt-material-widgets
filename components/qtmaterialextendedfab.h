#ifndef QTMATERIALEXTENDEDFAB_H
#define QTMATERIALEXTENDEDFAB_H

#include <QScopedPointer>
#include "qtmaterialfab.h"

class QtMaterialExtendedFloatingActionButtonPrivate;

class QtMaterialExtendedFloatingActionButton : public QtMaterialFloatingActionButton
{
  Q_OBJECT

  Q_PROPERTY(QString text READ text WRITE setText)
  Q_PROPERTY(bool collapsed READ isCollapsed WRITE setCollapsed)
  Q_PROPERTY(bool checkable READ isCheckable WRITE setCheckable)
  Q_PROPERTY(bool checked READ isChecked WRITE setChecked)
  Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
  Q_PROPERTY(QColor selectedColor READ selectedColor WRITE setSelectedColor)

public:
  explicit QtMaterialExtendedFloatingActionButton(const QIcon &icon = QIcon(),
                                                  const QString &text = QString(),
                                                  QWidget *parent = 0);
  ~QtMaterialExtendedFloatingActionButton();

  void setText(const QString &text);
  QString text() const;

  void setCollapsed(bool state);
  bool isCollapsed() const;

  void setTextColor(const QColor &color);
  QColor textColor() const;

  void setSelectedColor(const QColor &color);
  QColor selectedColor() const;

  void setLabelSpacing(int value);
  int labelSpacing() const;

  QSize sizeHint() const Q_DECL_OVERRIDE;

signals:
  void collapsedChanged(bool state);

protected:
  void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
  Q_DISABLE_COPY(QtMaterialExtendedFloatingActionButton)
  Q_DECLARE_PRIVATE(QtMaterialExtendedFloatingActionButton)
  const QScopedPointer<QtMaterialExtendedFloatingActionButtonPrivate> d_ptr;
};

#endif // QTMATERIALEXTENDEDFAB_H