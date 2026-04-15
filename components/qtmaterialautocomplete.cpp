#include "qtmaterialautocomplete.h"
#include "qtmaterialautocomplete_p.h"

#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QVBoxLayout>
#include <QEvent>
#include <QFontMetrics>
#include <QKeyEvent>
#include <QPainter>

#include "qtmaterialautocomplete_internal.h"
#include "qtmaterialflatbutton.h"
#include "lib/qtmaterialstyle.h"

QtMaterialAutoCompletePrivate::QtMaterialAutoCompletePrivate(QtMaterialAutoComplete *q)
    : QtMaterialTextFieldPrivate(q)
{
}

QtMaterialAutoCompletePrivate::~QtMaterialAutoCompletePrivate()
{
}

void QtMaterialAutoCompletePrivate::init()
{
    Q_Q(QtMaterialAutoComplete);

    menu = new QWidget;
    frame = new QWidget;
    stateMachine = new QtMaterialAutoCompleteStateMachine(menu);
    menuLayout = new QVBoxLayout;
    maxWidth = 0;
    maxVisibleItems = 5;
    highlightedIndex = -1;
    caseSensitivity = Qt::CaseInsensitive;
    filterMode = QtMaterialAutoComplete::ContainsFilter;

    menu->setParent(q->parentWidget());
    frame->setParent(q->parentWidget());

    menu->installEventFilter(q);
    frame->installEventFilter(q);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(11);
    effect->setColor(QColor(0, 0, 0, 50));
    effect->setOffset(0, 3);

    frame->setGraphicsEffect(effect);
    frame->setVisible(false);
    frame->setAttribute(Qt::WA_TransparentForMouseEvents);

    menu->setLayout(menuLayout);
    menu->setVisible(false);
    menu->setFocusPolicy(Qt::NoFocus);

    menuLayout->setContentsMargins(0, 0, 0, 0);
    menuLayout->setSpacing(0);

    QObject::connect(q, SIGNAL(textEdited(QString)), q, SLOT(updateResults(QString)));

    stateMachine->start();
}

void QtMaterialAutoCompletePrivate::syncMenuGeometry()
{
    Q_Q(QtMaterialAutoComplete);

    QWidget *parent = q->parentWidget();
    if (!parent) {
        return;
    }

    const QPoint localTopLeft = q->mapTo(parent, QPoint(0, q->height() + 6));
    menu->move(localTopLeft);
    frame->setGeometry(menu->geometry());
}

void QtMaterialAutoCompletePrivate::updateMenuButtons(const QStringList &results)
{
    Q_Q(QtMaterialAutoComplete);

    const int itemHeight = 48;
    const int visibleCount = qMin(results.count(), maxVisibleItems);
    const int diff = visibleCount - buttons.count();

    if (diff > 0) {
        for (int i = 0; i < diff; ++i) {
            QtMaterialFlatButton *item = new QtMaterialFlatButton;
            item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            item->setCornerRadius(0);
            item->setHaloVisible(false);
            item->setFixedHeight(itemHeight);
            item->setOverlayStyle(Material::TintedOverlay);
            item->setBackgroundMode(Qt::OpaqueMode);
            item->setUseThemeColors(false);
            menuLayout->addWidget(item);
            item->installEventFilter(q);
            buttons.append(item);
        }
    } else if (diff < 0) {
        for (int i = 0; i < -diff; ++i) {
            QtMaterialFlatButton *item = buttons.takeLast();
            menuLayout->removeWidget(item);
            delete item;
        }
    }

    QFont font("Roboto", 12, QFont::Normal);
    QFontMetrics fm(font);
    maxWidth = 0;

    visibleResults = results.mid(0, visibleCount);

    for (int i = 0; i < buttons.count(); ++i) {
        QtMaterialFlatButton *item = buttons.at(i);
        item->setVisible(i < visibleResults.count());
        item->setFont(font);

        if (i < visibleResults.count()) {
            const QString text = visibleResults.at(i);
            item->setText(text);
            maxWidth = qMax(maxWidth, fm.horizontalAdvance(text));
        } else {
            item->setText(QString());
        }
    }

    highlightedIndex = visibleResults.isEmpty() ? -1 : 0;
    updateMenuButtonStyles();

    menu->setFixedHeight(visibleResults.count() * itemHeight);
    menu->setFixedWidth(qMax(maxWidth + 32, q->width()));
    syncMenuGeometry();
    menu->update();
}

