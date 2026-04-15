#include "qtmaterialsegmentedbutton.h"
#include "qtmaterialsegmentedbutton_p.h"
#include "qtmaterialflatbutton.h"
#include "lib/qtmaterialstyle.h"

#include <QButtonGroup>
#include <QHBoxLayout>
#include <QResizeEvent>

QtMaterialSegmentedButtonPrivate::QtMaterialSegmentedButtonPrivate(QtMaterialSegmentedButton *q)
    : q_ptr(q),
      group(0),
      layout(0),
      useThemeColors(true),
      exclusive(true),
      showIcons(true),
      currentIndex(-1)
{
}

QtMaterialSegmentedButtonPrivate::~QtMaterialSegmentedButtonPrivate()
{
}

void QtMaterialSegmentedButtonPrivate::init()
{
    Q_Q(QtMaterialSegmentedButton);

    group = new QButtonGroup(q);
    group->setExclusive(true);

    layout = new QHBoxLayout;
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    q->setLayout(layout);
    q->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    q->setMinimumHeight(36);

    QObject::connect(group, SIGNAL(buttonClicked(int)), q, SLOT(handleButtonClicked(int)));
    QObject::connect(group, SIGNAL(buttonToggled(int,bool)), q, SLOT(handleButtonToggled(int,bool)));
}

QColor QtMaterialSegmentedButtonPrivate::resolvedBackgroundColor() const
{
    if (!useThemeColors && backgroundColor.isValid()) {
        return backgroundColor;
    }
    return QtMaterialStyle::instance().themeColor("canvas");
}

QColor QtMaterialSegmentedButtonPrivate::resolvedTextColor() const
{
    if (!useThemeColors && textColor.isValid()) {
        return textColor;
    }
    return QtMaterialStyle::instance().themeColor("text");
}

QColor QtMaterialSegmentedButtonPrivate::resolvedSelectedColor() const
{
    if (!useThemeColors && selectedColor.isValid()) {
        return selectedColor;
    }
    return QtMaterialStyle::instance().themeColor("primary1");
}

QColor QtMaterialSegmentedButtonPrivate::resolvedSelectedTextColor() const
{
    if (!useThemeColors && selectedTextColor.isValid()) {
        return selectedTextColor;
    }
    return Qt::white;
}

QColor QtMaterialSegmentedButtonPrivate::resolvedOutlineColor() const
{
    if (!useThemeColors && outlineColor.isValid()) {
        return outlineColor;
    }
    return QtMaterialStyle::instance().themeColor("border");
}

void QtMaterialSegmentedButtonPrivate::applyStyle(QtMaterialFlatButton *button, int)
{
    button->setCheckable(true);
    button->setCornerRadius(0);
    button->setHaloVisible(false);
    button->setOverlayStyle(Material::TintedOverlay);
    button->setBackgroundMode(Qt::OpaqueMode);
    button->setMinimumHeight(36);
    button->setBaseOpacity(0.0);

    button->setBackgroundColor(resolvedBackgroundColor());
    button->setForegroundColor(resolvedTextColor());
    button->setOverlayColor(resolvedSelectedColor());
    button->setDisabledForegroundColor(QtMaterialStyle::instance().themeColor("disabled"));
}

void QtMaterialSegmentedButtonPrivate::rebuild()
{
    Q_Q(QtMaterialSegmentedButton);

    while (QLayoutItem *item = layout->takeAt(0)) {
        delete item->widget();
        delete item;
    }
    delete group;
    group = new QButtonGroup(q);
    group->setExclusive(exclusive);
    QObject::connect(group, SIGNAL(buttonClicked(int)), q, SLOT(handleButtonClicked(int)));
    QObject::connect(group, SIGNAL(buttonToggled(int,bool)), q, SLOT(handleButtonToggled(int,bool)));

    for (int i = 0; i < segments.count(); ++i) {
        Segment &segment = segments[i];
        segment.button = new QtMaterialFlatButton(segment.text, q);
        if (showIcons) {
            segment.button->setIcon(segment.icon);
        }
        applyStyle(segment.button, i);
        layout->addWidget(segment.button);
        group->addButton(segment.button, i);
    }

    updateButtons();
}

void QtMaterialSegmentedButtonPrivate::updateButtons()
{
    for (int i = 0; i < segments.count(); ++i) {
        QtMaterialFlatButton *button = segments[i].button;
        if (!button) {
            continue;
        }
        button->setText(segments[i].text);
        button->setIcon(showIcons ? segments[i].icon : QIcon());
        button->setChecked(i == currentIndex);
        button->setForegroundColor(i == currentIndex ? resolvedSelectedTextColor() : resolvedTextColor());
        button->setBackgroundColor(i == currentIndex ? resolvedSelectedColor() : resolvedBackgroundColor());
        button->update();
    }
}

QtMaterialSegmentedButton::QtMaterialSegmentedButton(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialSegmentedButtonPrivate(this))
{
    d_func()->init();
}

QtMaterialSegmentedButton::~QtMaterialSegmentedButton()
{
}

void QtMaterialSegmentedButton::setUseThemeColors(bool value)
{
    Q_D(QtMaterialSegmentedButton);
    if (d->useThemeColors == value) {
        return;
    }
    d->useThemeColors = value;
    d->updateButtons();
}

bool QtMaterialSegmentedButton::useThemeColors() const
{
    Q_D(const QtMaterialSegmentedButton);
    return d->useThemeColors;
}

