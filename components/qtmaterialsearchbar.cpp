#include "qtmaterialsearchbar.h"
#include "qtmaterialsearchbar_p.h"

#include <QAction>
#include <QEvent>
#include <QFrame>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QResizeEvent>
#include <QToolButton>
#include <QTimer>
#include <qstyle.h>

#include "qtmaterialsearchfield.h"

QtMaterialSearchBarPrivate::QtMaterialSearchBarPrivate(QtMaterialSearchBar *q)
    : q_ptr(q),
      field(0),
      surface(0),
      leadingButton(0),
      clearButton(0),
      layout(0),
      inputLayout(0),
      useThemeColors(true),
      active(true),
      collapsible(false),
      showLeadingNavigationIcon(true),
      showTrailingActions(true),
      searchDelay(250)
{
}

QtMaterialSearchBarPrivate::~QtMaterialSearchBarPrivate()
{
}

void QtMaterialSearchBarPrivate::init()
{
  Q_Q(QtMaterialSearchBar);

  layout = new QHBoxLayout(q);
  layout->setContentsMargins(12, 8, 12, 8);
  layout->setSpacing(8);

  leadingButton = new QToolButton(q);
  leadingButton->setAutoRaise(true);
  leadingButton->setToolTip("Navigation");
  leadingButton->setIcon(q->style()->standardIcon(QStyle::SP_ArrowBack));

  clearButton = new QToolButton(q);
  clearButton->setAutoRaise(true);
  clearButton->setToolTip("Clear");
  clearButton->setIcon(q->style()->standardIcon(QStyle::SP_LineEditClearButton));

  field = new QtMaterialSearchField(q);
  field->setPlaceholderText("Search");
  field->setShowLabel(false);
  field->setShowInputLine(false);
  field->setShowSearchIcon(false);
  field->setShowClearButton(false);
  field->installEventFilter(q);

  layout->addWidget(leadingButton);
  layout->addWidget(field, 1);
  layout->addWidget(clearButton);

  q->setLayout(layout);
  q->setMinimumHeight(56);

  QObject::connect(field, SIGNAL(textChanged(QString)), q, SIGNAL(textChanged(QString)));
  QObject::connect(field, SIGNAL(cleared()), q, SIGNAL(cleared()));
  QObject::connect(field, SIGNAL(searchRequested(QString)), q, SIGNAL(searchRequested(QString)));
  QObject::connect(clearButton, SIGNAL(clicked(bool)), q, SLOT(clear()));
  QObject::connect(leadingButton, SIGNAL(clicked(bool)), q, SLOT(collapse()));

  QObject::connect(field, &QLineEdit::textChanged, q, [this](const QString &) {
    updateVisibility();
  });

  updateColors();
  updateVisibility();
}

void QtMaterialSearchBarPrivate::updateColors()
{
  Q_Q(QtMaterialSearchBar);

  q->setStyleSheet(QString(
                     "QtMaterialSearchBar {"
                     " background: %1;"
                     " border: none;"
                     " border-bottom: 1px solid %2;"
                     "}"
                     "QToolButton {"
                     " background: transparent;"
                     " border: none;"
                     " padding: 0px;"
                     "}"
                     ).arg(backgroundColor.name(), dividerColor.name()));

  field->setUseThemeColors(false);
  field->setTextColor(textColor);
  field->setLabelColor(placeholderColor);
  field->setIconColor(iconColor);
}

void QtMaterialSearchBarPrivate::updateVisibility()
{
  leadingButton->setVisible(showLeadingNavigationIcon);
  clearButton->setVisible(active && showTrailingActions && !field->text().isEmpty());
}

QtMaterialSearchBar::QtMaterialSearchBar(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialSearchBarPrivate(this))
{
    Q_D(QtMaterialSearchBar);
    d->init();
}

QtMaterialSearchBar::~QtMaterialSearchBar()
{
}

void QtMaterialSearchBar::setUseThemeColors(bool value)
{
    Q_D(QtMaterialSearchBar);
    d->useThemeColors = value;
    if (value) {
        d->backgroundColor = QColor("#FAFAFA");
        d->textColor = QColor("#212121");
        d->placeholderColor = QColor("#757575");
        d->iconColor = QColor("#616161");
        d->dividerColor = QColor("#E0E0E0");
    }
    d->updateColors();
}

bool QtMaterialSearchBar::useThemeColors() const
{
    Q_D(const QtMaterialSearchBar);
    return d->useThemeColors;
}

void QtMaterialSearchBar::setPlaceholderText(const QString &text)
{
    Q_D(QtMaterialSearchBar);
    d->placeholderText = text;
    d->field->setPlaceholderText(text);
}

QString QtMaterialSearchBar::placeholderText() const
{
    Q_D(const QtMaterialSearchBar);
    return d->field->placeholderText();
}

void QtMaterialSearchBar::setActive(bool value)
{
    Q_D(QtMaterialSearchBar);
    if (d->active == value) {
        return;
    }
    d->active = value;
    d->updateVisibility();
    if (value) {
        emit activated();
    } else {
        emit collapsed();
    }
}

