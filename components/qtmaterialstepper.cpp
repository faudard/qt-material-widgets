#include "qtmaterialstepper.h"
#include "qtmaterialstepper_p.h"

#include "lib/qtmaterialstyle.h"

#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QStyleOption>

QtMaterialStepperPrivate::QtMaterialStepperPrivate(QtMaterialStepper *q)
    : q_ptr(q)
{
}

QtMaterialStepperPrivate::~QtMaterialStepperPrivate()
{
}

void QtMaterialStepperPrivate::init()
{
    useThemeColors = true;
    orientation = Qt::Horizontal;
    currentStep = 0;
    clickable = true;
    labelsVisible = true;

    circleDiameter = 24;
    lineThickness = 2;
    sideMargin = 24;
    labelSpacing = 12;
    labelHeight = 20;

    Q_Q(QtMaterialStepper);
    q->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    q->setAttribute(Qt::WA_Hover, true);
}

QColor QtMaterialStepperPrivate::themeColor(const QString &key) const
{
    return QtMaterialStyle::instance().themeColor(key);
}

QVector<QPointF> QtMaterialStepperPrivate::stepCenters() const
{
    Q_Q(const QtMaterialStepper);

    QVector<QPointF> result;
    const int count = labels.isEmpty() ? 0 : labels.size();
    if (count <= 0) {
        return result;
    }

    if (orientation == Qt::Horizontal) {
        const qreal y = labelsVisible
                ? (sideMargin + circleDiameter / 2.0)
                : (q->height() / 2.0);
        const qreal available = qMax(0, q->width() - 2 * sideMargin - circleDiameter);
        const qreal spacing = count > 1 ? available / qreal(count - 1) : 0;
        for (int i = 0; i < count; ++i) {
            result.append(QPointF(sideMargin + circleDiameter / 2.0 + i * spacing, y));
        }
    } else {
        const qreal x = sideMargin + circleDiameter / 2.0;
        const qreal available = qMax(0, q->height() - 2 * sideMargin - circleDiameter);
        const qreal spacing = count > 1 ? available / qreal(count - 1) : 0;
        for (int i = 0; i < count; ++i) {
            result.append(QPointF(x, sideMargin + circleDiameter / 2.0 + i * spacing));
        }
    }

    return result;
}

QRectF QtMaterialStepperPrivate::stepRect(int index) const
{
    const QVector<QPointF> centers = stepCenters();
    if (index < 0 || index >= centers.size()) {
        return QRectF();
    }

    const QPointF c = centers.at(index);
    return QRectF(c.x() - circleDiameter / 2.0,
                  c.y() - circleDiameter / 2.0,
                  circleDiameter,
                  circleDiameter);
}

int QtMaterialStepperPrivate::stepAt(const QPoint &pos) const
{
    for (int i = 0; i < labels.size(); ++i) {
        if (stepRect(i).adjusted(-8, -8, 8, 8).contains(pos)) {
            return i;
        }
    }
    return -1;
}

QtMaterialStepper::QtMaterialStepper(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialStepperPrivate(this))
{
    Q_D(QtMaterialStepper);
    d->init();
}

QtMaterialStepper::~QtMaterialStepper()
{
}

void QtMaterialStepper::setUseThemeColors(bool value)
{
    Q_D(QtMaterialStepper);
    if (d->useThemeColors == value) {
        return;
    }
    d->useThemeColors = value;
    update();
}

bool QtMaterialStepper::useThemeColors() const
{
    Q_D(const QtMaterialStepper);
    return d->useThemeColors;
}

void QtMaterialStepper::setOrientation(Qt::Orientation orientation)
{
    Q_D(QtMaterialStepper);
    if (d->orientation == orientation) {
        return;
    }
    d->orientation = orientation;
    updateGeometry();
    update();
}

Qt::Orientation QtMaterialStepper::orientation() const
{
    Q_D(const QtMaterialStepper);
    return d->orientation;
}

void QtMaterialStepper::setCurrentStep(int step)
{
    Q_D(QtMaterialStepper);
    const int bounded = qBound(0, step, qMax(0, d->labels.size() - 1));
    if (d->currentStep == bounded) {
        return;
    }
    d->currentStep = bounded;
    emit currentStepChanged(d->currentStep);
    update();
}

int QtMaterialStepper::currentStep() const
{
    Q_D(const QtMaterialStepper);
    return d->currentStep;
}

void QtMaterialStepper::setClickable(bool value)
{
    Q_D(QtMaterialStepper);
    d->clickable = value;
}

bool QtMaterialStepper::isClickable() const
{
    Q_D(const QtMaterialStepper);
    return d->clickable;
}

void QtMaterialStepper::setShowLabels(bool value)
{
    Q_D(QtMaterialStepper);
    if (d->labelsVisible == value) {
        return;
    }
    d->labelsVisible = value;
    updateGeometry();
    update();
}

bool QtMaterialStepper::showLabels() const
{
    Q_D(const QtMaterialStepper);
    return d->labelsVisible;
}

void QtMaterialStepper::setStepLabels(const QStringList &labels)
{
    Q_D(QtMaterialStepper);
    d->labels = labels;
    d->currentStep = qBound(0, d->currentStep, qMax(0, labels.size() - 1));
    updateGeometry();
    update();
}

QStringList QtMaterialStepper::stepLabels() const
{
    Q_D(const QtMaterialStepper);
    return d->labels;
}

void QtMaterialStepper::addStep(const QString &label)
{
    Q_D(QtMaterialStepper);
    d->labels.append(label);
    updateGeometry();
    update();
}

int QtMaterialStepper::stepCount() const
{
    Q_D(const QtMaterialStepper);
    return d->labels.size();
}

