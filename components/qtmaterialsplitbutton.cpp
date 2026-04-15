#include "qtmaterialsplitbutton.h"
#include "qtmaterialsplitbutton_p.h"

#include <QAction>
#include <QEvent>
#include <QMenu>
#include <QPainter>
#include <QResizeEvent>
#include <QToolButton>
#include <QStyleOption>
#include <QHBoxLayout>

QtMaterialSplitButtonPrivate::QtMaterialSplitButtonPrivate(QtMaterialSplitButton *q)
    : q_ptr(q),
      mainButton(0),
      menuButton(0),
      attachedMenu(0),
      useThemeColors(true),
      dense(false)
{
}

QtMaterialSplitButtonPrivate::~QtMaterialSplitButtonPrivate()
{
}

void QtMaterialSplitButtonPrivate::init()
{
    Q_Q(QtMaterialSplitButton);

    mainButton = new QToolButton(q);
    menuButton = new QToolButton(q);

    mainButton->setAutoRaise(true);
    menuButton->setAutoRaise(true);
    menuButton->setArrowType(Qt::DownArrow);

    QObject::connect(mainButton, SIGNAL(clicked()), q, SLOT(handleMainClicked()));
    QObject::connect(menuButton, SIGNAL(clicked()), q, SLOT(handleMenuClicked()));

    setupGeometry();
}

void QtMaterialSplitButtonPrivate::setupGeometry()
{
    if (!mainButton || !menuButton) {
        return;
    }

    const int h = dense ? 32 : 36;
    const int menuWidth = dense ? 28 : 32;

    mainButton->setGeometry(0, 0, q_ptr->width() - menuWidth, h);
    menuButton->setGeometry(q_ptr->width() - menuWidth, 0, menuWidth, h);
}

QtMaterialSplitButton::QtMaterialSplitButton(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialSplitButtonPrivate(this))
{
    Q_D(QtMaterialSplitButton);
    d->init();
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setMinimumHeight(36);
}

QtMaterialSplitButton::~QtMaterialSplitButton()
{
    delete d_ptr;
}

void QtMaterialSplitButton::setUseThemeColors(bool value)
{
    Q_D(QtMaterialSplitButton);
    if (d->useThemeColors == value) {
        return;
    }
    d->useThemeColors = value;
    update();
}

bool QtMaterialSplitButton::useThemeColors() const
{
    Q_D(const QtMaterialSplitButton);
    return d->useThemeColors;
}

void QtMaterialSplitButton::setText(const QString &text)
{
    Q_D(QtMaterialSplitButton);
    d->text = text;
    if (d->mainButton) {
        d->mainButton->setText(text);
    }
}

QString QtMaterialSplitButton::text() const
{
    Q_D(const QtMaterialSplitButton);
    return d->text;
}

void QtMaterialSplitButton::setMenu(QMenu *menu)
{
    Q_D(QtMaterialSplitButton);
    if (d->attachedMenu == menu) {
        return;
    }
    if (d->attachedMenu) {
        disconnect(d->attachedMenu, SIGNAL(triggered(QAction*)), this, SLOT(handleActionTriggered(QAction*)));
    }
    d->attachedMenu = menu;
    if (d->attachedMenu) {
        connect(d->attachedMenu, SIGNAL(triggered(QAction*)), this, SLOT(handleActionTriggered(QAction*)));
    }
}

QMenu *QtMaterialSplitButton::menu() const
{
    Q_D(const QtMaterialSplitButton);
    return d->attachedMenu;
}

void QtMaterialSplitButton::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialSplitButton);
    d->backgroundColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialSplitButton::backgroundColor() const
{
    Q_D(const QtMaterialSplitButton);
    return d->backgroundColor.isValid() ? d->backgroundColor : QColor("#EEEEEE");
}

void QtMaterialSplitButton::setTextColor(const QColor &color)
{
    Q_D(QtMaterialSplitButton);
    d->textColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialSplitButton::textColor() const
{
    Q_D(const QtMaterialSplitButton);
    return d->textColor.isValid() ? d->textColor : QColor("#212121");
}

void QtMaterialSplitButton::setMenuButtonColor(const QColor &color)
{
    Q_D(QtMaterialSplitButton);
    d->menuButtonColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialSplitButton::menuButtonColor() const
{
    Q_D(const QtMaterialSplitButton);
    return d->menuButtonColor.isValid() ? d->menuButtonColor : backgroundColor();
}

void QtMaterialSplitButton::setDividerColor(const QColor &color)
{
    Q_D(QtMaterialSplitButton);
    d->dividerColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialSplitButton::dividerColor() const
{
    Q_D(const QtMaterialSplitButton);
    return d->dividerColor.isValid() ? d->dividerColor : QColor(0, 0, 0, 40);
}

void QtMaterialSplitButton::setDense(bool value)
{
    Q_D(QtMaterialSplitButton);
    if (d->dense == value) {
        return;
    }
    d->dense = value;
    setMinimumHeight(value ? 32 : 36);
    d->setupGeometry();
    update();
}

bool QtMaterialSplitButton::isDense() const
{
    Q_D(const QtMaterialSplitButton);
    return d->dense;
}

bool QtMaterialSplitButton::eventFilter(QObject *watched, QEvent *event)
{
    return QWidget::eventFilter(watched, event);
}

void QtMaterialSplitButton::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    Q_D(QtMaterialSplitButton);
    d->setupGeometry();
}

void QtMaterialSplitButton::handleMainClicked()
{
    emit clicked();
}

void QtMaterialSplitButton::handleMenuClicked()
{
    Q_D(QtMaterialSplitButton);
    emit menuTriggered();
    if (d->attachedMenu) {
        d->attachedMenu->popup(mapToGlobal(QPoint(width(), height())));
    }
}

void QtMaterialSplitButton::handleActionTriggered(QAction *action)
{
    emit triggered(action);
}
