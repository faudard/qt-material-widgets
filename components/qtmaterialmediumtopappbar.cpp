#include "qtmaterialmediumtopappbar.h"
#include "qtmaterialmediumtopappbar_p.h"
#include <QPainter>
QtMaterialMediumTopAppBarPrivate::QtMaterialMediumTopAppBarPrivate(QtMaterialMediumTopAppBar *q): q_ptr(q), useThemeColors(true) {}
QtMaterialMediumTopAppBarPrivate::~QtMaterialMediumTopAppBarPrivate() {}
void QtMaterialMediumTopAppBarPrivate::init() {}
QtMaterialMediumTopAppBar::QtMaterialMediumTopAppBar(QWidget *parent): QWidget(parent), d_ptr(new QtMaterialMediumTopAppBarPrivate(this)) { d_func()->init(); }
QtMaterialMediumTopAppBar::~QtMaterialMediumTopAppBar() {}
void QtMaterialMediumTopAppBar::setUseThemeColors(bool value){Q_D(QtMaterialMediumTopAppBar); d->useThemeColors=value; update();}
bool QtMaterialMediumTopAppBar::useThemeColors() const{Q_D(const QtMaterialMediumTopAppBar); return d->useThemeColors;}
void QtMaterialMediumTopAppBar::setForegroundColor(const QColor &color){Q_D(QtMaterialMediumTopAppBar); d->foregroundColor=color; d->useThemeColors=false; update();}
QColor QtMaterialMediumTopAppBar::foregroundColor() const{Q_D(const QtMaterialMediumTopAppBar); return d->foregroundColor;}
void QtMaterialMediumTopAppBar::setBackgroundColor(const QColor &color){Q_D(QtMaterialMediumTopAppBar); d->backgroundColor=color; d->useThemeColors=false; update();}
QColor QtMaterialMediumTopAppBar::backgroundColor() const{Q_D(const QtMaterialMediumTopAppBar); return d->backgroundColor;}
void QtMaterialMediumTopAppBar::setTitle(const QString &text){Q_D(QtMaterialMediumTopAppBar); d->title=text; update();}
QString QtMaterialMediumTopAppBar::title() const{Q_D(const QtMaterialMediumTopAppBar); return d->title;}
void QtMaterialMediumTopAppBar::setSubtitle(const QString &text){Q_D(QtMaterialMediumTopAppBar); d->subtitle=text; update();}
QString QtMaterialMediumTopAppBar::subtitle() const{Q_D(const QtMaterialMediumTopAppBar); return d->subtitle;}
QSize QtMaterialMediumTopAppBar::sizeHint() const { return QSize(-1, 112); }
void QtMaterialMediumTopAppBar::paintEvent(QPaintEvent *){Q_D(QtMaterialMediumTopAppBar); QPainter p(this); p.fillRect(rect(), d->backgroundColor.isValid()?d->backgroundColor:QColor(250,250,250)); p.setPen(d->foregroundColor.isValid()?d->foregroundColor:QColor(33,33,33)); p.drawText(QRect(24,40,width()-48,24), Qt::AlignLeft|Qt::AlignVCenter, d->title); p.drawText(QRect(24,68,width()-48,18), Qt::AlignLeft|Qt::AlignVCenter, d->subtitle);}
