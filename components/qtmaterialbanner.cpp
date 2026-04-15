#include "qtmaterialbanner.h"
#include "qtmaterialbanner_p.h"

#include <QLabel>
#include <QToolButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QStyle>
#include <QStyleOption>
#include <QPaintEvent>

QtMaterialBannerPrivate::QtMaterialBannerPrivate(QtMaterialBanner *q)
    : q_ptr(q),
      useThemeColors(true),
      showLeadingIcon(false),
      dismissible(true),
      iconLabel(0),
      textLabel(0),
      supportingLabel(0),
      primaryButton(0),
      secondaryButton(0),
      dismissButton(0),
      mainLayout(0),
      textLayout(0)
{
}

QtMaterialBannerPrivate::~QtMaterialBannerPrivate()
{
}

void QtMaterialBannerPrivate::init()
{
    Q_Q(QtMaterialBanner);

    iconLabel = new QLabel(q);
    textLabel = new QLabel(q);
    supportingLabel = new QLabel(q);
    primaryButton = new QToolButton(q);
    secondaryButton = new QToolButton(q);
    dismissButton = new QToolButton(q);

    iconLabel->setVisible(false);
    textLabel->setWordWrap(true);
    supportingLabel->setWordWrap(true);

    primaryButton->setAutoRaise(true);
    secondaryButton->setAutoRaise(true);
    dismissButton->setAutoRaise(true);
    dismissButton->setText(QStringLiteral("✕"));

    textLayout = new QVBoxLayout;
    textLayout->setContentsMargins(0, 0, 0, 0);
    textLayout->setSpacing(2);
    textLayout->addWidget(textLabel);
    textLayout->addWidget(supportingLabel);

    mainLayout = new QHBoxLayout(q);
    mainLayout->setContentsMargins(16, 12, 16, 12);
    mainLayout->setSpacing(12);
    mainLayout->addWidget(iconLabel, 0, Qt::AlignTop);
    mainLayout->addLayout(textLayout, 1);
    mainLayout->addWidget(secondaryButton, 0, Qt::AlignVCenter);
    mainLayout->addWidget(primaryButton, 0, Qt::AlignVCenter);
    mainLayout->addWidget(dismissButton, 0, Qt::AlignTop);

    QObject::connect(primaryButton, SIGNAL(clicked()), q, SIGNAL(primaryActionTriggered()));
    QObject::connect(secondaryButton, SIGNAL(clicked()), q, SIGNAL(secondaryActionTriggered()));
    QObject::connect(dismissButton, SIGNAL(clicked()), q, SLOT(dismiss()));

    q->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    q->updateLayoutState();
}

QtMaterialBanner::QtMaterialBanner(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialBannerPrivate(this))
{
    d_func()->init();
}

QtMaterialBanner::~QtMaterialBanner()
{
}

void QtMaterialBanner::setUseThemeColors(bool value)
{
    Q_D(QtMaterialBanner);
    if (d->useThemeColors == value) {
        return;
    }
    d->useThemeColors = value;
    update();
}

bool QtMaterialBanner::useThemeColors() const
{
    Q_D(const QtMaterialBanner);
    return d->useThemeColors;
}

void QtMaterialBanner::setText(const QString &text)
{
    Q_D(QtMaterialBanner);
    d->text = text;
    d->textLabel->setText(text);
    updateGeometry();
}

QString QtMaterialBanner::text() const
{
    Q_D(const QtMaterialBanner);
    return d->text;
}

void QtMaterialBanner::setSupportingText(const QString &text)
{
    Q_D(QtMaterialBanner);
    d->supportingText = text;
    d->supportingLabel->setText(text);
    updateLayoutState();
}

QString QtMaterialBanner::supportingText() const
{
    Q_D(const QtMaterialBanner);
    return d->supportingText;
}

void QtMaterialBanner::setLeadingIcon(const QIcon &icon)
{
    Q_D(QtMaterialBanner);
    d->leadingIcon = icon;
    d->iconLabel->setPixmap(icon.pixmap(24, 24));
    updateLayoutState();
}

QIcon QtMaterialBanner::leadingIcon() const
{
    Q_D(const QtMaterialBanner);
    return d->leadingIcon;
}