bool QtMaterialSearchBar::isActive() const
{
    Q_D(const QtMaterialSearchBar);
    return d->active;
}

void QtMaterialSearchBar::setCollapsible(bool value)
{
    Q_D(QtMaterialSearchBar);
    d->collapsible = value;
}

bool QtMaterialSearchBar::isCollapsible() const
{
    Q_D(const QtMaterialSearchBar);
    return d->collapsible;
}

void QtMaterialSearchBar::setShowLeadingNavigationIcon(bool value)
{
    Q_D(QtMaterialSearchBar);
    d->showLeadingNavigationIcon = value;
    d->updateVisibility();
}

bool QtMaterialSearchBar::showLeadingNavigationIcon() const
{
    Q_D(const QtMaterialSearchBar);
    return d->showLeadingNavigationIcon;
}

void QtMaterialSearchBar::setShowTrailingActions(bool value)
{
  Q_D(QtMaterialSearchBar);
  d->showTrailingActions = value;
  d->updateVisibility();
}

bool QtMaterialSearchBar::showTrailingActions() const
{
    Q_D(const QtMaterialSearchBar);
    return d->showTrailingActions;
}

void QtMaterialSearchBar::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialSearchBar);
    d->backgroundColor = color;
    d->useThemeColors = false;
    d->updateColors();
}

QColor QtMaterialSearchBar::backgroundColor() const
{
    Q_D(const QtMaterialSearchBar);
    return d->backgroundColor;
}

void QtMaterialSearchBar::setTextColor(const QColor &color)
{
    Q_D(QtMaterialSearchBar);
    d->textColor = color;
    d->useThemeColors = false;
}

QColor QtMaterialSearchBar::textColor() const
{
    Q_D(const QtMaterialSearchBar);
    return d->textColor;
}

void QtMaterialSearchBar::setPlaceholderColor(const QColor &color)
{
    Q_D(QtMaterialSearchBar);
    d->placeholderColor = color;
    d->useThemeColors = false;
}

QColor QtMaterialSearchBar::placeholderColor() const
{
    Q_D(const QtMaterialSearchBar);
    return d->placeholderColor;
}

void QtMaterialSearchBar::setIconColor(const QColor &color)
{
    Q_D(QtMaterialSearchBar);
    d->iconColor = color;
    d->useThemeColors = false;
}

QColor QtMaterialSearchBar::iconColor() const
{
    Q_D(const QtMaterialSearchBar);
    return d->iconColor;
}

void QtMaterialSearchBar::setDividerColor(const QColor &color)
{
    Q_D(QtMaterialSearchBar);
    d->dividerColor = color;
    d->useThemeColors = false;
    d->updateColors();
}

QColor QtMaterialSearchBar::dividerColor() const
{
    Q_D(const QtMaterialSearchBar);
    return d->dividerColor;
}

void QtMaterialSearchBar::setSuggestions(const QStringList &suggestions)
{
    Q_D(QtMaterialSearchBar);
    d->suggestions = suggestions;
    d->suggestions = suggestions;
}

QStringList QtMaterialSearchBar::suggestions() const
{
    Q_D(const QtMaterialSearchBar);
    return d->suggestions;
}

void QtMaterialSearchBar::setSearchDelay(int msec)
{
    Q_D(QtMaterialSearchBar);
    d->searchDelay = msec;
    d->field->setSearchDelay(msec);
}

int QtMaterialSearchBar::searchDelay() const
{
    Q_D(const QtMaterialSearchBar);
    return d->searchDelay;
}

void QtMaterialSearchBar::setInputLayout(QLayout *layout)
{
    Q_UNUSED(layout)
}

QLayout *QtMaterialSearchBar::inputLayout() const
{
    Q_D(const QtMaterialSearchBar);
    return d->inputLayout;
}

QtMaterialSearchField *QtMaterialSearchBar::searchField() const
{
    Q_D(const QtMaterialSearchBar);
    return d->field;
}

QAction *QtMaterialSearchBar::addTrailingAction(const QIcon &icon, const QString &toolTip)
{
    Q_D(QtMaterialSearchBar);
    QAction *action = new QAction(icon, toolTip, this);
    d->trailingActions.append(action);
    return action;
}

void QtMaterialSearchBar::clearTrailingActions()
{
    Q_D(QtMaterialSearchBar);
    qDeleteAll(d->trailingActions);
    d->trailingActions.clear();
}

void QtMaterialSearchBar::clear()
{
    Q_D(QtMaterialSearchBar);
    d->field->clear();
    emit cleared();
}

void QtMaterialSearchBar::expand()
{
    setActive(true);
}

void QtMaterialSearchBar::collapse()
{
    Q_D(QtMaterialSearchBar);
    if (!d->collapsible) {
        return;
    }
    setActive(false);
}

bool QtMaterialSearchBar::eventFilter(QObject *obj, QEvent *event)
{
    Q_D(QtMaterialSearchBar);
    if (obj == d->field && event->type() == QEvent::FocusIn) {
        setActive(true);
    }
    return QWidget::eventFilter(obj, event);
}

void QtMaterialSearchBar::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}
