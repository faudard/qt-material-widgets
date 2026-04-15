#include "qtmaterialexpansionpanel.h"
#include "qtmaterialexpansionpanel_p.h"
#include "lib/qtmaterialstyle.h"

#include <QEvent>
#include <QLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <QWidget>

QtMaterialExpansionPanelPrivate::QtMaterialExpansionPanelPrivate(QtMaterialExpansionPanel *q)
    : q_ptr(q),
      useThemeColors(true),
      expanded(false),
      collapsible(true),
      showDivider(true),
      bodyWidget(0),
      rootLayout(0),
      contentLayout(0)
{
}

void QtMaterialExpansionPanelPrivate::init()
{
    Q_Q(QtMaterialExpansionPanel);

    bodyWidget = new QWidget(q);
    bodyWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    bodyWidget->setVisible(expanded);

    rootLayout = new QVBoxLayout(q);
    rootLayout->setContentsMargins(0, headerHeight(), 0, 0);
    rootLayout->setSpacing(0);
    rootLayout->addWidget(bodyWidget);

    q->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    q->setAttribute(Qt::WA_Hover);
}

QColor QtMaterialExpansionPanelPrivate::resolvedBackgroundColor() const
{
    if (!useThemeColors && backgroundColor.isValid()) {
        return backgroundColor;
    }
    return QtMaterialStyle::instance().themeColor("canvas");
}

QColor QtMaterialExpansionPanelPrivate::resolvedTextColor() const
{
    if (!useThemeColors && textColor.isValid()) {
        return textColor;
    }
    return QtMaterialStyle::instance().themeColor("text");
}

QColor QtMaterialExpansionPanelPrivate::resolvedSecondaryTextColor() const
{
    if (!useThemeColors && secondaryTextColor.isValid()) {
        return secondaryTextColor;
    }
    return QtMaterialStyle::instance().themeColor("accent3");
}

QColor QtMaterialExpansionPanelPrivate::resolvedAccentColor() const
{
    if (!useThemeColors && accentColor.isValid()) {
        return accentColor;
    }
    return QtMaterialStyle::instance().themeColor("primary1");
}

int QtMaterialExpansionPanelPrivate::headerHeight() const
{
    return subtitle.isEmpty() ? 56 : 72;
}

int QtMaterialExpansionPanelPrivate::bodyHeightHint() const
{
    return bodyWidget ? bodyWidget->sizeHint().height() : 0;
}

QtMaterialExpansionPanel::QtMaterialExpansionPanel(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialExpansionPanelPrivate(this))
{
    Q_D(QtMaterialExpansionPanel);
    d->init();
}

QtMaterialExpansionPanel::~QtMaterialExpansionPanel()
{
}

void QtMaterialExpansionPanel::setUseThemeColors(bool value)
{
    Q_D(QtMaterialExpansionPanel);
    if (d->useThemeColors == value) {
        return;
    }
    d->useThemeColors = value;
    update();
}

bool QtMaterialExpansionPanel::useThemeColors() const
{
    Q_D(const QtMaterialExpansionPanel);
    return d->useThemeColors;
}

void QtMaterialExpansionPanel::setTitle(const QString &title)
{
    Q_D(QtMaterialExpansionPanel);
    d->title = title;
    updateGeometry();
    update();
}

QString QtMaterialExpansionPanel::title() const
{
    Q_D(const QtMaterialExpansionPanel);
    return d->title;
}

void QtMaterialExpansionPanel::setSubtitle(const QString &subtitle)
{
    Q_D(QtMaterialExpansionPanel);
    d->subtitle = subtitle;
    if (d->rootLayout) {
        d->rootLayout->setContentsMargins(0, d->headerHeight(), 0, 0);
    }
    updateGeometry();
    update();
}

QString QtMaterialExpansionPanel::subtitle() const
{
    Q_D(const QtMaterialExpansionPanel);
    return d->subtitle;
}

void QtMaterialExpansionPanel::setHeaderIcon(const QIcon &icon)
{
    Q_D(QtMaterialExpansionPanel);
    d->headerIcon = icon;
    update();
}

QIcon QtMaterialExpansionPanel::headerIcon() const
{
    Q_D(const QtMaterialExpansionPanel);
    return d->headerIcon;
}

void QtMaterialExpansionPanel::setContentLayout(QLayout *layout)
{
    Q_D(QtMaterialExpansionPanel);

    if (!d->bodyWidget) {
        return;
    }

    if (d->contentLayout == layout) {
        return;
    }

    delete d->bodyWidget->layout();
    d->bodyWidget->setLayout(layout);
    d->contentLayout = layout;
    updateGeometry();
}

QLayout *QtMaterialExpansionPanel::contentLayout() const
{
    Q_D(const QtMaterialExpansionPanel);
    return d->contentLayout;
}

void QtMaterialExpansionPanel::setExpanded(bool value)
{
    Q_D(QtMaterialExpansionPanel);
    if (d->expanded == value) {
        return;
    }
    d->expanded = value;
    if (d->bodyWidget) {
        d->bodyWidget->setVisible(value);
    }
    updateGeometry();
    update();
    emit expandedChanged(value);
}

