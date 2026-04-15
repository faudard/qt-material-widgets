#include "qtmaterialconnectedbuttongroup.h"
#include "qtmaterialconnectedbuttongroup_p.h"

#include <QButtonGroup>
#include <QHBoxLayout>
#include <QSignalBlocker>

#include "qtmaterialflatbutton.h"
#include "qtmaterialstyle.h"

QtMaterialConnectedButtonGroupPrivate::QtMaterialConnectedButtonGroupPrivate(QtMaterialConnectedButtonGroup *q)
    : q_ptr(q),
      group(0),
      layout(0),
      useThemeColors(true),
      exclusive(true),
      spacing(0)
{
}

QtMaterialConnectedButtonGroupPrivate::~QtMaterialConnectedButtonGroupPrivate()
{
}

void QtMaterialConnectedButtonGroupPrivate::init()
{
    Q_Q(QtMaterialConnectedButtonGroup);

    group = new QButtonGroup(q);
    group->setExclusive(exclusive);

    layout = new QHBoxLayout;
    layout->setSpacing(spacing);
    layout->setContentsMargins(0, 0, 0, 0);

    q->setLayout(layout);

    QObject::connect(group, SIGNAL(buttonClicked(int)), q, SIGNAL(buttonClicked(int)));
    QObject::connect(group, SIGNAL(buttonClicked(int)), q, SIGNAL(selectionChanged()));
    QObject::connect(group, SIGNAL(buttonClicked(int)), q, SIGNAL(checkedIndexChanged(int)));

    applyStyle();
}

void QtMaterialConnectedButtonGroupPrivate::applyStyle()
{
    Q_Q(QtMaterialConnectedButtonGroup);

    QColor bg = backgroundColor.isValid()
        ? backgroundColor
        : QtMaterialStyle::instance().themeColor("canvas");
    QColor sel = selectedColor.isValid()
        ? selectedColor
        : QtMaterialStyle::instance().themeColor("primary1");
    QColor fg = textColor.isValid()
        ? textColor
        : QtMaterialStyle::instance().themeColor("text");
    QColor selFg = selectedTextColor.isValid()
        ? selectedTextColor
        : Qt::white;
    QColor outline = outlineColor.isValid()
        ? outlineColor
        : QtMaterialStyle::instance().themeColor("border");

    q->setStyleSheet(QString("QtMaterialConnectedButtonGroup { background: transparent; }"));

    for (int i = 0; i < buttons.size(); ++i) {
        QtMaterialFlatButton *button = buttons.at(i);
        button->setCheckable(true);
        button->setUseThemeColors(false);
        button->setBackgroundColor(button->isChecked() ? sel : bg);
        button->setForegroundColor(button->isChecked() ? selFg : fg);
        button->setOverlayStyle(Material::TintedOverlay);
        button->setBaseOpacity(0.08);

        QString radiusStyle;
        if (i == 0 && i == buttons.size() - 1) {
            radiusStyle = "border-radius: 18px;";
        } else if (i == 0) {
            radiusStyle = "border-top-left-radius: 18px; border-bottom-left-radius: 18px; border-top-right-radius: 0px; border-bottom-right-radius: 0px;";
        } else if (i == buttons.size() - 1) {
            radiusStyle = "border-top-left-radius: 0px; border-bottom-left-radius: 0px; border-top-right-radius: 18px; border-bottom-right-radius: 18px;";
        } else {
            radiusStyle = "border-radius: 0px;";
        }

        const QString style = QString(
            "QPushButton {"
            " border: 1px solid %1;"
            " %2"
            " padding-left: 16px; padding-right: 16px; min-height: 36px;"
            "}"
        ).arg(outline.name(), radiusStyle);

        button->setStyleSheet(style);
    }
}

QtMaterialConnectedButtonGroup::QtMaterialConnectedButtonGroup(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialConnectedButtonGroupPrivate(this))
{
    d_func()->init();
}

QtMaterialConnectedButtonGroup::~QtMaterialConnectedButtonGroup()
{
}

void QtMaterialConnectedButtonGroup::setUseThemeColors(bool value)
{
    Q_D(QtMaterialConnectedButtonGroup);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    d->applyStyle();
}

bool QtMaterialConnectedButtonGroup::useThemeColors() const
{
    Q_D(const QtMaterialConnectedButtonGroup);

    return d->useThemeColors;
}

void QtMaterialConnectedButtonGroup::setExclusive(bool value)
{
    Q_D(QtMaterialConnectedButtonGroup);

    if (d->exclusive == value) {
        return;
    }

    d->exclusive = value;
    d->group->setExclusive(value);
}

bool QtMaterialConnectedButtonGroup::isExclusive() const
{
    Q_D(const QtMaterialConnectedButtonGroup);

    return d->exclusive;
}

