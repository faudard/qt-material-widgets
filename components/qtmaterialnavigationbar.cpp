#include "qtmaterialnavigationbar.h"
#include "qtmaterialnavigationbar_p.h"

#include <QPainter>
#include <QResizeEvent>
#include <QStyleOption>
#include <QtMath>

QtMaterialNavigationItem::QtMaterialNavigationItem(QWidget *parent)
    : QAbstractButton(parent),
      m_shifting(false),
      m_labelsVisible(true),
      m_itemIndex(-1)
{
    setCheckable(true);
    setCursor(Qt::PointingHandCursor);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

QtMaterialNavigationItem::~QtMaterialNavigationItem()
{
}

void QtMaterialNavigationItem::setTextColor(const QColor &color)
{
    m_textColor = color;
    update();
}

QColor QtMaterialNavigationItem::textColor() const
{
    return m_textColor;
}

void QtMaterialNavigationItem::setSelectedColor(const QColor &color)
{
    m_selectedColor = color;
    update();
}

QColor QtMaterialNavigationItem::selectedColor() const
{
    return m_selectedColor;
}

void QtMaterialNavigationItem::setRippleColor(const QColor &color)
{
    m_rippleColor = color;
    update();
}

QColor QtMaterialNavigationItem::rippleColor() const
{
    return m_rippleColor;
}

void QtMaterialNavigationItem::setShifting(bool value)
{
    m_shifting = value;
    updateGeometry();
    update();
}

bool QtMaterialNavigationItem::isShifting() const
{
    return m_shifting;
}

void QtMaterialNavigationItem::setLabelsVisible(bool value)
{
    m_labelsVisible = value;
    updateGeometry();
    update();
}

bool QtMaterialNavigationItem::labelsVisible() const
{
    return m_labelsVisible;
}

void QtMaterialNavigationItem::setItemIndex(int value)
{
    m_itemIndex = value;
}

int QtMaterialNavigationItem::itemIndex() const
{
    return m_itemIndex;
}

void QtMaterialNavigationItem::setItemData(const QVariant &value)
{
    m_itemData = value;
}

QVariant QtMaterialNavigationItem::itemData() const
{
    return m_itemData;
}

void QtMaterialNavigationItem::setIcon(const QIcon &icon)
{
    m_icon = icon;
    update();
}

QIcon QtMaterialNavigationItem::icon() const
{
    return m_icon;
}

QSize QtMaterialNavigationItem::sizeHint() const
{
    return QSize(96, 56);
}

void QtMaterialNavigationItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const QRect r = rect();
    const bool active = isChecked();
    const QColor fg = active ? m_selectedColor : m_textColor;

    if (active) {
        QColor fill = m_selectedColor;
        fill.setAlpha(24);
        painter.setPen(Qt::NoPen);
        painter.setBrush(fill);
        painter.drawRoundedRect(r.adjusted(8, 6, -8, -6), 12, 12);
    }

    QRect iconRect(r.left(), r.top() + 8, r.width(), 24);
    if (!m_labelsVisible && !active && m_shifting) {
        iconRect.translate(0, 6);
    } else if (active && m_shifting) {
        iconRect.translate(0, -2);
    }

    if (!m_icon.isNull()) {
        const QSize iconSize(24, 24);
        const QPixmap pix = m_icon.pixmap(iconSize);
        QPoint p(iconRect.center().x() - iconSize.width() / 2,
                 iconRect.center().y() - iconSize.height() / 2);
        painter.drawPixmap(p, pix);
        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        painter.fillRect(QRect(p, iconSize), fg);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    }

    const bool drawLabel = m_labelsVisible || active || !m_shifting;
    if (drawLabel) {
        QFont f = font();
        f.setPointSize(active ? 10 : 9);
        f.setBold(active);
        painter.setFont(f);
        painter.setPen(fg);
        QRect textRect(r.left() + 4, r.bottom() - 24, r.width() - 8, 18);
        painter.drawText(textRect, Qt::AlignCenter | Qt::TextSingleLine, text());
    }
}

QtMaterialNavigationBarPrivate::QtMaterialNavigationBarPrivate(QtMaterialNavigationBar *q)
    : q_ptr(q),
      layout(0),
      useThemeColors(true),
      shifting(false),
      labelsVisible(true),
      currentIndex(-1)
{
}

QtMaterialNavigationBarPrivate::~QtMaterialNavigationBarPrivate()
{
}

void QtMaterialNavigationBarPrivate::init()
{
    Q_Q(QtMaterialNavigationBar);

    layout = new QHBoxLayout;
    layout->setContentsMargins(8, 4, 8, 4);
    layout->setSpacing(4);

    q->setLayout(layout);
    q->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    q->setMinimumHeight(56);

    backgroundColor = QColor("#ffffff");
    textColor = QColor("#6b6f76");
    selectedColor = QColor("#3f51b5");
    rippleColor = QColor("#3f51b5");
}

void QtMaterialNavigationBarPrivate::setupItems()
{
    for (int i = 0; i < items.size(); ++i) {
        QtMaterialNavigationItem *item = items.at(i);
        item->setItemIndex(i);
        item->setShifting(shifting);
        item->setLabelsVisible(labelsVisible);
    }
}

