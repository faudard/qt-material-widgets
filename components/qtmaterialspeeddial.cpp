#include "qtmaterialspeeddial.h"
#include "qtmaterialspeeddial_p.h"
#include "qtmaterialfab.h"
#include "lib/qtmaterialstyle.h"

#include <QResizeEvent>
#include <QPainter>
#include <QLabel>
#include <QMouseEvent>

namespace {
static const int kMargin   = 16;
static const int kMainSize = 56;
static const int kMiniSize = 40;
static const int kLabelGap = 12;
}

QtMaterialSpeedDialPrivate::QtMaterialSpeedDialPrivate()
    : useThemeColors(true)
      , expanded(false)
      , labelsVisible(true)
      , actionSpacing(12)
      , anchorCorner(Qt::BottomRightCorner)
{
}

QtMaterialSpeedDial::QtMaterialSpeedDial(QWidget *parent)
    : QWidget(parent)
      , d_ptr(new QtMaterialSpeedDialPrivate)
{
  setAttribute(Qt::WA_TransparentForMouseEvents, false);
  setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

  Q_D(QtMaterialSpeedDial);

  d->mainButton = new QtMaterialFloatingActionButton(QIcon::fromTheme("list-add"), this);
  d->mainButton->setMini(false);

  connect(d->mainButton, &QAbstractButton::clicked, this, &QtMaterialSpeedDial::toggle);

  layoutButtons();
}

QtMaterialSpeedDial::~QtMaterialSpeedDial()
{
  delete d_ptr;
}

void QtMaterialSpeedDial::layoutButtons()
{
  Q_D(QtMaterialSpeedDial);

  if (!d->mainButton) {
    return;
  }

  const bool leftAnchor = (d->anchorCorner == Qt::BottomLeftCorner ||
                           d->anchorCorner == Qt::TopLeftCorner);
  const bool topAnchor  = (d->anchorCorner == Qt::TopLeftCorner ||
                          d->anchorCorner == Qt::TopRightCorner);

  const int mainX = leftAnchor ? kMargin : width()  - kMainSize - kMargin;
  const int mainY = topAnchor  ? kMargin : height() - kMainSize - kMargin;

  d->mainButton->setGeometry(mainX, mainY, kMainSize, kMainSize);
  d->mainButton->raise();

  const int miniX = mainX + (kMainSize - kMiniSize) / 2;
  const int step  = kMainSize + d->actionSpacing;
  const int dir   = topAnchor ? +1 : -1;

  for (int i = 0; i < d->items.size(); ++i) {
    auto &item = d->items[i];
    if (!item.button) {
      continue;
    }

    const int miniY = mainY + dir * step * (i + 1);
    item.button->setGeometry(miniX, miniY, kMiniSize, kMiniSize);
    item.button->raise();

    if (item.label) {
      const QSize hint = item.label->sizeHint();
      const int labelY = miniY + (kMiniSize - hint.height()) / 2;
      const int labelX = leftAnchor
                           ? (miniX + kMiniSize + kLabelGap)
                           : (miniX - hint.width() - kLabelGap);

      item.label->setGeometry(labelX, labelY, hint.width(), hint.height());
      item.label->raise();
    }
  }
}

void QtMaterialSpeedDial::addAction(const QIcon &icon, const QString &text, const QVariant &data)
{
  Q_D(QtMaterialSpeedDial);

  QtMaterialSpeedDialPrivate::Item item;
  item.icon = icon;
  item.text = text;
  item.data = data;
  item.button = new QtMaterialFloatingActionButton(icon, this);
  item.button->setMini(true);
  item.button->hide();

  if (d->labelsVisible) {
    QLabel *label = new QLabel(text, this);
    label->hide();
    label->setObjectName(QStringLiteral("qt_material_speed_dial_label"));
    item.label = label;
  }

  const int index = d->items.size();
  connect(item.button, &QAbstractButton::clicked, this, [this, index, data]() {
    emit actionTriggered(index, data);
    close();
  });

  d->items.push_back(item);
  layoutButtons();
  update();
}

void QtMaterialSpeedDial::clearActions()
{
  Q_D(QtMaterialSpeedDial);

  for (auto &item : d->items) {
    delete item.button;
    delete item.label;
  }

  d->items.clear();
  update();
}

