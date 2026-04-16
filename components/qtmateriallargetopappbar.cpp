#include "qtmateriallargetopappbar.h"
#include "qtmateriallargetopappbar_p.h"
#include <QPainter>
QtMaterialLargeTopAppBarPrivate::QtMaterialLargeTopAppBarPrivate(QtMaterialLargeTopAppBar *q): q_ptr(q), useThemeColors(true) {}
QtMaterialLargeTopAppBarPrivate::~QtMaterialLargeTopAppBarPrivate() {}
void QtMaterialLargeTopAppBarPrivate::init() {}
QtMaterialLargeTopAppBar::QtMaterialLargeTopAppBar(QWidget *parent): QWidget(parent), d_ptr(new QtMaterialLargeTopAppBarPrivate(this)) { d_func()->init(); }
QtMaterialLargeTopAppBar::~QtMaterialLargeTopAppBar() {}
void QtMaterialLargeTopAppBar::setUseThemeColors(bool value){Q_D(QtMaterialLargeTopAppBar); d->useThemeColors=value; update();}
bool QtMaterialLargeTopAppBar::useThemeColors() const{Q_D(const QtMaterialLargeTopAppBar); return d->useThemeColors;}
void QtMaterialLargeTopAppBar::setForegroundColor(const QColor &color){Q_D(QtMaterialLargeTopAppBar); d->foregroundColor=color; d->useThemeColors=false; update();}
QColor QtMaterialLargeTopAppBar::foregroundColor() const{Q_D(const QtMaterialLargeTopAppBar); return d->foregroundColor;}
void QtMaterialLargeTopAppBar::setBackgroundColor(const QColor &color){Q_D(QtMaterialLargeTopAppBar); d->backgroundColor=color; d->useThemeColors=false; update();}
QColor QtMaterialLargeTopAppBar::backgroundColor() const{Q_D(const QtMaterialLargeTopAppBar); return d->backgroundColor;}
void QtMaterialLargeTopAppBar::setTitle(const QString &text){Q_D(QtMaterialLargeTopAppBar); d->title=text; update();}
QString QtMaterialLargeTopAppBar::title() const{Q_D(const QtMaterialLargeTopAppBar); return d->title;}
void QtMaterialLargeTopAppBar::setSubtitle(const QString &text){Q_D(QtMaterialLargeTopAppBar); d->subtitle=text; update();}
QString QtMaterialLargeTopAppBar::subtitle() const{Q_D(const QtMaterialLargeTopAppBar); return d->subtitle;}
QSize QtMaterialLargeTopAppBar::sizeHint() const { return QSize(-1, 152); }
void QtMaterialLargeTopAppBar::paintEvent(QPaintEvent *){Q_D(QtMaterialLargeTopAppBar); QPainter p(this); p.fillRect(rect(), d->backgroundColor.isValid()?d->backgroundColor:QColor(250,250,250)); p.setPen(d->foregroundColor.isValid()?d->foregroundColor:QColor(33,33,33)); p.drawText(QRect(24,72,width()-48,32), Qt::AlignLeft|Qt::AlignVCenter, d->title); p.drawText(QRect(24,108,width()-48,20), Qt::AlignLeft|Qt::AlignVCenter, d->subtitle);}