void QtMaterialSegmentedButton::setExclusive(bool value)
{
    Q_D(QtMaterialSegmentedButton);
    if (d->exclusive == value) {
        return;
    }
    d->exclusive = value;
    d->rebuild();
}

bool QtMaterialSegmentedButton::isExclusive() const
{
    Q_D(const QtMaterialSegmentedButton);
    return d->exclusive;
}

void QtMaterialSegmentedButton::setShowIcons(bool value)
{
    Q_D(QtMaterialSegmentedButton);
    if (d->showIcons == value) {
        return;
    }
    d->showIcons = value;
    d->updateButtons();
}

bool QtMaterialSegmentedButton::showIcons() const
{
    Q_D(const QtMaterialSegmentedButton);
    return d->showIcons;
}

void QtMaterialSegmentedButton::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialSegmentedButton);
    d->backgroundColor = color;
    d->useThemeColors = false;
    d->updateButtons();
}

QColor QtMaterialSegmentedButton::backgroundColor() const
{
    Q_D(const QtMaterialSegmentedButton);
    return d->backgroundColor;
}

void QtMaterialSegmentedButton::setTextColor(const QColor &color)
{
    Q_D(QtMaterialSegmentedButton);
    d->textColor = color;
    d->useThemeColors = false;
    d->updateButtons();
}

QColor QtMaterialSegmentedButton::textColor() const
{
    Q_D(const QtMaterialSegmentedButton);
    return d->textColor;
}

void QtMaterialSegmentedButton::setSelectedColor(const QColor &color)
{
    Q_D(QtMaterialSegmentedButton);
    d->selectedColor = color;
    d->useThemeColors = false;
    d->updateButtons();
}

QColor QtMaterialSegmentedButton::selectedColor() const
{
    Q_D(const QtMaterialSegmentedButton);
    return d->selectedColor;
}

void QtMaterialSegmentedButton::setSelectedTextColor(const QColor &color)
{
    Q_D(QtMaterialSegmentedButton);
    d->selectedTextColor = color;
    d->useThemeColors = false;
    d->updateButtons();
}

QColor QtMaterialSegmentedButton::selectedTextColor() const
{
    Q_D(const QtMaterialSegmentedButton);
    return d->selectedTextColor;
}

void QtMaterialSegmentedButton::setOutlineColor(const QColor &color)
{
    Q_D(QtMaterialSegmentedButton);
    d->outlineColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialSegmentedButton::outlineColor() const
{
    Q_D(const QtMaterialSegmentedButton);
    return d->outlineColor;
}

int QtMaterialSegmentedButton::addSegment(const QString &text, const QIcon &icon)
{
    Q_D(QtMaterialSegmentedButton);
    QtMaterialSegmentedButtonPrivate::Segment segment;
    segment.text = text;
    segment.icon = icon;
    d->segments.append(segment);
    d->rebuild();
    if (d->currentIndex < 0 && !d->segments.isEmpty()) {
        setCurrentIndex(0);
    }
    return d->segments.count() - 1;
}

void QtMaterialSegmentedButton::clearSegments()
{
    Q_D(QtMaterialSegmentedButton);
    d->segments.clear();
    d->currentIndex = -1;
    d->rebuild();
}

int QtMaterialSegmentedButton::count() const
{
    Q_D(const QtMaterialSegmentedButton);
    return d->segments.count();
}

void QtMaterialSegmentedButton::setSegmentText(int index, const QString &text)
{
    Q_D(QtMaterialSegmentedButton);
    if (index < 0 || index >= d->segments.count()) {
        return;
    }
    d->segments[index].text = text;
    d->updateButtons();
}

QString QtMaterialSegmentedButton::segmentText(int index) const
{
    Q_D(const QtMaterialSegmentedButton);
    if (index < 0 || index >= d->segments.count()) {
        return QString();
    }
    return d->segments[index].text;
}

void QtMaterialSegmentedButton::setCurrentIndex(int index)
{
    Q_D(QtMaterialSegmentedButton);
    if (index < 0 || index >= d->segments.count() || d->currentIndex == index) {
        return;
    }
    d->currentIndex = index;
    d->updateButtons();
    emit currentIndexChanged(index);
}

int QtMaterialSegmentedButton::currentIndex() const
{
    Q_D(const QtMaterialSegmentedButton);
    return d->currentIndex;
}

bool QtMaterialSegmentedButton::isSegmentChecked(int index) const
{
    Q_D(const QtMaterialSegmentedButton);
    if (index < 0 || index >= d->segments.count() || !d->segments[index].button) {
        return false;
    }
    return d->segments[index].button->isChecked();
}

void QtMaterialSegmentedButton::setSegmentChecked(int index, bool checked)
{
    Q_D(QtMaterialSegmentedButton);
    if (index < 0 || index >= d->segments.count() || !d->segments[index].button) {
        return;
    }
    d->segments[index].button->setChecked(checked);
    if (checked && d->exclusive) {
        setCurrentIndex(index);
    }
}

void QtMaterialSegmentedButton::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    update();
}

void QtMaterialSegmentedButton::handleButtonClicked(int id)
{
    Q_D(QtMaterialSegmentedButton);
    if (d->exclusive) {
        setCurrentIndex(id);
    }
    emit segmentClicked(id);
}

void QtMaterialSegmentedButton::handleButtonToggled(int id, bool checked)
{
    if (checked && isExclusive()) {
        setCurrentIndex(id);
    }
    emit segmentToggled(id, checked);
}