void QtMaterialSpeedDial::setUseThemeColors(bool value)
{
  Q_D(QtMaterialSpeedDial);
  d->useThemeColors = value;
  update();
}

bool QtMaterialSpeedDial::useThemeColors() const
{
  Q_D(const QtMaterialSpeedDial);
  return d->useThemeColors;
}

void QtMaterialSpeedDial::setBackgroundColor(const QColor &color)
{
  Q_D(QtMaterialSpeedDial);
  d->backgroundColor = color;
  update();
}

QColor QtMaterialSpeedDial::backgroundColor() const
{
  Q_D(const QtMaterialSpeedDial);
  return d->useThemeColors ? QtMaterialStyle::instance().themeColor("primary1")
                           : d->backgroundColor;
}

void QtMaterialSpeedDial::setForegroundColor(const QColor &color)
{
  Q_D(QtMaterialSpeedDial);
  d->foregroundColor = color;
  update();
}

QColor QtMaterialSpeedDial::foregroundColor() const
{
  Q_D(const QtMaterialSpeedDial);
  return d->useThemeColors ? QtMaterialStyle::instance().themeColor("canvas")
                           : d->foregroundColor;
}

void QtMaterialSpeedDial::setOverlayColor(const QColor &color)
{
  Q_D(QtMaterialSpeedDial);
  d->overlayColor = color;
  update();
}

QColor QtMaterialSpeedDial::overlayColor() const
{
  Q_D(const QtMaterialSpeedDial);
  return d->useThemeColors ? QColor(0, 0, 0, 96) : d->overlayColor;
}

void QtMaterialSpeedDial::setExpanded(bool value)
{
  Q_D(QtMaterialSpeedDial);

  if (d->expanded == value) {
    return;
  }

  d->expanded = value;

  for (auto &item : d->items) {
    if (item.button) {
      item.button->setVisible(value);
    }
    if (item.label) {
      item.label->setVisible(value && d->labelsVisible);
    }
  }

  layoutButtons();
  emit expandedChanged(value);
  update();
}

bool QtMaterialSpeedDial::isExpanded() const
{
  Q_D(const QtMaterialSpeedDial);
  return d->expanded;
}

void QtMaterialSpeedDial::setLabelsVisible(bool value)
{
  Q_D(QtMaterialSpeedDial);

  d->labelsVisible = value;

  for (auto &item : d->items) {
    if (value && !item.label) {
      QLabel *label = new QLabel(item.text, this);
      label->hide();
      label->setObjectName(QStringLiteral("qt_material_speed_dial_label"));
      item.label = label;
    }

    if (item.label) {
      item.label->setVisible(d->expanded && value);
    }
  }

  layoutButtons();
  update();
}

bool QtMaterialSpeedDial::labelsVisible() const
{
  Q_D(const QtMaterialSpeedDial);
  return d->labelsVisible;
}

void QtMaterialSpeedDial::setActionSpacing(int value)
{
  Q_D(QtMaterialSpeedDial);
  d->actionSpacing = qMax(0, value);
  layoutButtons();
  update();
}

int QtMaterialSpeedDial::actionSpacing() const
{
  Q_D(const QtMaterialSpeedDial);
  return d->actionSpacing;
}

void QtMaterialSpeedDial::setAnchorCorner(Qt::Corner corner)
{
  Q_D(QtMaterialSpeedDial);
  d->anchorCorner = corner;
  layoutButtons();
  update();
}

Qt::Corner QtMaterialSpeedDial::anchorCorner() const
{
  Q_D(const QtMaterialSpeedDial);
  return d->anchorCorner;
}

void QtMaterialSpeedDial::toggle()
{
  setExpanded(!isExpanded());
}

void QtMaterialSpeedDial::open()
{
  setExpanded(true);
}

void QtMaterialSpeedDial::close()
{
  setExpanded(false);
}

void QtMaterialSpeedDial::resizeEvent(QResizeEvent *event)
{
  QWidget::resizeEvent(event);
  layoutButtons();
}

void QtMaterialSpeedDial::paintEvent(QPaintEvent *event)
{
  Q_UNUSED(event)

  if (!isExpanded()) {
    return;
  }

  QPainter painter(this);
  painter.fillRect(rect(), overlayColor());
}