void QtMaterialNavigationBarPrivate::updateItemStyles()
{
    for (int i = 0; i < items.size(); ++i) {
        QtMaterialNavigationItem *item = items.at(i);
        item->setTextColor(textColor);
        item->setSelectedColor(selectedColor);
        item->setRippleColor(rippleColor);
        item->setShifting(shifting);
        item->setLabelsVisible(labelsVisible);
        item->setChecked(i == currentIndex);
        item->updateGeometry();
        item->update();
    }
}

QtMaterialNavigationBar::QtMaterialNavigationBar(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialNavigationBarPrivate(this))
{
    Q_D(QtMaterialNavigationBar);
    d->init();
}

QtMaterialNavigationBar::~QtMaterialNavigationBar()
{
}

void QtMaterialNavigationBar::setUseThemeColors(bool value)
{
    Q_D(QtMaterialNavigationBar);
    d->useThemeColors = value;
    update();
}

bool QtMaterialNavigationBar::useThemeColors() const
{
    Q_D(const QtMaterialNavigationBar);
    return d->useThemeColors;
}

void QtMaterialNavigationBar::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialNavigationBar);
    d->backgroundColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialNavigationBar::backgroundColor() const
{
    Q_D(const QtMaterialNavigationBar);
    return d->backgroundColor;
}

void QtMaterialNavigationBar::setTextColor(const QColor &color)
{
    Q_D(QtMaterialNavigationBar);
    d->textColor = color;
    d->useThemeColors = false;
    d->updateItemStyles();
}

QColor QtMaterialNavigationBar::textColor() const
{
    Q_D(const QtMaterialNavigationBar);
    return d->textColor;
}

void QtMaterialNavigationBar::setSelectedColor(const QColor &color)
{
    Q_D(QtMaterialNavigationBar);
    d->selectedColor = color;
    d->useThemeColors = false;
    d->updateItemStyles();
}

QColor QtMaterialNavigationBar::selectedColor() const
{
    Q_D(const QtMaterialNavigationBar);
    return d->selectedColor;
}

void QtMaterialNavigationBar::setRippleColor(const QColor &color)
{
    Q_D(QtMaterialNavigationBar);
    d->rippleColor = color;
    d->useThemeColors = false;
    d->updateItemStyles();
}

QColor QtMaterialNavigationBar::rippleColor() const
{
    Q_D(const QtMaterialNavigationBar);
    return d->rippleColor;
}

void QtMaterialNavigationBar::setShifting(bool value)
{
    Q_D(QtMaterialNavigationBar);
    d->shifting = value;
    d->setupItems();
    d->updateItemStyles();
}

bool QtMaterialNavigationBar::isShifting() const
{
    Q_D(const QtMaterialNavigationBar);
    return d->shifting;
}

void QtMaterialNavigationBar::setLabelsVisible(bool value)
{
    Q_D(QtMaterialNavigationBar);
    d->labelsVisible = value;
    d->setupItems();
    d->updateItemStyles();
}

bool QtMaterialNavigationBar::labelsVisible() const
{
    Q_D(const QtMaterialNavigationBar);
    return d->labelsVisible;
}

int QtMaterialNavigationBar::addItem(const QString &text, const QIcon &icon, const QVariant &data)
{
    Q_D(QtMaterialNavigationBar);

    QtMaterialNavigationItem *item = new QtMaterialNavigationItem(this);
    item->setText(text);
    item->setIcon(icon);
    item->setItemData(data);
    item->setItemIndex(d->items.size());

    d->layout->addWidget(item);
    d->items.append(item);

    connect(item, &QAbstractButton::clicked, this, [this, item]() {
        setCurrentIndex(item->itemIndex());
        emit itemTriggered(item->itemIndex());
    });

    if (d->currentIndex < 0) {
        d->currentIndex = 0;
    }

    d->setupItems();
    d->updateItemStyles();
    updateGeometry();
    return item->itemIndex();
}

int QtMaterialNavigationBar::count() const
{
    Q_D(const QtMaterialNavigationBar);
    return d->items.count();
}

void QtMaterialNavigationBar::setCurrentIndex(int index)
{
    Q_D(QtMaterialNavigationBar);

    if (index < 0 || index >= d->items.size() || d->currentIndex == index) {
        return;
    }

    d->currentIndex = index;
    d->updateItemStyles();
    emit currentChanged(index);
}

int QtMaterialNavigationBar::currentIndex() const
{
    Q_D(const QtMaterialNavigationBar);
    return d->currentIndex;
}

QVariant QtMaterialNavigationBar::itemData(int index) const
{
    Q_D(const QtMaterialNavigationBar);
    if (index < 0 || index >= d->items.size()) {
        return QVariant();
    }
    return d->items.at(index)->itemData();
}

void QtMaterialNavigationBar::setItemEnabled(int index, bool value)
{
    Q_D(QtMaterialNavigationBar);
    if (index < 0 || index >= d->items.size()) {
        return;
    }
    d->items.at(index)->setEnabled(value);
    d->items.at(index)->update();
}

bool QtMaterialNavigationBar::isItemEnabled(int index) const
{
    Q_D(const QtMaterialNavigationBar);
    if (index < 0 || index >= d->items.size()) {
        return false;
    }
    return d->items.at(index)->isEnabled();
}

QSize QtMaterialNavigationBar::sizeHint() const
{
    return QSize(360, 64);
}

void QtMaterialNavigationBar::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    update();
}
