#include "qtmaterialtoggleiconbutton.h"
#include "qtmaterialstyle.h"
#include "qtmaterialtoggleiconbutton_p.h"

#include <QPainter>

QtMaterialToggleIconButtonPrivate::QtMaterialToggleIconButtonPrivate(QtMaterialToggleIconButton *q)
    : QtMaterialIconButtonPrivate(q),
      q_ptr(q)
{
}

QtMaterialToggleIconButtonPrivate::~QtMaterialToggleIconButtonPrivate()
{
}

void QtMaterialToggleIconButtonPrivate::init()
{
    Q_Q(QtMaterialToggleIconButton);

    QtMaterialIconButtonPrivate::init();

    selectedColor = QColor();
    selectedDisabledColor = QColor();
    q->setCheckable(true);
}

QtMaterialToggleIconButton::QtMaterialToggleIconButton(const QIcon &icon, QWidget *parent)
    : QtMaterialIconButton(*new QtMaterialToggleIconButtonPrivate(this), parent),
      d_ptr(static_cast<QtMaterialToggleIconButtonPrivate *>(QtMaterialIconButton::d_ptr.data()))
{
    setIcon(icon);
    d_func()->init();
}

QtMaterialToggleIconButton::QtMaterialToggleIconButton(QtMaterialToggleIconButtonPrivate &d, const QIcon &icon, QWidget *parent)
    : QtMaterialIconButton(d, parent),
      d_ptr(&d)
{
    setIcon(icon);
    d_func()->init();
}

QtMaterialToggleIconButton::~QtMaterialToggleIconButton()
{
}

void QtMaterialToggleIconButton::setSelectedIcon(const QIcon &icon)
{
    Q_D(QtMaterialToggleIconButton);
    d->selectedIcon = icon;
    update();
}

QIcon QtMaterialToggleIconButton::selectedIcon() const
{
    Q_D(const QtMaterialToggleIconButton);
    return d->selectedIcon;
}

void QtMaterialToggleIconButton::setSelectedColor(const QColor &color)
{
    Q_D(QtMaterialToggleIconButton);
    d->selectedColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialToggleIconButton::selectedColor() const
{
    Q_D(const QtMaterialToggleIconButton);

    if (d->useThemeColors || !d->selectedColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("primary1");
    }

    return d->selectedColor;
}

void QtMaterialToggleIconButton::setSelectedDisabledColor(const QColor &color)
{
    Q_D(QtMaterialToggleIconButton);
    d->selectedDisabledColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialToggleIconButton::selectedDisabledColor() const
{
    Q_D(const QtMaterialToggleIconButton);

    if (d->useThemeColors || !d->selectedDisabledColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("disabled");
    }

    return d->selectedDisabledColor;
}

void QtMaterialToggleIconButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialToggleIconButton);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QIcon drawIcon = icon();
    QColor drawColor = color();

    if (isChecked()) {
        if (!d->selectedIcon.isNull()) {
            drawIcon = d->selectedIcon;
        }
        drawColor = isEnabled() ? selectedColor() : selectedDisabledColor();
    } else if (!isEnabled()) {
        drawColor = disabledColor();
    }

    const QSize iconSize(24, 24);
    const QRect iconRect = QRect(QPoint(0, 0), iconSize).translated(rect().center() - QPoint(iconSize.width() / 2, iconSize.height() / 2));

    painter.setOpacity(isEnabled() ? 1.0 : 0.7);
    drawIcon.paint(&painter, iconRect, Qt::AlignCenter, isEnabled() ? QIcon::Normal : QIcon::Disabled,
                   isChecked() ? QIcon::On : QIcon::Off);

    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(iconRect.adjusted(-2, -2, 2, 2), drawColor);
}
