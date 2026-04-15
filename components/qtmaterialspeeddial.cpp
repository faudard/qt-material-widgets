#include "qtmaterialspeeddial.h"
#include "qtmaterialspeeddial_p.h"
#include "qtmaterialfab.h"
#include "lib/qtmaterialstyle.h"

#include <QResizeEvent>
#include <QPainter>
#include <QLabel>
#include <QVBoxLayout>

QtMaterialSpeedDialPrivate::QtMaterialSpeedDialPrivate()
    : useThemeColors(true)
    , expanded(false)
    , labelsVisible(true)
    , actionSpacing(12)
    , anchorCorner(Qt::BottomRightCorner)
{
}

QtMaterialSpeedDial::~QtMaterialSpeedDial()
{
    delete d_ptr;
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

void QtMaterialSpeedDial::setUseThemeColors(bool value) { Q_D(QtMaterialSpeedDial); d->useThemeColors = value; update(); }
bool QtMaterialSpeedDial::useThemeColors() const { Q_D(const QtMaterialSpeedDial); return d->useThemeColors; }

void QtMaterialSpeedDial::setBackgroundColor(const QColor &color) { Q_D(QtMaterialSpeedDial); d->backgroundColor = color; update(); }
QColor QtMaterialSpeedDial::backgroundColor() const {
    Q_D(const QtMaterialSpeedDial);
    return d->useThemeColors ? QtMaterialStyle::instance().themeColor("primary1") : d->backgroundColor;
}

void QtMaterialSpeedDial::setForegroundColor(const QColor &color) { Q_D(QtMaterialSpeedDial); d->foregroundColor = color; update(); }
QColor QtMaterialSpeedDial::foregroundColor() const {
    Q_D(const QtMaterialSpeedDial);
    return d->useThemeColors ? QtMaterialStyle::instance().themeColor("canvas") : d->foregroundColor;
}

void QtMaterialSpeedDial::setOverlayColor(const QColor &color) { Q_D(QtMaterialSpeedDial); d->overlayColor = color; update(); }
QColor QtMaterialSpeedDial::overlayColor() const {
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
        if (item.button) item.button->setVisible(value);
        if (item.label) item.label->setVisible(value && d->labelsVisible);
    }
    emit expandedChanged(value);
    update();
}

bool QtMaterialSpeedDial::isExpanded() const { Q_D(const QtMaterialSpeedDial); return d->expanded; }

void QtMaterialSpeedDial::setLabelsVisible(bool value)
{
    Q_D(QtMaterialSpeedDial);
    d->labelsVisible = value;
    for (auto &item : d->items) {
        if (item.label) {
            item.label->setVisible(d->expanded && value);
        }
    }
    update();
}

bool QtMaterialSpeedDial::labelsVisible() const { Q_D(const QtMaterialSpeedDial); return d->labelsVisible; }

void QtMaterialSpeedDial::setActionSpacing(int value) { Q_D(QtMaterialSpeedDial); d->actionSpacing = qMax(0, value); update(); }
int QtMaterialSpeedDial::actionSpacing() const { Q_D(const QtMaterialSpeedDial); return d->actionSpacing; }

void QtMaterialSpeedDial::setAnchorCorner(Qt::Corner corner) { Q_D(QtMaterialSpeedDial); d->anchorCorner = corner; update(); }
Qt::Corner QtMaterialSpeedDial::anchorCorner() const { Q_D(const QtMaterialSpeedDial); return d->anchorCorner; }

void QtMaterialSpeedDial::toggle() { setExpanded(!isExpanded()); }
void QtMaterialSpeedDial::open() { setExpanded(true); }
void QtMaterialSpeedDial::close() { setExpanded(false); }

void QtMaterialSpeedDial::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    Q_D(QtMaterialSpeedDial);

    const int margin = 16;
    const int baseSize = 56;
    int x = width() - baseSize - margin;
    int y = height() - baseSize - margin;

    if (d->anchorCorner == Qt::BottomLeftCorner) {
        x = margin;
    } else if (d->anchorCorner == Qt::TopLeftCorner) {
        x = margin;
        y = margin;
    } else if (d->anchorCorner == Qt::TopRightCorner) {
        y = margin;
    }

    d->mainButton->setGeometry(x, y, baseSize, baseSize);

    int offset = baseSize + d->actionSpacing;
    for (int i = 0; i < d->items.size(); ++i) {
        auto &item = d->items[i];
        if (!item.button) continue;

        int bx = x + 8;
        int by = y - offset * (i + 1);
        if (d->anchorCorner == Qt::TopLeftCorner || d->anchorCorner == Qt::TopRightCorner) {
            by = y + offset * (i + 1);
        }
        item.button->setGeometry(bx, by, 40, 40);

        if (item.label) {
            const QSize hint = item.label->sizeHint();
            item.label->setGeometry(bx - hint.width() - 12, by + 8, hint.width(), hint.height());
        }
    }
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
