#include "qtmaterialsmalltopappbar.h"
#include "qtmaterialsmalltopappbar_p.h"
#include <QPainter>
QtMaterialSmallTopAppBarPrivate::QtMaterialSmallTopAppBarPrivate(QtMaterialSmallTopAppBar *q) : q_ptr(q), useThemeColors(true), showDivider(false) {}
QtMaterialSmallTopAppBarPrivate::~QtMaterialSmallTopAppBarPrivate() {}
void QtMaterialSmallTopAppBarPrivate::init() {}
QtMaterialSmallTopAppBar::QtMaterialSmallTopAppBar(QWidget *parent) : QWidget(parent), d_ptr(new QtMaterialSmallTopAppBarPrivate(this)) { d_func()->init(); }
QtMaterialSmallTopAppBar::~QtMaterialSmallTopAppBar() {}
void QtMaterialSmallTopAppBar::setUseThemeColors(bool value){Q_D(QtMaterialSmallTopAppBar); d->useThemeColors=value; update();}
bool QtMaterialSmallTopAppBar::useThemeColors() const{Q_D(const QtMaterialSmallTopAppBar); return d->useThemeColors;}
void QtMaterialSmallTopAppBar::setForegroundColor(const QColor &color){Q_D(QtMaterialSmallTopAppBar); d->foregroundColor=color; d->useThemeColors=false; update();}
QColor QtMaterialSmallTopAppBar::foregroundColor() const{Q_D(const QtMaterialSmallTopAppBar); return d->foregroundColor;}
void QtMaterialSmallTopAppBar::setBackgroundColor(const QColor &color){Q_D(QtMaterialSmallTopAppBar); d->backgroundColor=color; d->useThemeColors=false; update();}
QColor QtMaterialSmallTopAppBar::backgroundColor() const{Q_D(const QtMaterialSmallTopAppBar); return d->backgroundColor;}
void QtMaterialSmallTopAppBar::setShowDivider(bool value){Q_D(QtMaterialSmallTopAppBar); d->showDivider=value; update();}
bool QtMaterialSmallTopAppBar::showDivider() const{Q_D(const QtMaterialSmallTopAppBar); return d->showDivider;}
QSize QtMaterialSmallTopAppBar::sizeHint() const { return QSize(-1, 64); }
void QtMaterialSmallTopAppBar::paintEvent(QPaintEvent *){Q_D(QtMaterialSmallTopAppBar); QPainter p(this); p.fillRect(rect(), d->backgroundColor.isValid()?d->backgroundColor:QColor(250,250,250)); if(d->showDivider) p.fillRect(QRect(0,height()-1,width(),1), QColor(220,220,220));}