void QtMaterialAutoCompletePrivate::updateMenuButtonStyles()
{
    QColor background = menuBackgroundColor.isValid() ? menuBackgroundColor : QColor(Qt::white);
    QColor text = menuTextColor.isValid() ? menuTextColor : QtMaterialStyle::instance().themeColor("text");
    QColor selected = menuSelectedColor.isValid() ? menuSelectedColor : QColor(0, 0, 0, 18);

    for (int i = 0; i < buttons.count(); ++i) {
        QtMaterialFlatButton *item = buttons.at(i);
        item->setForegroundColor(text);
        item->setBackgroundColor(i == highlightedIndex ? selected : background);
    }

    if (frame) {
        frame->update();
    }
}

void QtMaterialAutoCompletePrivate::setHighlightedIndex(int value)
{
    if (visibleResults.isEmpty()) {
        highlightedIndex = -1;
    } else {
        const int count = visibleResults.count();
        highlightedIndex = (value % count + count) % count;
    }

    updateMenuButtonStyles();
}

void QtMaterialAutoCompletePrivate::activateIndex(int value)
{
    Q_Q(QtMaterialAutoComplete);

    if (value < 0 || value >= visibleResults.count()) {
        return;
    }

    const QString selectedText = visibleResults.at(value);
    q->setText(selectedText);
    emit q->itemSelected(selectedText);
    emit stateMachine->shouldFade();
}

QtMaterialAutoComplete::QtMaterialAutoComplete(QWidget *parent)
    : QtMaterialTextField(*new QtMaterialAutoCompletePrivate(this), parent)
{
    d_func()->init();
}

QtMaterialAutoComplete::~QtMaterialAutoComplete()
{
}

void QtMaterialAutoComplete::setDataSource(const QStringList &data)
{
    Q_D(QtMaterialAutoComplete);

    d->dataSource = data;
    updateResults(text());
}

QStringList QtMaterialAutoComplete::dataSource() const
{
    Q_D(const QtMaterialAutoComplete);
    return d->dataSource;
}

void QtMaterialAutoComplete::setMaxVisibleItems(int value)
{
    Q_D(QtMaterialAutoComplete);

    d->maxVisibleItems = qMax(1, value);
    updateResults(text());
}

int QtMaterialAutoComplete::maxVisibleItems() const
{
    Q_D(const QtMaterialAutoComplete);
    return d->maxVisibleItems;
}

void QtMaterialAutoComplete::setCaseSensitivity(Qt::CaseSensitivity value)
{
    Q_D(QtMaterialAutoComplete);

    d->caseSensitivity = value;
    updateResults(text());
}

Qt::CaseSensitivity QtMaterialAutoComplete::caseSensitivity() const
{
    Q_D(const QtMaterialAutoComplete);
    return d->caseSensitivity;
}

void QtMaterialAutoComplete::setFilterMode(FilterMode value)
{
    Q_D(QtMaterialAutoComplete);

    d->filterMode = static_cast<int>(value);
    updateResults(text());
}

QtMaterialAutoComplete::FilterMode QtMaterialAutoComplete::filterMode() const
{
    Q_D(const QtMaterialAutoComplete);
    return static_cast<FilterMode>(d->filterMode);
}

void QtMaterialAutoComplete::setMenuBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialAutoComplete);

    d->menuBackgroundColor = color;
    d->updateMenuButtonStyles();
}

QColor QtMaterialAutoComplete::menuBackgroundColor() const
{
    Q_D(const QtMaterialAutoComplete);
    return d->menuBackgroundColor.isValid() ? d->menuBackgroundColor : QColor(Qt::white);
}

void QtMaterialAutoComplete::setMenuTextColor(const QColor &color)
{
    Q_D(QtMaterialAutoComplete);

    d->menuTextColor = color;
    d->updateMenuButtonStyles();
}

QColor QtMaterialAutoComplete::menuTextColor() const
{
    Q_D(const QtMaterialAutoComplete);
    return d->menuTextColor.isValid() ? d->menuTextColor : QtMaterialStyle::instance().themeColor("text");
}

