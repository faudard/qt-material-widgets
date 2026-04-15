#include "qtmaterialtoolbar.h"
#include "qtmaterialtoolbar_p.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

#include "lib/qtmaterialstyle.h"

QtMaterialToolBarPrivate::QtMaterialToolBarPrivate(QtMaterialToolBar *q)
    : QtMaterialAppBarPrivate(q),
      dense(false),
      centeredTitle(false),
      titleContainer(0),
      titleLabel(0),
      subtitleLabel(0),
      leadingLayout(0),
      actionsLayout(0),
      titleLayout(0)
{
}

QtMaterialToolBarPrivate::~QtMaterialToolBarPrivate()
{
}

void QtMaterialToolBarPrivate::init()
{
    Q_Q(QtMaterialToolBar);

    leadingLayout = new QHBoxLayout;
    leadingLayout->setSpacing(0);
    leadingLayout->setContentsMargins(0, 0, 0, 0);

    actionsLayout = new QHBoxLayout;
    actionsLayout->setSpacing(0);
    actionsLayout->setContentsMargins(0, 0, 0, 0);

    titleContainer = new QWidget(q);
    titleLayout = new QVBoxLayout;
    titleLayout->setSpacing(0);
    titleLayout->setContentsMargins(0, 0, 0, 0);
    titleContainer->setLayout(titleLayout);

    titleLabel = new QLabel(q);
    subtitleLabel = new QLabel(q);

    titleLabel->setAttribute(Qt::WA_TranslucentBackground);
    subtitleLabel->setAttribute(Qt::WA_TranslucentBackground);

    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(subtitleLabel);

    QHBoxLayout *layout = q->appBarLayout();
    layout->setSpacing(8);
    layout->setContentsMargins(8, 0, 8, 0);
    layout->addLayout(leadingLayout);
    layout->addWidget(titleContainer, 1);
    layout->addLayout(actionsLayout);

    updateLabels();
    updateLayout();
}

void QtMaterialToolBarPrivate::updateLayout()
{
    Q_Q(QtMaterialToolBar);

    Qt::Alignment alignment = centeredTitle
        ? Qt::AlignCenter
        : (Qt::AlignVCenter | Qt::AlignLeft);

    titleLabel->setAlignment(alignment);
    subtitleLabel->setAlignment(alignment);

    subtitleLabel->setVisible(!subtitle.isEmpty());

    QFont titleFont("Roboto", dense ? 16 : 18, QFont::Normal);
    QFont subtitleFont("Roboto", dense ? 10 : 12, QFont::Normal);
    titleLabel->setFont(titleFont);
    subtitleLabel->setFont(subtitleFont);

    const QColor onSurface = q->useThemeColors()
        ? Qt::white
        : q->foregroundColor();

    QPalette titlePalette = titleLabel->palette();
    titlePalette.setColor(titleLabel->foregroundRole(), onSurface);
    titleLabel->setPalette(titlePalette);

    QPalette subtitlePalette = subtitleLabel->palette();
    QColor sub = onSurface;
    sub.setAlpha(180);
    subtitlePalette.setColor(subtitleLabel->foregroundRole(), sub);
    subtitleLabel->setPalette(subtitlePalette);

    q->updateGeometry();
    q->update();
}

void QtMaterialToolBarPrivate::updateLabels()
{
    titleLabel->setText(title);
    subtitleLabel->setText(subtitle);
}

QtMaterialToolBar::QtMaterialToolBar(QWidget *parent)
    : QtMaterialAppBar(*new QtMaterialToolBarPrivate(this), parent)
{
    Q_D(QtMaterialToolBar);
    d->init();
}

QtMaterialToolBar::~QtMaterialToolBar()
{
}

QSize QtMaterialToolBar::sizeHint() const
{
    Q_D(const QtMaterialToolBar);
    return QSize(-1, d->dense ? 56 : 64);
}

void QtMaterialToolBar::setTitle(const QString &title)
{
    Q_D(QtMaterialToolBar);

    if (d->title == title) {
        return;
    }

    d->title = title;
    d->updateLabels();
    d->updateLayout();
}

QString QtMaterialToolBar::title() const
{
    Q_D(const QtMaterialToolBar);
    return d->title;
}

void QtMaterialToolBar::setSubtitle(const QString &subtitle)
{
    Q_D(QtMaterialToolBar);

    if (d->subtitle == subtitle) {
        return;
    }

    d->subtitle = subtitle;
    d->updateLabels();
    d->updateLayout();
}

QString QtMaterialToolBar::subtitle() const
{
    Q_D(const QtMaterialToolBar);
    return d->subtitle;
}

void QtMaterialToolBar::setDense(bool value)
{
    Q_D(QtMaterialToolBar);

    if (d->dense == value) {
        return;
    }

    d->dense = value;
    d->updateLayout();
}

bool QtMaterialToolBar::isDense() const
{
    Q_D(const QtMaterialToolBar);
    return d->dense;
}

void QtMaterialToolBar::setCenteredTitle(bool value)
{
    Q_D(QtMaterialToolBar);

    if (d->centeredTitle == value) {
        return;
    }

    d->centeredTitle = value;
    d->updateLayout();
}

bool QtMaterialToolBar::centeredTitle() const
{
    Q_D(const QtMaterialToolBar);
    return d->centeredTitle;
}

QHBoxLayout *QtMaterialToolBar::leadingLayout() const
{
    Q_D(const QtMaterialToolBar);
    return d->leadingLayout;
}

QHBoxLayout *QtMaterialToolBar::actionsLayout() const
{
    Q_D(const QtMaterialToolBar);
    return d->actionsLayout;
}