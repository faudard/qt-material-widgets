#include "qtmaterialsnackbarlayout.h"
#include "qtmaterialsnackbarlayout_p.h"

#include <QLayoutItem>
#include <QWidget>

QtMaterialSnackbarLayoutPrivate::QtMaterialSnackbarLayoutPrivate(QtMaterialSnackbarLayout *q)
    : q_ptr(q),
      dense(false),
      messageSpacing(24),
      singleLineHeight(48),
      multiLineHeight(68)
{
}

QtMaterialSnackbarLayoutPrivate::~QtMaterialSnackbarLayoutPrivate()
{
}

int QtMaterialSnackbarLayoutPrivate::doLayout(const QRect &rect, bool testOnly) const
{
    Q_Q(const QtMaterialSnackbarLayout);

    if (items.isEmpty()) {
        return 0;
    }

    int left = 0;
    int top = 0;
    int right = 0;
    int bottom = 0;
    q->getContentsMargins(&left, &top, &right, &bottom);

    const QRect contents = rect.adjusted(left, top, -right, -bottom);
    if (!contents.isValid()) {
        return top + bottom;
    }

    QLayoutItem *messageItem = items.value(0, 0);
    QLayoutItem *actionItem = items.value(1, 0);

    if (!messageItem) {
        return top + bottom;
    }

    const QSize actionHint = actionItem ? actionItem->sizeHint() : QSize();
    const int minSingleHeight = dense ? qMax(36, singleLineHeight - 8) : singleLineHeight;
    const int minMultiHeight = dense ? qMax(minSingleHeight + 8, multiLineHeight - 8) : multiLineHeight;

    const int horizontalSpacing = q->spacing() >= 0 ? q->spacing() : messageSpacing;
    const int verticalSpacing = dense ? 6 : 8;

    const int actionWidth = actionItem ? actionHint.width() : 0;
    const int inlineMessageWidth = qMax(0, contents.width() - (actionItem ? actionWidth + horizontalSpacing : 0));
    const int inlineMessageHeight = messageItem->hasHeightForWidth()
        ? messageItem->heightForWidth(inlineMessageWidth)
        : messageItem->sizeHint().height();

    const bool singleLine = !actionItem
        || ((inlineMessageWidth > 120)
            && (inlineMessageHeight <= (dense ? 24 : 28))
            && (messageItem->sizeHint().width() + actionWidth + horizontalSpacing <= contents.width() + 24));

    if (singleLine) {
        const int height = qMax(minSingleHeight, qMax(inlineMessageHeight, actionHint.height()) + top + bottom);
        if (!testOnly) {
            int x = contents.x();
            const int y = contents.y() + (height - top - bottom - inlineMessageHeight) / 2;
            messageItem->setGeometry(QRect(x, y, inlineMessageWidth, inlineMessageHeight));
            x += inlineMessageWidth;

            if (actionItem) {
                x += horizontalSpacing;
                const int actionY = contents.y() + (height - top - bottom - actionHint.height()) / 2;
                actionItem->setGeometry(QRect(x, actionY, actionWidth, actionHint.height()));
            }
        }
        return height;
    }

    const int stackedMessageWidth = contents.width();
    const int stackedMessageHeight = messageItem->hasHeightForWidth()
        ? messageItem->heightForWidth(stackedMessageWidth)
        : messageItem->sizeHint().height();

    const int actionHeight = actionItem ? actionHint.height() : 0;
    const int calculatedHeight = qMax(minMultiHeight,
                                      top + stackedMessageHeight + (actionItem ? verticalSpacing + actionHeight : 0) + bottom);

    if (!testOnly) {
        const int messageY = contents.y();
        messageItem->setGeometry(QRect(contents.x(), messageY, stackedMessageWidth, stackedMessageHeight));

        if (actionItem) {
            const int actionX = contents.right() - actionWidth + 1;
            const int actionY = messageY + stackedMessageHeight + verticalSpacing;
            actionItem->setGeometry(QRect(actionX, actionY, actionWidth, actionHeight));
        }
    }

    return calculatedHeight;
}

