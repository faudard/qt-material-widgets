#include "qtmaterialfulldialog.h"
#include "qtmaterialfulldialog_p.h"

#include <QEvent>
#include <QPainter>
#include <QResizeEvent>
#include <QVBoxLayout>
#include <QWidget>

QtMaterialFullScreenDialogPrivate::QtMaterialFullScreenDialogPrivate()
    : useThemeColors(true),
      dismissOnOverlayClick(true),
      surface(0),
      header(0),
      content(0),
      surfaceLayout(0),
      contentLayout(0)
{
}

QtMaterialFullScreenDialog::QtMaterialFullScreenDialog(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialFullScreenDialogPrivate)
{
    setAttribute(Qt::WA_StyledBackground, true);
    setVisible(false);
}

QtMaterialFullScreenDialog::~QtMaterialFullScreenDialog()
{
    delete d_ptr;
}

void QtMaterialFullScreenDialog::setUseThemeColors(bool value) { Q_D(QtMaterialFullScreenDialog); d->useThemeColors = value; update(); }
bool QtMaterialFullScreenDialog::useThemeColors() const { Q_D(const QtMaterialFullScreenDialog); return d->useThemeColors; }

void QtMaterialFullScreenDialog::setBackgroundColor(const QColor &color) { Q_D(QtMaterialFullScreenDialog); d->backgroundColor = color; update(); }
QColor QtMaterialFullScreenDialog::backgroundColor() const { Q_D(const QtMaterialFullScreenDialog); return d->backgroundColor; }

void QtMaterialFullScreenDialog::setOverlayColor(const QColor &color) { Q_D(QtMaterialFullScreenDialog); d->overlayColor = color; update(); }
QColor QtMaterialFullScreenDialog::overlayColor() const { Q_D(const QtMaterialFullScreenDialog); return d->overlayColor; }

void QtMaterialFullScreenDialog::setTitleColor(const QColor &color) { Q_D(QtMaterialFullScreenDialog); d->titleColor = color; update(); }
QColor QtMaterialFullScreenDialog::titleColor() const { Q_D(const QtMaterialFullScreenDialog); return d->titleColor; }

void QtMaterialFullScreenDialog::setTitle(const QString &title) { Q_D(QtMaterialFullScreenDialog); d->title = title; update(); }
QString QtMaterialFullScreenDialog::title() const { Q_D(const QtMaterialFullScreenDialog); return d->title; }

void QtMaterialFullScreenDialog::setContentLayout(QLayout *layout) { Q_UNUSED(layout) }
QLayout *QtMaterialFullScreenDialog::contentLayout() const { return 0; }

void QtMaterialFullScreenDialog::setDismissOnOverlayClick(bool value) { Q_D(QtMaterialFullScreenDialog); d->dismissOnOverlayClick = value; }
bool QtMaterialFullScreenDialog::dismissOnOverlayClick() const { Q_D(const QtMaterialFullScreenDialog); return d->dismissOnOverlayClick; }

void QtMaterialFullScreenDialog::open() { show(); raise(); emit opened(); }
void QtMaterialFullScreenDialog::close() { hide(); emit closed(); }

bool QtMaterialFullScreenDialog::eventFilter(QObject *obj, QEvent *event) { Q_UNUSED(obj) Q_UNUSED(event) return false; }

void QtMaterialFullScreenDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.fillRect(rect(), overlayColor().isValid() ? overlayColor() : QColor(0, 0, 0, 160));
    painter.fillRect(rect().adjusted(0, 24, 0, 0), backgroundColor().isValid() ? backgroundColor() : Qt::white);
    painter.setPen(titleColor().isValid() ? titleColor() : Qt::black);
    painter.drawText(QRect(24, 24, width() - 48, 56), Qt::AlignVCenter | Qt::AlignLeft, title());
}

void QtMaterialFullScreenDialog::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}