void QtMaterialConnectedButtonGroup::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialConnectedButtonGroup);

    d->backgroundColor = color;
    d->applyStyle();
}

QColor QtMaterialConnectedButtonGroup::backgroundColor() const
{
    Q_D(const QtMaterialConnectedButtonGroup);

    return d->backgroundColor;
}

void QtMaterialConnectedButtonGroup::setSelectedColor(const QColor &color)
{
    Q_D(QtMaterialConnectedButtonGroup);

    d->selectedColor = color;
    d->applyStyle();
}

QColor QtMaterialConnectedButtonGroup::selectedColor() const
{
    Q_D(const QtMaterialConnectedButtonGroup);

    return d->selectedColor;
}

void QtMaterialConnectedButtonGroup::setTextColor(const QColor &color)
{
    Q_D(QtMaterialConnectedButtonGroup);

    d->textColor = color;
    d->applyStyle();
}

QColor QtMaterialConnectedButtonGroup::textColor() const
{
    Q_D(const QtMaterialConnectedButtonGroup);

    return d->textColor;
}

void QtMaterialConnectedButtonGroup::setSelectedTextColor(const QColor &color)
{
    Q_D(QtMaterialConnectedButtonGroup);

    d->selectedTextColor = color;
    d->applyStyle();
}

QColor QtMaterialConnectedButtonGroup::selectedTextColor() const
{
    Q_D(const QtMaterialConnectedButtonGroup);

    return d->selectedTextColor;
}

void QtMaterialConnectedButtonGroup::setOutlineColor(const QColor &color)
{
    Q_D(QtMaterialConnectedButtonGroup);

    d->outlineColor = color;
    d->applyStyle();
}

QColor QtMaterialConnectedButtonGroup::outlineColor() const
{
    Q_D(const QtMaterialConnectedButtonGroup);

    return d->outlineColor;
}

void QtMaterialConnectedButtonGroup::setSpacing(int value)
{
    Q_D(QtMaterialConnectedButtonGroup);

    if (d->spacing == value) {
        return;
    }

    d->spacing = value;
    d->layout->setSpacing(value);
}

int QtMaterialConnectedButtonGroup::spacing() const
{
    Q_D(const QtMaterialConnectedButtonGroup);

    return d->spacing;
}

QtMaterialFlatButton *QtMaterialConnectedButtonGroup::addButton(const QString &text, const QIcon &icon)
{
    Q_D(QtMaterialConnectedButtonGroup);

    QtMaterialFlatButton *button = new QtMaterialFlatButton(text, this);
    if (!icon.isNull()) {
        button->setIcon(icon);
    }

    button->setCheckable(true);
    button->setMinimumHeight(36);
    button->setMaximumHeight(36);

    d->layout->addWidget(button);
    d->group->addButton(button, d->buttons.count());
    d->buttons.append(button);

    d->applyStyle();
    return button;
}

int QtMaterialConnectedButtonGroup::count() const
{
    Q_D(const QtMaterialConnectedButtonGroup);
    return d->buttons.count();
}

QtMaterialFlatButton *QtMaterialConnectedButtonGroup::buttonAt(int index) const
{
    Q_D(const QtMaterialConnectedButtonGroup);
    return (index >= 0 && index < d->buttons.count()) ? d->buttons.at(index) : 0;
}

int QtMaterialConnectedButtonGroup::checkedIndex() const
{
    Q_D(const QtMaterialConnectedButtonGroup);
    return d->group->checkedId();
}

QList<int> QtMaterialConnectedButtonGroup::checkedIndexes() const
{
    Q_D(const QtMaterialConnectedButtonGroup);

    QList<int> result;
    for (int i = 0; i < d->buttons.count(); ++i) {
        if (d->buttons.at(i)->isChecked()) {
            result << i;
        }
    }
    return result;
}

void QtMaterialConnectedButtonGroup::setCheckedIndex(int index)
{
    Q_D(QtMaterialConnectedButtonGroup);

    if (index < 0 || index >= d->buttons.count()) {
        return;
    }

    if (d->exclusive) {
        d->buttons.at(index)->setChecked(true);
    } else {
        d->buttons.at(index)->toggle();
    }

    d->applyStyle();
    emit selectionChanged();
    emit checkedIndexChanged(checkedIndex());
}

void QtMaterialConnectedButtonGroup::clearSelection()
{
    Q_D(QtMaterialConnectedButtonGroup);

    const QSignalBlocker blocker(d->group);

    const bool exclusive = d->group->exclusive();
    d->group->setExclusive(false);
    for (int i = 0; i < d->buttons.count(); ++i) {
        d->buttons.at(i)->setChecked(false);
    }
    d->group->setExclusive(exclusive);

    d->applyStyle();
    emit selectionChanged();
    emit checkedIndexChanged(-1);
}
