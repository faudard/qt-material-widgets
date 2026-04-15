#include "qtmaterialsearchfield.h"
#include "qtmaterialsearchfield_p.h"
#include "lib/qtmaterialstyle.h"

#include <QAction>
#include <QEvent>
#include <QStyle>
#include <QTimer>
#include <QResizeEvent>

QtMaterialSearchFieldPrivate::QtMaterialSearchFieldPrivate(QtMaterialSearchField *q)
    : q_ptr(q),
      showSearchIcon(true),
      showClearButton(true),
      searchDelay(250),
      searchAction(0),
      clearAction(0),
      searchTimer(0)
{
}

QtMaterialSearchFieldPrivate::~QtMaterialSearchFieldPrivate()
{
}

void QtMaterialSearchFieldPrivate::init()
{
    Q_Q(QtMaterialSearchField);

    searchTimer = new QTimer(q);
    searchTimer->setSingleShot(true);

    searchAction = q->addAction(q->style()->standardIcon(QStyle::SP_FileDialogContentsView),
                                QLineEdit::LeadingPosition);
    clearAction = q->addAction(q->style()->standardIcon(QStyle::SP_LineEditClearButton),
                               QLineEdit::TrailingPosition);

    QObject::connect(clearAction, &QAction::triggered,
                     q, &QtMaterialSearchField::handleClearButtonClicked);
    QObject::connect(searchTimer, &QTimer::timeout,
                     q, &QtMaterialSearchField::emitSearch);
    QObject::connect(q, &QLineEdit::textChanged,
                     q, &QtMaterialSearchField::queueSearch);

    q->setLabel("Search");
    q->setShowLabel(true);

    updateActions();
}

void QtMaterialSearchFieldPrivate::updateActions()
{
    if (searchAction) {
        searchAction->setVisible(showSearchIcon);
        if (!searchIcon.isNull()) {
            searchAction->setIcon(searchIcon);
        }
    }
    if (clearAction) {
        clearAction->setVisible(showClearButton && !q_ptr->text().isEmpty());
        if (!clearIcon.isNull()) {
            clearAction->setIcon(clearIcon);
        }
    }
}

void QtMaterialSearchFieldPrivate::updateMargins()
{
    Q_Q(QtMaterialSearchField);

    int left = showSearchIcon ? 32 : 0;
    int right = showClearButton ? 32 : 0;

    q->setTextMargins(left, 0, right, 0);
}

QtMaterialSearchField::QtMaterialSearchField(QWidget *parent)
    : QtMaterialTextField(parent),
      d_ptr(new QtMaterialSearchFieldPrivate(this))
{
    Q_D(QtMaterialSearchField);
    d->init();
}

QtMaterialSearchField::~QtMaterialSearchField()
{
}

void QtMaterialSearchField::setShowSearchIcon(bool value)
{
    Q_D(QtMaterialSearchField);

    if (d->showSearchIcon == value) {
        return;
    }

    d->showSearchIcon = value;
    d->updateActions();
    d->updateMargins();
    update();
}

bool QtMaterialSearchField::hasSearchIcon() const
{
    Q_D(const QtMaterialSearchField);
    return d->showSearchIcon;
}

void QtMaterialSearchField::setShowClearButton(bool value)
{
    Q_D(QtMaterialSearchField);

    if (d->showClearButton == value) {
        return;
    }

    d->showClearButton = value;
    d->updateActions();
    d->updateMargins();
    update();
}

bool QtMaterialSearchField::hasClearButton() const
{
    Q_D(const QtMaterialSearchField);
    return d->showClearButton;
}

void QtMaterialSearchField::setSearchDelay(int msec)
{
    Q_D(QtMaterialSearchField);
    d->searchDelay = qMax(0, msec);
}

int QtMaterialSearchField::searchDelay() const
{
    Q_D(const QtMaterialSearchField);
    return d->searchDelay;
}

void QtMaterialSearchField::setIconColor(const QColor &color)
{
    Q_D(QtMaterialSearchField);
    d->iconColor = color;
    update();
}

QColor QtMaterialSearchField::iconColor() const
{
    Q_D(const QtMaterialSearchField);

    if (d->iconColor.isValid()) {
        return d->iconColor;
    }

    return QtMaterialStyle::instance().themeColor("border");
}

void QtMaterialSearchField::setSearchIcon(const QIcon &icon)
{
    Q_D(QtMaterialSearchField);
    d->searchIcon = icon;
    d->updateActions();
}

QIcon QtMaterialSearchField::searchIcon() const
{
    Q_D(const QtMaterialSearchField);
    return d->searchIcon;
}

void QtMaterialSearchField::setClearIcon(const QIcon &icon)
{
    Q_D(QtMaterialSearchField);
    d->clearIcon = icon;
    d->updateActions();
}

QIcon QtMaterialSearchField::clearIcon() const
{
    Q_D(const QtMaterialSearchField);
    return d->clearIcon;
}

void QtMaterialSearchField::queueSearch(const QString &text)
{
    Q_D(QtMaterialSearchField);
    d->updateActions();

    if (d->searchDelay == 0) {
        emit searchRequested(text);
        return;
    }

    d->searchTimer->start(d->searchDelay);
}

void QtMaterialSearchField::emitSearch()
{
    emit searchRequested(text());
}

void QtMaterialSearchField::handleClearButtonClicked()
{
    clear();
    emit cleared();
    emit searchRequested(QString());
}

bool QtMaterialSearchField::event(QEvent *event)
{
    Q_D(QtMaterialSearchField);

    switch (event->type()) {
    case QEvent::EnabledChange:
    case QEvent::StyleChange:
        d->updateActions();
        break;
    default:
        break;
    }

    return QtMaterialTextField::event(event);
}

void QtMaterialSearchField::resizeEvent(QResizeEvent *event)
{
    Q_D(QtMaterialSearchField);
    d->updateMargins();
    QtMaterialTextField::resizeEvent(event);
}