void QtMaterialAutoComplete::setMenuSelectedColor(const QColor &color)
{
    Q_D(QtMaterialAutoComplete);

    d->menuSelectedColor = color;
    d->updateMenuButtonStyles();
}

QColor QtMaterialAutoComplete::menuSelectedColor() const
{
    Q_D(const QtMaterialAutoComplete);
    return d->menuSelectedColor.isValid() ? d->menuSelectedColor : QColor(0, 0, 0, 18);
}

void QtMaterialAutoComplete::updateResults(QString text)
{
    Q_D(QtMaterialAutoComplete);

    const QString trimmed = text.trimmed();
    QStringList prefixMatches;
    QStringList containsMatches;

    if (!trimmed.isEmpty()) {
        for (QStringList::const_iterator it = d->dataSource.constBegin(); it != d->dataSource.constEnd(); ++it) {
            const QString candidate = *it;
            const bool startsWith = candidate.startsWith(trimmed, d->caseSensitivity);
            const bool contains = candidate.contains(trimmed, d->caseSensitivity);

            if (static_cast<FilterMode>(d->filterMode) == StartsWithFilter) {
                if (startsWith) {
                    prefixMatches.push_back(candidate);
                }
            } else {
                if (startsWith) {
                    prefixMatches.push_back(candidate);
                } else if (contains) {
                    containsMatches.push_back(candidate);
                }
            }
        }
    }

    const QStringList results = prefixMatches + containsMatches;
    d->updateMenuButtons(results);

    if (results.isEmpty()) {
        emit d->stateMachine->shouldClose();
    } else {
        emit d->stateMachine->shouldOpen();
    }
}

bool QtMaterialAutoComplete::event(QEvent *event)
{
    Q_D(QtMaterialAutoComplete);

    switch (event->type()) {
    case QEvent::Move:
    case QEvent::Resize:
    case QEvent::Show:
        d->syncMenuGeometry();
        break;
    case QEvent::ParentChange: {
        QWidget *widget = qobject_cast<QWidget *>(parent());
        if (widget) {
            d->menu->setParent(widget);
            d->frame->setParent(widget);
            d->syncMenuGeometry();
        }
        break;
    }
    case QEvent::KeyPress: {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        switch (keyEvent->key()) {
        case Qt::Key_Down:
            if (!d->visibleResults.isEmpty()) {
                d->setHighlightedIndex(d->highlightedIndex + 1);
                if (!d->menu->isVisible()) {
                    emit d->stateMachine->shouldOpen();
                }
                return true;
            }
            break;
        case Qt::Key_Up:
            if (!d->visibleResults.isEmpty()) {
                d->setHighlightedIndex(d->highlightedIndex - 1);
                return true;
            }
            break;
        case Qt::Key_Return:
        case Qt::Key_Enter:
            if (d->menu->isVisible() && d->highlightedIndex >= 0) {
                d->activateIndex(d->highlightedIndex);
                return true;
            }
            break;
        case Qt::Key_Escape:
            emit d->stateMachine->shouldClose();
            return true;
        default:
            break;
        }
        break;
    }
    default:
        break;
    }

    return QtMaterialTextField::event(event);
}

bool QtMaterialAutoComplete::eventFilter(QObject *watched, QEvent *event)
{
    Q_D(QtMaterialAutoComplete);

    if (d->frame == watched) {
        switch (event->type()) {
        case QEvent::Paint: {
            QPainter painter(d->frame);
            painter.fillRect(d->frame->rect(), menuBackgroundColor());
            break;
        }
        default:
            break;
        }
    } else if (d->menu == watched) {
        switch (event->type()) {
        case QEvent::Resize:
        case QEvent::Move:
            d->frame->setGeometry(d->menu->geometry());
            break;
        case QEvent::Show:
            d->frame->show();
            d->menu->raise();
            break;
        case QEvent::Hide:
            d->frame->hide();
            break;
        default:
            break;
        }
    } else {
        const int index = d->buttons.indexOf(static_cast<QtMaterialFlatButton *>(watched));
        switch (event->type()) {
        case QEvent::Enter:
            d->setHighlightedIndex(index);
            break;
        case QEvent::MouseButtonPress:
            d->activateIndex(index);
            break;
        default:
            break;
        }
    }

    return QtMaterialTextField::eventFilter(watched, event);
}
