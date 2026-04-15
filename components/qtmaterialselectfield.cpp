#include "qtmaterialselectfield.h"
#include "qtmaterialselectfield_p.h"

#include "qtmaterialtextfield.h"
#include <QEvent>
#include <QFrame>
#include <QKeyEvent>
#include <QListWidget>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QVBoxLayout>

QtMaterialSelectFieldPrivate::QtMaterialSelectFieldPrivate(QtMaterialSelectField *q)
    : QtMaterialTextFieldPrivate(q)
    , index(-1)
    , editable(false)
    , showIndicator(true)
{
}

QtMaterialSelectFieldPrivate::~QtMaterialSelectFieldPrivate()
{
}

void QtMaterialSelectFieldPrivate::init()
{
    Q_Q(QtMaterialSelectField);

    popup = new QFrame(q, Qt::Popup | Qt::FramelessWindowHint);
    popup->setObjectName("materialSelectPopup");

    listWidget = new QListWidget(popup);
    QVBoxLayout *layout = new QVBoxLayout(popup);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(listWidget);

    q->setReadOnly(true);
    applyReadOnlyState();

    QObject::connect(listWidget, &QListWidget::currentRowChanged,
                     q, &QtMaterialSelectField::setCurrentIndex);

    QObject::connect(listWidget, &QListWidget::itemClicked,
                     q, [q](QListWidgetItem *) { q->closeMenu(); });
}

void QtMaterialSelectFieldPrivate::updatePopupGeometry()
{
    Q_Q(QtMaterialSelectField);
    if (!popup || !listWidget) {
        return;
    }

    const QPoint global = q->mapToGlobal(QPoint(0, q->height()));
    const int rowCount = qMin(itemList.size(), 6);
    const int rowHeight = 40;
    popup->setGeometry(global.x(), global.y(), q->width(), qMax(1, rowCount) * rowHeight);
}

void QtMaterialSelectFieldPrivate::syncSelection()
{
    Q_Q(QtMaterialSelectField);

    if (!listWidget) {
        return;
    }

    listWidget->clear();
    listWidget->addItems(itemList);
    listWidget->setCurrentRow(index);

    if (index >= 0 && index < itemList.size()) {
        q->setText(itemList.at(index));
    } else {
        q->setText(placeholder);
    }
}

void QtMaterialSelectFieldPrivate::applyReadOnlyState()
{
    Q_Q(QtMaterialSelectField);
    q->setReadOnly(!editable);
}

QtMaterialSelectField::QtMaterialSelectField(QWidget *parent)
    : QtMaterialTextField(*new QtMaterialSelectFieldPrivate(this), parent)
{
    Q_D(QtMaterialSelectField);
    d->init();
}

QtMaterialSelectField::~QtMaterialSelectField()
{
}

void QtMaterialSelectField::setItems(const QStringList &items)
{
    Q_D(QtMaterialSelectField);
    d->itemList = items;
    if (d->index >= d->itemList.size()) {
        d->index = -1;
    }
    d->syncSelection();
}

QStringList QtMaterialSelectField::items() const
{
    Q_D(const QtMaterialSelectField);
    return d->itemList;
}

void QtMaterialSelectField::setCurrentIndex(int index)
{
    Q_D(QtMaterialSelectField);
    if (index < -1 || index >= d->itemList.size() || index == d->index) {
        return;
    }

    d->index = index;
    d->syncSelection();
    emit currentIndexChanged(d->index);
    emit currentTextChanged(currentText());
}

int QtMaterialSelectField::currentIndex() const
{
    Q_D(const QtMaterialSelectField);
    return d->index;
}

void QtMaterialSelectField::setCurrentText(const QString &text)
{
    Q_D(QtMaterialSelectField);
    setCurrentIndex(d->itemList.indexOf(text));
}

QString QtMaterialSelectField::currentText() const
{
    Q_D(const QtMaterialSelectField);
    return (d->index >= 0 && d->index < d->itemList.size()) ? d->itemList.at(d->index) : QString();
}

void QtMaterialSelectField::setPlaceholderOption(const QString &text)
{
    Q_D(QtMaterialSelectField);
    d->placeholder = text;
    d->syncSelection();
}

QString QtMaterialSelectField::placeholderOption() const
{
    Q_D(const QtMaterialSelectField);
    return d->placeholder;
}

void QtMaterialSelectField::setEditableSelection(bool value)
{
    Q_D(QtMaterialSelectField);
    d->editable = value;
    d->applyReadOnlyState();
}

bool QtMaterialSelectField::editableSelection() const
{
    Q_D(const QtMaterialSelectField);
    return d->editable;
}

void QtMaterialSelectField::setShowDropdownIndicator(bool value)
{
    Q_D(QtMaterialSelectField);
    d->showIndicator = value;
    update();
}

bool QtMaterialSelectField::showDropdownIndicator() const
{
    Q_D(const QtMaterialSelectField);
    return d->showIndicator;
}

void QtMaterialSelectField::setPopupBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialSelectField);
    d->popupBackgroundColor = color;
}

QColor QtMaterialSelectField::popupBackgroundColor() const
{
    Q_D(const QtMaterialSelectField);
    return d->popupBackgroundColor;
}

void QtMaterialSelectField::setPopupTextColor(const QColor &color)
{
    Q_D(QtMaterialSelectField);
    d->popupTextColor = color;
}

QColor QtMaterialSelectField::popupTextColor() const
{
    Q_D(const QtMaterialSelectField);
    return d->popupTextColor;
}

void QtMaterialSelectField::setPopupSelectedColor(const QColor &color)
{
    Q_D(QtMaterialSelectField);
    d->popupSelectedColor = color;
}

QColor QtMaterialSelectField::popupSelectedColor() const
{
    Q_D(const QtMaterialSelectField);
    return d->popupSelectedColor;
}

void QtMaterialSelectField::openMenu()
{
    Q_D(QtMaterialSelectField);
    d->updatePopupGeometry();
    if (d->popup) {
        d->popup->show();
        d->popup->raise();
    }
}

void QtMaterialSelectField::closeMenu()
{
    Q_D(QtMaterialSelectField);
    if (d->popup) {
        d->popup->hide();
    }
}

bool QtMaterialSelectField::event(QEvent *event)
{
    if (event->type() == QEvent::EnabledChange) {
        update();
    }
    return QtMaterialTextField::event(event);
}

void QtMaterialSelectField::resizeEvent(QResizeEvent *event)
{
    QtMaterialTextField::resizeEvent(event);
    Q_D(QtMaterialSelectField);
    d->updatePopupGeometry();
}

void QtMaterialSelectField::mousePressEvent(QMouseEvent *event)
{
    QtMaterialTextField::mousePressEvent(event);
    if (isEnabled()) {
        openMenu();
    }
}

void QtMaterialSelectField::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Space:
    case Qt::Key_Return:
    case Qt::Key_Enter:
    case Qt::Key_Down:
        openMenu();
        event->accept();
        return;
    case Qt::Key_Escape:
        closeMenu();
        event->accept();
        return;
    default:
        break;
    }

    QtMaterialTextField::keyPressEvent(event);
}
