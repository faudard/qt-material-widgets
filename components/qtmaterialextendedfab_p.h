#ifndef QTMATERIALEXTENDEDFAB_P_H
#define QTMATERIALEXTENDEDFAB_P_H

#include <QColor>
#include <QString>

class QtMaterialExtendedFloatingActionButton;

class QtMaterialExtendedFloatingActionButtonPrivate
{
  Q_DISABLE_COPY(QtMaterialExtendedFloatingActionButtonPrivate)
  Q_DECLARE_PUBLIC(QtMaterialExtendedFloatingActionButton)

public:
  explicit QtMaterialExtendedFloatingActionButtonPrivate(QtMaterialExtendedFloatingActionButton *q);
  ~QtMaterialExtendedFloatingActionButtonPrivate();

  void init();

  QtMaterialExtendedFloatingActionButton *const q_ptr;
  QString text;
  bool collapsed;
  int labelSpacing;
  QColor textColor;
  QColor selectedColor;
};

#endif // QTMATERIALEXTENDEDFAB_P_H