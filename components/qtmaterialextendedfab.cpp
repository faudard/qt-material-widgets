#include "qtmaterialextendedfab.h"
#include "qtmaterialextendedfab_p.h"
#include "lib/qtmaterialstyle.h"

#include <QPainter>

QtMaterialExtendedFloatingActionButtonPrivate::QtMaterialExtendedFloatingActionButtonPrivate(
  QtMaterialExtendedFloatingActionButton *q)
    : q_ptr(q)
      , collapsed(false)
      , labelSpacing(12)
{
}

QtMaterialExtendedFloatingActionButtonPrivate::~QtMaterialExtendedFloatingActionButtonPrivate()
{
}

void QtMaterialExtendedFloatingActionButtonPrivate::init()
{
  Q_Q(QtMaterialExtendedFloatingActionButton);

  text.clear();
  textColor = QColor();
  selectedColor = QColor();
  q->setFixedHeight(56);
}

QtMaterialExtendedFloatingActionButton::QtMaterialExtendedFloatingActionButton(
  const QIcon &icon,
  const QString &text,
  QWidget *parent)
    : QtMaterialFloatingActionButton(icon, parent)
      , d_ptr(new QtMaterialExtendedFloatingActionButtonPrivate(this))
{
  Q_D(QtMaterialExtendedFloatingActionButton);
  d->init();
  d->text = text;
  setCheckable(false);
}

QtMaterialExtendedFloatingActionButton::~QtMaterialExtendedFloatingActionButton()
{
}

void QtMaterialExtendedFloatingActionButton::setText(const QString &text)
{
  Q_D(QtMaterialExtendedFloatingActionButton);
  if (d->text == text) {
    return;
  }
  d->text = text;
  updateGeometry();
  update();
}

QString QtMaterialExtendedFloatingActionButton::text() const
{
  Q_D(const QtMaterialExtendedFloatingActionButton);
  return d->text;
}

void QtMaterialExtendedFloatingActionButton::setCollapsed(bool state)
{
  Q_D(QtMaterialExtendedFloatingActionButton);
  if (d->collapsed == state) {
    return;
  }
  d->collapsed = state;
  updateGeometry();
  update();
  emit collapsedChanged(state);
}

bool QtMaterialExtendedFloatingActionButton::isCollapsed() const
{
  Q_D(const QtMaterialExtendedFloatingActionButton);
  return d->collapsed;
}

void QtMaterialExtendedFloatingActionButton::setTextColor(const QColor &color)
{
  Q_D(QtMaterialExtendedFloatingActionButton);
  d->textColor = color;
  setUseThemeColors(false);
  update();
}

QColor QtMaterialExtendedFloatingActionButton::textColor() const
{
  Q_D(const QtMaterialExtendedFloatingActionButton);
  if (useThemeColors() || !d->textColor.isValid()) {
    return QtMaterialStyle::instance().themeColor("canvas");
  }
  return d->textColor;
}

void QtMaterialExtendedFloatingActionButton::setSelectedColor(const QColor &color)
{
  Q_D(QtMaterialExtendedFloatingActionButton);
  d->selectedColor = color;
  setUseThemeColors(false);
  update();
}

QColor QtMaterialExtendedFloatingActionButton::selectedColor() const
{
  Q_D(const QtMaterialExtendedFloatingActionButton);
  if (useThemeColors() || !d->selectedColor.isValid()) {
    return QtMaterialStyle::instance().themeColor("accent1");
  }
  return d->selectedColor;
}

void QtMaterialExtendedFloatingActionButton::setLabelSpacing(int value)
{
  Q_D(QtMaterialExtendedFloatingActionButton);
  d->labelSpacing = qMax(0, value);
  updateGeometry();
  update();
}

int QtMaterialExtendedFloatingActionButton::labelSpacing() const
{
  Q_D(const QtMaterialExtendedFloatingActionButton);
  return d->labelSpacing;
}

QSize QtMaterialExtendedFloatingActionButton::sizeHint() const
{
  Q_D(const QtMaterialExtendedFloatingActionButton);
  if (d->collapsed || d->text.isEmpty()) {
    return QSize(56, 56);
  }

  QFontMetrics fm(font());
  const int textWidth = fm.horizontalAdvance(d->text);
  return QSize(56 + d->labelSpacing + textWidth + 24, 56);
}

void QtMaterialExtendedFloatingActionButton::paintEvent(QPaintEvent *event)
{
  Q_UNUSED(event)

  Q_D(QtMaterialExtendedFloatingActionButton);

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  QColor background = backgroundColor();
  if (isCheckable() && isChecked()) {
    background = selectedColor();
  }

  painter.setPen(Qt::NoPen);
  painter.setBrush(background);
  painter.drawRoundedRect(rect().adjusted(0, 0, -1, -1), 28, 28);

  const QRect iconRect(16, (height() - 24) / 2, 24, 24);
  icon().paint(&painter, iconRect);

  if (!d->collapsed && !d->text.isEmpty()) {
    painter.setPen(textColor());
    painter.drawText(QRect(iconRect.right() + d->labelSpacing, 0,
                           width() - iconRect.right() - d->labelSpacing - 16, height()),
                     Qt::AlignVCenter | Qt::AlignLeft,
                     d->text);
  }
}