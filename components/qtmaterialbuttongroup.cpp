#include "qtmaterialbuttongroup.h"
#include "qtmaterialbuttongroup_p.h"

#include "qtmaterialflatbutton.h"
#include "qtmaterialstyle.h"

#include <QAbstractButton>
#include <QButtonGroup>
#include <QHBoxLayout>

QtMaterialButtonGroupPrivate::QtMaterialButtonGroupPrivate(QtMaterialButtonGroup *q)
    : q_ptr(q),
      layout(0),
      group(0),
      useThemeColors(true),
      exclusive(false),
      spacing(8)
{
}

QtMaterialButtonGroupPrivate::~QtMaterialButtonGroupPrivate()
{
}

void QtMaterialButtonGroupPrivate::init()
{
    Q_Q(QtMaterialButtonGroup);

    layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(spacing);

    group = new QButtonGroup(q);
    group->setExclusive(exclusive);

    q->setLayout(layout);

    QObject::connect(group, SIGNAL(buttonClicked(QAbstractButton*)),
                     q, SLOT(handleButtonClicked(QAbstractButton*)));
    QObject::connect(group, SIGNAL(buttonToggled(QAbstractButton*,bool)),
                     q, SLOT(handleButtonToggled(QAbstractButton*,bool)));
}

QtMaterialButtonGroup::QtMaterialButtonGroup(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialButtonGroupPrivate(this))
{
    d_func()->init();
}

QtMaterialButtonGroup::~QtMaterialButtonGroup()
{
}

void QtMaterialButtonGroup::setUseThemeColors(bool value)
{
    Q_D(QtMaterialButtonGroup);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    updateButtonStyles();
}

bool QtMaterialButtonGroup::useThemeColors() const
{
    Q_D(const QtMaterialButtonGroup);

    return d->useThemeColors;
}

void QtMaterialButtonGroup::setExclusive(bool value)
{
    Q_D(QtMaterialButtonGroup);

    if (d->exclusive == value) {
        return;
    }

    d->exclusive = value;
    d->group->setExclusive(value);
}

bool QtMaterialButtonGroup::isExclusive() const
{
    Q_D(const QtMaterialButtonGroup);

    return d->exclusive;
}

void QtMaterialButtonGroup::setSpacing(int value)
{
    Q_D(QtMaterialButtonGroup);

    if (d->spacing == value) {
        return;
    }

    d->spacing = value;
    d->layout->setSpacing(value);
    updateGeometryForButtons();
}

int QtMaterialButtonGroup::spacing() const
{
    Q_D(const QtMaterialButtonGroup);

    return d->spacing;
}

void QtMaterialButtonGroup::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialButtonGroup);

    d->backgroundColor = color;
    d->useThemeColors = false;
    updateButtonStyles();
}

QColor QtMaterialButtonGroup::backgroundColor() const
{
    Q_D(const QtMaterialButtonGroup);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("canvas");
    }

    return d->backgroundColor;
}

void QtMaterialButtonGroup::setSelectedColor(const QColor &color)
{
    Q_D(QtMaterialButtonGroup);

    d->selectedColor = color;
    d->useThemeColors = false;
    updateButtonStyles();
}

QColor QtMaterialButtonGroup::selectedColor() const
{
    Q_D(const QtMaterialButtonGroup);

    if (d->useThemeColors || !d->selectedColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("primary1");
    }

    return d->selectedColor;
}

void QtMaterialButtonGroup::setTextColor(const QColor &color)
{
    Q_D(QtMaterialButtonGroup);

    d->textColor = color;
    d->useThemeColors = false;
    updateButtonStyles();
}

QColor QtMaterialButtonGroup::textColor() const
{
    Q_D(const QtMaterialButtonGroup);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("text");
    }

    return d->textColor;
}

void QtMaterialButtonGroup::setSelectedTextColor(const QColor &color)
{
    Q_D(QtMaterialButtonGroup);

    d->selectedTextColor = color;
    d->useThemeColors = false;
    updateButtonStyles();
}

QColor QtMaterialButtonGroup::selectedTextColor() const
{
    Q_D(const QtMaterialButtonGroup);

    if (d->useThemeColors || !d->selectedTextColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("canvas");
    }

    return d->selectedTextColor;
}

void QtMaterialButtonGroup::addButton(QAbstractButton *button)
{
    Q_D(QtMaterialButtonGroup);

    if (!button || d->buttons.contains(button)) {
        return;
    }

    button->setParent(this);
    button->setCheckable(true);

    d->buttons.push_back(button);
    d->group->addButton(button, d->buttons.count() - 1);
    d->layout->addWidget(button);

    updateGeometryForButtons();
    updateButtonStyles();
}

void QtMaterialButtonGroup::removeButton(QAbstractButton *button)
{
    Q_D(QtMaterialButtonGroup);

    const int index = d->buttons.indexOf(button);
    if (index < 0) {
        return;
    }

    d->group->removeButton(button);
    d->layout->removeWidget(button);
    d->buttons.removeAt(index);

    updateGeometryForButtons();
    updateButtonStyles();
}

QList<QAbstractButton *> QtMaterialButtonGroup::buttons() const
{
    Q_D(const QtMaterialButtonGroup);

    return d->buttons;
}

int QtMaterialButtonGroup::checkedIndex() const
{
    Q_D(const QtMaterialButtonGroup);

    QAbstractButton *checked = d->group->checkedButton();
    return checked ? d->buttons.indexOf(checked) : -1;
}

void QtMaterialButtonGroup::setCheckedIndex(int index)
{
    Q_D(QtMaterialButtonGroup);

    if (index < 0 || index >= d->buttons.count()) {
        return;
    }

    d->buttons.at(index)->setChecked(true);
    updateButtonStyles();
    emit checkedIndexChanged(index);
}

void QtMaterialButtonGroup::updateButtonStyles()
{
    Q_D(QtMaterialButtonGroup);

    foreach (QAbstractButton *button, d->buttons) {
        QtMaterialFlatButton *flat = qobject_cast<QtMaterialFlatButton *>(button);
        if (!flat) {
            continue;
        }

        flat->setUseThemeColors(false);
        flat->setBackgroundMode(Qt::OpaqueMode);

        if (button->isChecked()) {
            flat->setBackgroundColor(selectedColor());
            flat->setForegroundColor(selectedTextColor());
        } else {
            flat->setBackgroundColor(backgroundColor());
            flat->setForegroundColor(textColor());
        }
    }

    update();
}

void QtMaterialButtonGroup::handleButtonClicked(QAbstractButton *button)
{
    Q_D(QtMaterialButtonGroup);

    emit buttonClicked(d->buttons.indexOf(button));
}

void QtMaterialButtonGroup::handleButtonToggled(QAbstractButton *button, bool checked)
{
    Q_UNUSED(button)

    if (checked) {
        updateButtonStyles();
        emit checkedIndexChanged(checkedIndex());
    } else if (!isExclusive()) {
        updateButtonStyles();
    }
}

void QtMaterialButtonGroup::updateGeometryForButtons()
{
    Q_D(QtMaterialButtonGroup);

    for (int i = 0; i < d->buttons.count(); ++i) {
        QtMaterialFlatButton *flat = qobject_cast<QtMaterialFlatButton *>(d->buttons.at(i));
        if (!flat) {
            continue;
        }

        flat->setCornerRadius(20);
        flat->setBaseOpacity(0.08);

        if (i == 0) {
            flat->setMaximumHeight(36);
        } else {
            flat->setMaximumHeight(36);
        }
    }

    updateGeometry();
}