QSize QtMaterialSnackbarLayoutPrivate::calculatedSize() const
{
    QSize size;
    QLayoutItem *messageItem = items.value(0, 0);
    QLayoutItem *actionItem = items.value(1, 0);

    if (messageItem) {
        size = size.expandedTo(messageItem->minimumSize());
        size = size.expandedTo(messageItem->sizeHint());
    }

    if (actionItem) {
        size.rwidth() += (size.isEmpty() ? 0 : messageSpacing) + actionItem->sizeHint().width();
        size.rheight() = qMax(size.height(), actionItem->sizeHint().height());
    }

    return size;
}

QtMaterialSnackbarLayout::QtMaterialSnackbarLayout(QWidget *parent)
    : QLayout(parent),
      d_ptr(new QtMaterialSnackbarLayoutPrivate(this))
{
    setContentsMargins(24, 14, 24, 14);
    setSpacing(24);
}

QtMaterialSnackbarLayout::~QtMaterialSnackbarLayout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)) != 0) {
        delete item;
    }
}

void QtMaterialSnackbarLayout::addItem(QLayoutItem *item)
{
    Q_D(QtMaterialSnackbarLayout);

    if (!item) {
        return;
    }

    d->items.append(item);
    invalidate();
}

int QtMaterialSnackbarLayout::count() const
{
    Q_D(const QtMaterialSnackbarLayout);
    return d->items.count();
}

QLayoutItem *QtMaterialSnackbarLayout::itemAt(int index) const
{
    Q_D(const QtMaterialSnackbarLayout);
    return d->items.value(index, 0);
}

QLayoutItem *QtMaterialSnackbarLayout::takeAt(int index)
{
    Q_D(QtMaterialSnackbarLayout);

    if (index < 0 || index >= d->items.count()) {
        return 0;
    }

    return d->items.takeAt(index);
}

QSize QtMaterialSnackbarLayout::sizeHint() const
{
    Q_D(const QtMaterialSnackbarLayout);

    int left = 0;
    int top = 0;
    int right = 0;
    int bottom = 0;
    getContentsMargins(&left, &top, &right, &bottom);

    const QSize size = d->calculatedSize();
    return QSize(qMax(288, size.width() + left + right),
                 qMax(d->dense ? 40 : d->singleLineHeight, size.height() + top + bottom));
}

QSize QtMaterialSnackbarLayout::minimumSize() const
{
    return sizeHint();
}

Qt::Orientations QtMaterialSnackbarLayout::expandingDirections() const
{
    return Qt::Horizontal;
}

bool QtMaterialSnackbarLayout::hasHeightForWidth() const
{
    return true;
}

int QtMaterialSnackbarLayout::heightForWidth(int width) const
{
    Q_D(const QtMaterialSnackbarLayout);
    return d->doLayout(QRect(0, 0, width, 0), true);
}

void QtMaterialSnackbarLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);
    Q_D(QtMaterialSnackbarLayout);
    d->doLayout(rect, false);
}

void QtMaterialSnackbarLayout::setDense(bool value)
{
    Q_D(QtMaterialSnackbarLayout);

    if (d->dense == value) {
        return;
    }

    d->dense = value;
    invalidate();
}

bool QtMaterialSnackbarLayout::isDense() const
{
    Q_D(const QtMaterialSnackbarLayout);
    return d->dense;
}

void QtMaterialSnackbarLayout::setMessageSpacing(int value)
{
    Q_D(QtMaterialSnackbarLayout);

    d->messageSpacing = qMax(0, value);
    setSpacing(d->messageSpacing);
    invalidate();
}

int QtMaterialSnackbarLayout::messageSpacing() const
{
    Q_D(const QtMaterialSnackbarLayout);
    return d->messageSpacing;
}

void QtMaterialSnackbarLayout::setSingleLineHeight(int value)
{
    Q_D(QtMaterialSnackbarLayout);
    d->singleLineHeight = qMax(32, value);
    invalidate();
}

int QtMaterialSnackbarLayout::singleLineHeight() const
{
    Q_D(const QtMaterialSnackbarLayout);
    return d->singleLineHeight;
}

void QtMaterialSnackbarLayout::setMultiLineHeight(int value)
{
    Q_D(QtMaterialSnackbarLayout);
    d->multiLineHeight = qMax(singleLineHeight(), value);
    invalidate();
}

int QtMaterialSnackbarLayout::multiLineHeight() const
{
    Q_D(const QtMaterialSnackbarLayout);
    return d->multiLineHeight;
}
