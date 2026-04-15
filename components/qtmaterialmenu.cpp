#include "qtmaterialmenu.h"
#include "qtmaterialmenu_p.h"

#include <QAction>
#include <QEvent>
#include <QVBoxLayout>

#include "qtmaterialmenu_internal.h"
#include "qtmaterialpaper.h"
#include "lib/qtmaterialstyle.h"

QtMaterialMenuPrivate::QtMaterialMenuPrivate(QtMaterialMenu *q)
    : q_ptr(q),
      paper(0),
      menuLayout(0),
      elevation(8),
      useThemeColors(true),
      dense(false)
{
}

QtMaterialMenuPrivate::~QtMaterialMenuPrivate()
{
}

void QtMaterialMenuPrivate::init()
{
    Q_Q(QtMaterialMenu);

    q->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    q->setAttribute(Qt::WA_TranslucentBackground);

    QVBoxLayout *outerLayout = new QVBoxLayout;
    outerLayout->setContentsMargins(8, 8, 8, 8);
    q->setLayout(outerLayout);

    paper = new QtMaterialPaper(q);
    menuLayout = new QVBoxLayout;
    menuLayout->setContentsMargins(0, 8, 0, 8);
    menuLayout->setSpacing(0);
    paper->setLayout(menuLayout);
    paper->setCornerRadius(4);
    paper->setElevation(elevation);

    outerLayout->addWidget(paper);

    updateMenu();
}

void QtMaterialMenuPrivate::rebuildMenu()
{
    Q_Q(QtMaterialMenu);

    qDeleteAll(items);
    items.clear();

    QLayoutItem *child;
    while ((child = menuLayout->takeAt(0)) != 0) {
        delete child;
    }

    foreach (QAction *action, actions) {
        QtMaterialMenuItem *item = new QtMaterialMenuItem(action, paper);
        QObject::connect(item, &QtMaterialMenuItem::triggered, q, &QtMaterialMenu::triggered);
        QObject::connect(item, &QtMaterialMenuItem::triggered, q, &QWidget::hide);
        QObject::connect(item, &QtMaterialMenuItem::triggered, q, [this](QAction *action) {
            handleTriggered(action);
        });
        items.append(item);
        menuLayout->addWidget(item);
    }

    updateMenu();
}

void QtMaterialMenuPrivate::updateMenu()
{
    const QColor resolvedBackground = useThemeColors || !backgroundColor.isValid()
        ? QColor(255, 255, 255)
        : backgroundColor;

    const QColor resolvedText = useThemeColors || !textColor.isValid()
        ? QColor(33, 33, 33)
        : textColor;

    const QColor resolvedSelected = useThemeColors || !selectedColor.isValid()
        ? QColor(0, 0, 0, 18)
        : selectedColor;

    const QColor resolvedDisabled = useThemeColors || !disabledColor.isValid()
        ? QtMaterialStyle::instance().themeColor("disabled")
        : disabledColor;

    paper->setUseThemeColors(false);
    paper->setBackgroundColor(resolvedBackground);
    paper->setOutlineColor(QColor(0, 0, 0, 20));
    paper->setElevation(elevation);

    foreach (QtMaterialMenuItem *item, items) {
        item->setDense(dense);
        item->setTextColor(resolvedText);
        item->setSelectedColor(resolvedSelected);
        item->setDisabledColor(resolvedDisabled);
    }
}

void QtMaterialMenuPrivate::handleTriggered(QAction *action)
{
    if (!action) {
        return;
    }

    action->trigger();
}

QtMaterialMenu::QtMaterialMenu(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialMenuPrivate(this))
{
    d_func()->init();
}

QtMaterialMenu::~QtMaterialMenu()
{
}

void QtMaterialMenu::setUseThemeColors(bool value)
{
    Q_D(QtMaterialMenu);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    d->updateMenu();
}

bool QtMaterialMenu::useThemeColors() const
{
    Q_D(const QtMaterialMenu);

    return d->useThemeColors;
}

void QtMaterialMenu::setDense(bool value)
{
    Q_D(QtMaterialMenu);

    if (d->dense == value) {
        return;
    }

    d->dense = value;
    d->updateMenu();
    adjustSize();
}

bool QtMaterialMenu::isDense() const
{
    Q_D(const QtMaterialMenu);

    return d->dense;
}

void QtMaterialMenu::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialMenu);

    d->backgroundColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    d->updateMenu();
}

QColor QtMaterialMenu::backgroundColor() const
{
    Q_D(const QtMaterialMenu);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return QColor(255, 255, 255);
    }

    return d->backgroundColor;
}

void QtMaterialMenu::setTextColor(const QColor &color)
{
    Q_D(QtMaterialMenu);

    d->textColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    d->updateMenu();
}

QColor QtMaterialMenu::textColor() const
{
    Q_D(const QtMaterialMenu);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return QColor(33, 33, 33);
    }

    return d->textColor;
}

void QtMaterialMenu::setSelectedColor(const QColor &color)
{
    Q_D(QtMaterialMenu);

    d->selectedColor = color;
    MATERIAL_DISABLE_THEME_COLORS
    d->updateMenu();
}

QColor QtMaterialMenu::selectedColor() const
{
    Q_D(const QtMaterialMenu);

    if (d->useThemeColors || !d->selectedColor.isValid()) {
        return QColor(0, 0, 0, 18);
    }

    return d->selectedColor;
}

void QtMaterialMenu::setElevation(int value)
{
    Q_D(QtMaterialMenu);

    d->elevation = qMax(0, value);
    d->updateMenu();
    updateGeometry();
}

int QtMaterialMenu::elevation() const
{
    Q_D(const QtMaterialMenu);

    return d->elevation;
}

QAction *QtMaterialMenu::addMenuItem(const QString &text)
{
    QAction *action = new QAction(text, this);
    QWidget::addAction(action);

    Q_D(QtMaterialMenu);
    d->actions.append(action);
    d->rebuildMenu();

    return action;
}

QAction *QtMaterialMenu::addMenuItem(const QIcon &icon, const QString &text)
{
    QAction *action = new QAction(icon, text, this);
    QWidget::addAction(action);

    Q_D(QtMaterialMenu);
    d->actions.append(action);
    d->rebuildMenu();

    return action;
}

QAction *QtMaterialMenu::addSeparator()
{
    QAction *action = new QAction(this);
    action->setSeparator(true);
    QWidget::addAction(action);

    Q_D(QtMaterialMenu);
    d->actions.append(action);
    d->rebuildMenu();

    return action;
}

void QtMaterialMenu::clearMenuItems()
{
    Q_D(QtMaterialMenu);

    foreach (QAction *action, d->actions) {
        QWidget::removeAction(action);
        action->deleteLater();
    }

    d->actions.clear();
    d->rebuildMenu();
}

int QtMaterialMenu::itemCount() const
{
    Q_D(const QtMaterialMenu);

    return d->actions.count();
}

void QtMaterialMenu::popup(const QPoint &pos)
{
    adjustSize();
    move(pos);
    show();
    raise();
}

bool QtMaterialMenu::event(QEvent *event)
{
    if (QEvent::WindowDeactivate == event->type()) {
        hide();
    }

    return QWidget::event(event);
}

QSize QtMaterialMenu::sizeHint() const
{
    Q_D(const QtMaterialMenu);

    int height = 16;
    foreach (QAction *action, d->actions) {
        height += action->isSeparator() ? 9 : (d->dense ? 32 : 40);
    }

    return QSize(224, height + 16);
}
