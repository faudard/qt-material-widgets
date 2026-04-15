#include "qtmaterialsearchview.h"
#include "qtmaterialsearchview_p.h"

#include <QEvent>
#include <QFrame>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPainter>
#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStyle>
#include <QSignalBlocker>

QtMaterialSearchViewPrivate::QtMaterialSearchViewPrivate(QtMaterialSearchView *q)
    : q_ptr(q),
      useThemeColors(true),
      active(false),
      surface(0),
      header(0),
      lineEdit(0),
      backButton(0),
      clearButton(0),
      listWidget(0),
      rootLayout(0),
      surfaceLayout(0),
      headerLayout(0)
{
}

QtMaterialSearchViewPrivate::~QtMaterialSearchViewPrivate()
{
}

void QtMaterialSearchViewPrivate::init()
{
    Q_Q(QtMaterialSearchView);

    surface = new QFrame(q);
    surface->setObjectName("searchViewSurface");
    surface->setFrameShape(QFrame::NoFrame);

    header = new QFrame(surface);
    header->setObjectName("searchViewHeader");
    header->setFrameShape(QFrame::NoFrame);

    backButton = new QToolButton(header);
    backButton->setAutoRaise(true);
    backButton->setIcon(q->style()->standardIcon(QStyle::SP_ArrowBack));

    clearButton = new QToolButton(header);
    clearButton->setAutoRaise(true);
    clearButton->setIcon(q->style()->standardIcon(QStyle::SP_LineEditClearButton));

    lineEdit = new QLineEdit(header);
    lineEdit->setPlaceholderText("Search");

    listWidget = new QListWidget(surface);
    listWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(12, 8, 12, 8);
    headerLayout->setSpacing(8);
    headerLayout->addWidget(backButton);
    headerLayout->addWidget(lineEdit, 1);
    headerLayout->addWidget(clearButton);

    surfaceLayout = new QVBoxLayout(surface);
    surfaceLayout->setContentsMargins(0, 0, 0, 0);
    surfaceLayout->setSpacing(0);
    surfaceLayout->addWidget(header);
    surfaceLayout->addWidget(listWidget, 1);

    rootLayout = new QVBoxLayout(q);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->addWidget(surface);

    QObject::connect(lineEdit, SIGNAL(textChanged(QString)), q, SLOT(updateSuggestions(QString)));
    QObject::connect(lineEdit, SIGNAL(returnPressed()), q, SLOT(handleReturnPressed()));
    QObject::connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)), q, SLOT(handleSuggestionClicked(QListWidgetItem*)));
    QObject::connect(clearButton, &QToolButton::clicked, lineEdit, &QLineEdit::clear);
    QObject::connect(backButton, &QToolButton::clicked, [q](){ q->setActive(false); });

    q->installEventFilter(q);
    lineEdit->installEventFilter(q);
    listWidget->installEventFilter(q);

    applyActiveState();
}

void QtMaterialSearchViewPrivate::applyActiveState()
{
    surface->setVisible(active);
}

QColor QtMaterialSearchViewPrivate::resolveBackgroundColor() const
{
    return backgroundColor.isValid() ? backgroundColor : QColor(255, 255, 255);
}

QColor QtMaterialSearchViewPrivate::resolveTextColor() const
{
    return textColor.isValid() ? textColor : QColor(33, 33, 33);
}

QColor QtMaterialSearchViewPrivate::resolveDividerColor() const
{
    return dividerColor.isValid() ? dividerColor : QColor(224, 224, 224);
}

QtMaterialSearchView::QtMaterialSearchView(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialSearchViewPrivate(this))
{
    Q_D(QtMaterialSearchView);
    d->init();
}

QtMaterialSearchView::~QtMaterialSearchView()
{
    delete d_ptr;
}

void QtMaterialSearchView::setUseThemeColors(bool value)
{
    Q_D(QtMaterialSearchView);
    d->useThemeColors = value;
    update();
}

