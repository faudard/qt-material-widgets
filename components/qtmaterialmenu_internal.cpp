#include "qtmaterialmenu_internal.h"

#include <QAction>
#include <QMouseEvent>
#include <QPainter>

QtMaterialMenuItem::QtMaterialMenuItem(QAction *action, QWidget *parent)
    : QWidget(parent),
      m_action(action),
      m_dense(false),
      m_hovered(false),
      m_pressed(false)
{
    setMouseTracking(true);
    connect(m_action, SIGNAL(changed()), this, SLOT(updateFromAction()));
    updateFromAction();
}

QtMaterialMenuItem::~QtMaterialMenuItem()
{
}

void QtMaterialMenuItem::setDense(bool value)
{
    if (m_dense == value) {
        return;
    }

    m_dense = value;
    updateGeometry();
    update();
}

void QtMaterialMenuItem::setTextColor(const QColor &color)
{
    m_textColor = color;
    update();
}

void QtMaterialMenuItem::setSelectedColor(const QColor &color)
{
    m_selectedColor = color;
    update();
}

void QtMaterialMenuItem::setDisabledColor(const QColor &color)
{
    m_disabledColor = color;
    update();
}

QAction *QtMaterialMenuItem::action() const
{
    return m_action;
}

QSize QtMaterialMenuItem::sizeHint() const
{
    if (m_action->isSeparator()) {
        return QSize(208, 9);
    }

    return QSize(208, m_dense ? 32 : 40);
}

void QtMaterialMenuItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (m_action->isSeparator()) {
        painter.setPen(QPen(m_disabledColor, 1));
        painter.drawLine(16, height() / 2, width() - 16, height() / 2);
        return;
    }

    if (m_hovered || m_pressed) {
        painter.fillRect(rect(), m_selectedColor);
    }

    const bool enabled = m_action->isEnabled();
    const QColor textColor = enabled ? m_textColor : m_disabledColor;

    const int leftPadding = 16;
    const int iconSize = 20;
    const bool hasIcon = !m_action->icon().isNull();
    int textLeft = leftPadding;

    if (hasIcon) {
        QRect iconRect(leftPadding, (height() - iconSize) / 2, iconSize, iconSize);
        const QPixmap pixmap = m_action->icon().pixmap(iconSize, iconSize,
                                                       enabled ? QIcon::Normal : QIcon::Disabled);
        painter.drawPixmap(iconRect, pixmap);
        textLeft = iconRect.right() + 16;
    }

    painter.setPen(textColor);
    QRect textRect(textLeft, 0, width() - textLeft - 16, height());
    painter.drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, m_action->text());
}

void QtMaterialMenuItem::enterEvent(QEvent *event)
{
    QWidget::enterEvent(event);
    m_hovered = true;
    update();
}

void QtMaterialMenuItem::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);
    m_hovered = false;
    m_pressed = false;
    update();
}

void QtMaterialMenuItem::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && !m_action->isSeparator() && m_action->isEnabled()) {
        m_pressed = true;
        update();
    }

    QWidget::mousePressEvent(event);
}

void QtMaterialMenuItem::mouseReleaseEvent(QMouseEvent *event)
{
    const bool shouldTrigger = m_pressed && rect().contains(event->pos())
        && event->button() == Qt::LeftButton
        && !m_action->isSeparator()
        && m_action->isEnabled();

    m_pressed = false;
    update();

    if (shouldTrigger) {
        emit triggered(m_action);
    }

    QWidget::mouseReleaseEvent(event);
}

void QtMaterialMenuItem::updateFromAction()
{
    setVisible(m_action->isVisible());
    updateGeometry();
    update();
}