void QtMaterialBanner::setShowLeadingIcon(bool value)
{
    Q_D(QtMaterialBanner);
    d->showLeadingIcon = value;
    updateLayoutState();
}

bool QtMaterialBanner::showLeadingIcon() const
{
    Q_D(const QtMaterialBanner);
    return d->showLeadingIcon;
}

void QtMaterialBanner::setDismissible(bool value)
{
    Q_D(QtMaterialBanner);
    d->dismissible = value;
    updateLayoutState();
}

bool QtMaterialBanner::isDismissible() const
{
    Q_D(const QtMaterialBanner);
    return d->dismissible;
}

void QtMaterialBanner::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialBanner);
    d->backgroundColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialBanner::backgroundColor() const
{
    Q_D(const QtMaterialBanner);
    return d->backgroundColor.isValid() ? d->backgroundColor : QColor(250, 244, 200);
}

void QtMaterialBanner::setTextColor(const QColor &color)
{
    Q_D(QtMaterialBanner);
    d->textColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialBanner::textColor() const
{
    Q_D(const QtMaterialBanner);
    return d->textColor.isValid() ? d->textColor : QColor(0, 0, 0, 222);
}

void QtMaterialBanner::setSupportingTextColor(const QColor &color)
{
    Q_D(QtMaterialBanner);
    d->supportingTextColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialBanner::supportingTextColor() const
{
    Q_D(const QtMaterialBanner);
    return d->supportingTextColor.isValid() ? d->supportingTextColor : QColor(0, 0, 0, 160);
}

void QtMaterialBanner::setAccentColor(const QColor &color)
{
    Q_D(QtMaterialBanner);
    d->accentColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialBanner::accentColor() const
{
    Q_D(const QtMaterialBanner);
    return d->accentColor.isValid() ? d->accentColor : QColor(33, 150, 243);
}

void QtMaterialBanner::setPrimaryActionText(const QString &text)
{
    Q_D(QtMaterialBanner);
    d->primaryActionText = text;
    d->primaryButton->setText(text);
    updateLayoutState();
}

QString QtMaterialBanner::primaryActionText() const
{
    Q_D(const QtMaterialBanner);
    return d->primaryActionText;
}

void QtMaterialBanner::setSecondaryActionText(const QString &text)
{
    Q_D(QtMaterialBanner);
    d->secondaryActionText = text;
    d->secondaryButton->setText(text);
    updateLayoutState();
}

QString QtMaterialBanner::secondaryActionText() const
{
    Q_D(const QtMaterialBanner);
    return d->secondaryActionText;
}

QSize QtMaterialBanner::sizeHint() const
{
    Q_D(const QtMaterialBanner);
    const bool multiline = !d->supportingText.isEmpty();
    return QSize(360, multiline ? 88 : 64);
}

QSize QtMaterialBanner::minimumSizeHint() const
{
    return sizeHint();
}

void QtMaterialBanner::dismiss()
{
    hide();
    emit dismissed();
}

void QtMaterialBanner::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(backgroundColor());
    painter.drawRoundedRect(rect().adjusted(0, 0, -1, -1), 4, 4);

    Q_D(QtMaterialBanner);
    d->textLabel->setStyleSheet(QString("color:%1; font-weight:500;").arg(textColor().name()));
    d->supportingLabel->setStyleSheet(QString("color:%1;").arg(supportingTextColor().name()));
    QString accent = accentColor().name();
    d->primaryButton->setStyleSheet(QString("color:%1; font-weight:600;").arg(accent));
    d->secondaryButton->setStyleSheet(QString("color:%1; font-weight:600;").arg(accent));
    d->dismissButton->setStyleSheet(QString("color:%1;").arg(supportingTextColor().name()));
}

void QtMaterialBanner::updateLayoutState()
{
    Q_D(QtMaterialBanner);
    d->iconLabel->setVisible(d->showLeadingIcon && !d->leadingIcon.isNull());
    d->supportingLabel->setVisible(!d->supportingText.isEmpty());
    d->primaryButton->setVisible(!d->primaryActionText.isEmpty());
    d->secondaryButton->setVisible(!d->secondaryActionText.isEmpty());
    d->dismissButton->setVisible(d->dismissible);
    updateGeometry();
    update();
}