bool QtMaterialExpansionPanel::isExpanded() const
{
    Q_D(const QtMaterialExpansionPanel);
    return d->expanded;
}

void QtMaterialExpansionPanel::expand()
{
    setExpanded(true);
}

void QtMaterialExpansionPanel::collapse()
{
    setExpanded(false);
}

void QtMaterialExpansionPanel::toggle()
{
    setExpanded(!isExpanded());
}

void QtMaterialExpansionPanel::setCollapsible(bool value)
{
    Q_D(QtMaterialExpansionPanel);
    d->collapsible = value;
}

bool QtMaterialExpansionPanel::isCollapsible() const
{
    Q_D(const QtMaterialExpansionPanel);
    return d->collapsible;
}

void QtMaterialExpansionPanel::setShowDivider(bool value)
{
    Q_D(QtMaterialExpansionPanel);
    d->showDivider = value;
    update();
}

bool QtMaterialExpansionPanel::showDivider() const
{
    Q_D(const QtMaterialExpansionPanel);
    return d->showDivider;
}

void QtMaterialExpansionPanel::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialExpansionPanel);
    d->backgroundColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialExpansionPanel::backgroundColor() const
{
    Q_D(const QtMaterialExpansionPanel);
    return d->backgroundColor;
}

void QtMaterialExpansionPanel::setTextColor(const QColor &color)
{
    Q_D(QtMaterialExpansionPanel);
    d->textColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialExpansionPanel::textColor() const
{
    Q_D(const QtMaterialExpansionPanel);
    return d->textColor;
}

void QtMaterialExpansionPanel::setSecondaryTextColor(const QColor &color)
{
    Q_D(QtMaterialExpansionPanel);
    d->secondaryTextColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialExpansionPanel::secondaryTextColor() const
{
    Q_D(const QtMaterialExpansionPanel);
    return d->secondaryTextColor;
}

void QtMaterialExpansionPanel::setAccentColor(const QColor &color)
{
    Q_D(QtMaterialExpansionPanel);
    d->accentColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialExpansionPanel::accentColor() const
{
    Q_D(const QtMaterialExpansionPanel);
    return d->accentColor;
}

bool QtMaterialExpansionPanel::event(QEvent *event)
{
    if (event->type() == QEvent::LayoutRequest) {
        updateGeometry();
    }
    return QWidget::event(event);
}

void QtMaterialExpansionPanel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialExpansionPanel);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.fillRect(rect(), d->resolvedBackgroundColor());

    const int headerH = d->headerHeight();
    const QRect headerRect(0, 0, width(), headerH);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, underMouse() ? 10 : 0));
    painter.drawRect(headerRect);

    int left = 16;
    if (!d->headerIcon.isNull()) {
        QRect iconRect(16, (headerH - 24) / 2, 24, 24);
        d->headerIcon.paint(&painter, iconRect);
        left = iconRect.right() + 16;
    }

    painter.setPen(d->resolvedTextColor());
    QFont titleFont = font();
    titleFont.setBold(true);
    painter.setFont(titleFont);
    painter.drawText(QRect(left, d->subtitle.isEmpty() ? 0 : 12, width() - left - 48, 24),
                     Qt::AlignLeft | Qt::AlignVCenter, d->title);

    if (!d->subtitle.isEmpty()) {
        painter.setPen(d->resolvedSecondaryTextColor());
        QFont subtitleFont = font();
        subtitleFont.setPointSize(qMax(8, subtitleFont.pointSize() - 1));
        painter.setFont(subtitleFont);
        painter.drawText(QRect(left, 34, width() - left - 48, 20),
                         Qt::AlignLeft | Qt::AlignVCenter, d->subtitle);
    }

    painter.setPen(QPen(d->resolvedAccentColor(), 2));
    const int cx = width() - 24;
    const int cy = headerH / 2;
    if (d->expanded) {
        painter.drawLine(cx - 5, cy - 2, cx, cy + 3);
        painter.drawLine(cx, cy + 3, cx + 5, cy - 2);
    } else {
        painter.drawLine(cx - 5, cy - 3, cx, cy + 2);
        painter.drawLine(cx, cy + 2, cx + 5, cy - 3);
    }

    if (d->showDivider) {
        painter.setPen(QColor(0, 0, 0, 30));
        painter.drawLine(0, height() - 1, width(), height() - 1);
    }
}

void QtMaterialExpansionPanel::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(QtMaterialExpansionPanel);

    if (event->button() == Qt::LeftButton && QRect(0, 0, width(), d->headerHeight()).contains(event->pos())) {
        emit headerClicked();
        if (d->collapsible) {
            toggle();
        }
        event->accept();
        return;
    }

    QWidget::mouseReleaseEvent(event);
}

QSize QtMaterialExpansionPanel::sizeHint() const
{
    Q_D(const QtMaterialExpansionPanel);
    return QSize(320, d->headerHeight() + (d->expanded ? d->bodyHeightHint() : 0));
}

QSize QtMaterialExpansionPanel::minimumSizeHint() const
{
    Q_D(const QtMaterialExpansionPanel);
    return QSize(160, d->headerHeight());
}