void QtMaterialStepper::setActiveColor(const QColor &color)
{
    Q_D(QtMaterialStepper);
    d->activeColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialStepper::activeColor() const
{
    Q_D(const QtMaterialStepper);
    return d->useThemeColors || !d->activeColor.isValid()
            ? d->themeColor("primary1")
            : d->activeColor;
}

void QtMaterialStepper::setCompletedColor(const QColor &color)
{
    Q_D(QtMaterialStepper);
    d->completedColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialStepper::completedColor() const
{
    Q_D(const QtMaterialStepper);
    return d->useThemeColors || !d->completedColor.isValid()
            ? d->themeColor("accent1")
            : d->completedColor;
}

void QtMaterialStepper::setInactiveColor(const QColor &color)
{
    Q_D(QtMaterialStepper);
    d->inactiveColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialStepper::inactiveColor() const
{
    Q_D(const QtMaterialStepper);
    return d->useThemeColors || !d->inactiveColor.isValid()
            ? d->themeColor("border")
            : d->inactiveColor;
}

void QtMaterialStepper::setTextColor(const QColor &color)
{
    Q_D(QtMaterialStepper);
    d->textColor = color;
    d->useThemeColors = false;
    update();
}

QColor QtMaterialStepper::textColor() const
{
    Q_D(const QtMaterialStepper);
    return d->useThemeColors || !d->textColor.isValid()
            ? d->themeColor("text")
            : d->textColor;
}

QSize QtMaterialStepper::sizeHint() const
{
    Q_D(const QtMaterialStepper);
    const int count = qMax(3, d->labels.size());
    if (d->orientation == Qt::Horizontal) {
        const int h = d->sideMargin * 2 + d->circleDiameter + (d->labelsVisible ? d->labelSpacing + d->labelHeight : 0);
        return QSize(120 * count, h);
    }
    const int w = d->sideMargin * 2 + d->circleDiameter + (d->labelsVisible ? 120 : 0);
    return QSize(w, 72 * count);
}

QSize QtMaterialStepper::minimumSizeHint() const
{
    Q_D(const QtMaterialStepper);
    const int count = qMax(2, d->labels.size());
    if (d->orientation == Qt::Horizontal) {
        const int h = d->sideMargin * 2 + d->circleDiameter + (d->labelsVisible ? d->labelSpacing + d->labelHeight : 0);
        return QSize(72 * count, h);
    }
    const int w = d->sideMargin * 2 + d->circleDiameter + (d->labelsVisible ? 80 : 0);
    return QSize(w, 56 * count);
}

void QtMaterialStepper::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialStepper);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const QVector<QPointF> centers = d->stepCenters();
    if (centers.isEmpty()) {
        return;
    }

    const QColor active = activeColor();
    const QColor completed = completedColor();
    const QColor inactive = inactiveColor();
    const QColor labelColor = textColor();

    QPen linePen;
    linePen.setWidth(d->lineThickness);
    linePen.setCapStyle(Qt::RoundCap);

    for (int i = 0; i < centers.size() - 1; ++i) {
        linePen.setColor(i < d->currentStep ? completed : inactive);
        painter.setPen(linePen);
        painter.drawLine(centers.at(i), centers.at(i + 1));
    }

    QFont circleFont(font());
    circleFont.setBold(true);
    circleFont.setPixelSize(11);
    painter.setFont(circleFont);

    for (int i = 0; i < centers.size(); ++i) {
        const QRectF rect = d->stepRect(i);
        const bool isCurrent = (i == d->currentStep);
        const bool isCompleted = (i < d->currentStep);
        const QColor fill = isCurrent ? active : (isCompleted ? completed : palette().window().color());
        const QColor stroke = isCurrent ? active : (isCompleted ? completed : inactive);
        const QColor stepText = isCurrent || isCompleted ? palette().window().color() : labelColor;

        painter.setPen(QPen(stroke, 2));
        painter.setBrush(fill);
        painter.drawEllipse(rect);

        painter.setPen(stepText);
        const QString marker = isCompleted ? QString::fromUtf8("✓") : QString::number(i + 1);
        painter.drawText(rect, Qt::AlignCenter, marker);

        if (d->labelsVisible && i < d->labels.size()) {
            painter.setPen(labelColor);
            QFont labelFont(font());
            labelFont.setPixelSize(12);
            painter.setFont(labelFont);

            QRectF labelRect;
            if (d->orientation == Qt::Horizontal) {
                labelRect = QRectF(rect.center().x() - 48,
                                   rect.bottom() + d->labelSpacing / 2.0,
                                   96,
                                   d->labelHeight + 18);
                painter.drawText(labelRect, Qt::AlignHCenter | Qt::AlignTop | Qt::TextWordWrap, d->labels.at(i));
            } else {
                labelRect = QRectF(rect.right() + d->labelSpacing,
                                   rect.center().y() - 10,
                                   qMax(80, width() - int(rect.right()) - d->labelSpacing - d->sideMargin),
                                   20);
                painter.drawText(labelRect, Qt::AlignVCenter | Qt::AlignLeft | Qt::TextSingleLine, d->labels.at(i));
            }
        }
    }
}

void QtMaterialStepper::mousePressEvent(QMouseEvent *event)
{
    Q_D(QtMaterialStepper);
    if (!d->clickable) {
        QWidget::mousePressEvent(event);
        return;
    }

    const int step = d->stepAt(event->pos());
    if (step >= 0) {
        emit stepClicked(step);
        setCurrentStep(step);
        event->accept();
        return;
    }

    QWidget::mousePressEvent(event);
}