bool QtMaterialSearchView::useThemeColors() const
{
    Q_D(const QtMaterialSearchView);
    return d->useThemeColors;
}

void QtMaterialSearchView::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialSearchView);
    d->backgroundColor = color;
    update();
}

QColor QtMaterialSearchView::backgroundColor() const
{
    Q_D(const QtMaterialSearchView);
    return d->backgroundColor;
}

void QtMaterialSearchView::setTextColor(const QColor &color)
{
    Q_D(QtMaterialSearchView);
    d->textColor = color;
    update();
}

QColor QtMaterialSearchView::textColor() const
{
    Q_D(const QtMaterialSearchView);
    return d->textColor;
}

void QtMaterialSearchView::setDividerColor(const QColor &color)
{
    Q_D(QtMaterialSearchView);
    d->dividerColor = color;
    update();
}

QColor QtMaterialSearchView::dividerColor() const
{
    Q_D(const QtMaterialSearchView);
    return d->dividerColor;
}

void QtMaterialSearchView::setPlaceholderText(const QString &text)
{
    Q_D(QtMaterialSearchView);
    d->lineEdit->setPlaceholderText(text);
}

QString QtMaterialSearchView::placeholderText() const
{
    Q_D(const QtMaterialSearchView);
    return d->lineEdit->placeholderText();
}

void QtMaterialSearchView::setSuggestions(const QStringList &items)
{
    Q_D(QtMaterialSearchView);
    d->suggestionItems = items;
    updateSuggestions(d->lineEdit->text());
}

QStringList QtMaterialSearchView::suggestions() const
{
    Q_D(const QtMaterialSearchView);
    return d->suggestionItems;
}

void QtMaterialSearchView::setActive(bool value)
{
    Q_D(QtMaterialSearchView);
    if (d->active == value) {
        return;
    }
    d->active = value;
    d->applyActiveState();
    emit activeChanged(value);
}

bool QtMaterialSearchView::isActive() const
{
    Q_D(const QtMaterialSearchView);
    return d->active;
}

QString QtMaterialSearchView::text() const
{
    Q_D(const QtMaterialSearchView);
    return d->lineEdit->text();
}

void QtMaterialSearchView::clear()
{
    Q_D(QtMaterialSearchView);
    d->lineEdit->clear();
}

bool QtMaterialSearchView::eventFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(obj)

    if (event->type() == QEvent::Show) {
        Q_D(QtMaterialSearchView);
        d->surface->setStyleSheet(QString(
            "#searchViewSurface { background: %1; border: 1px solid %2; border-radius: 16px; }"
            "#searchViewHeader { border-bottom: 1px solid %2; }"
            "QLineEdit { border: none; color: %3; background: transparent; padding: 8px 0; }"
            "QListWidget { border: none; color: %3; background: transparent; }")
            .arg(d->resolveBackgroundColor().name(),
                 d->resolveDividerColor().name(),
                 d->resolveTextColor().name()));
    }
    return QWidget::eventFilter(obj, event);
}

void QtMaterialSearchView::updateSuggestions(const QString &text)
{
    Q_D(QtMaterialSearchView);

    d->listWidget->clear();

    const QString needle = text.trimmed();
    for (const QString &item : d->suggestionItems) {
        if (needle.isEmpty() || item.contains(needle, Qt::CaseInsensitive)) {
            d->listWidget->addItem(item);
        }
    }
}

void QtMaterialSearchView::handleReturnPressed()
{
    emit searchRequested(text());
}

#include <QSignalBlocker>

void QtMaterialSearchView::handleSuggestionClicked(QListWidgetItem *item)
{
  if (!item) {
    return;
  }

  const QString selectedText = item->text();

  Q_D(QtMaterialSearchView);
  {
    QSignalBlocker blocker(d->lineEdit);
    d->lineEdit->setText(selectedText);
  }

  updateSuggestions(selectedText);
  emit suggestionSelected(selectedText);
  emit searchRequested(selectedText);
}