#include "carouselsettingseditor.h"

#include <QCheckBox>
#include <QColor>
#include <QFormLayout>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QPalette>
#include <QSpinBox>
#include <QVBoxLayout>

#include "qtmaterialcarousel.h"

static QWidget *createSlide(const QString &title, const QString &subtitle, const QColor &color)
{
    QFrame *frame = new QFrame;
    frame->setMinimumSize(320, 180);
    frame->setAutoFillBackground(true);

    QPalette palette = frame->palette();
    palette.setColor(QPalette::Window, color);
    frame->setPalette(palette);

    QLabel *headline = new QLabel(title);
    headline->setStyleSheet("font-size: 20px; color: white; font-weight: 600;");

    QLabel *body = new QLabel(subtitle);
    body->setStyleSheet("font-size: 13px; color: rgba(255,255,255,0.85);");
    body->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addStretch();
    layout->addWidget(headline);
    layout->addWidget(body);
    frame->setLayout(layout);

    return frame;
}

CarouselSettingsEditor::CarouselSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    m_carousel = new QtMaterialCarousel;
    m_carousel->addSlide(createSlide("Discover", "A simple first-pass Material carousel foundation.", QColor("#546E7A")));
    m_carousel->addSlide(createSlide("Promote", "Use slides for highlights, tutorials, or product tiles.", QColor("#5E35B1")));
    m_carousel->addSlide(createSlide("Navigate", "Indicators and autoplay keep the demo self-contained.", QColor("#00897B")));

    m_autoPlayCheckBox = new QCheckBox;
    m_wrapCheckBox = new QCheckBox;
    m_indicatorsCheckBox = new QCheckBox;
    m_intervalSpinBox = new QSpinBox;

    m_autoPlayCheckBox->setChecked(false);
    m_wrapCheckBox->setChecked(true);
    m_indicatorsCheckBox->setChecked(true);
    m_intervalSpinBox->setRange(500, 10000);
    m_intervalSpinBox->setSingleStep(250);
    m_intervalSpinBox->setValue(3500);

    QFormLayout *controls = new QFormLayout;
    controls->addRow("Auto play", m_autoPlayCheckBox);
    controls->addRow("Wrap", m_wrapCheckBox);
    controls->addRow("Show indicators", m_indicatorsCheckBox);
    controls->addRow("Interval (ms)", m_intervalSpinBox);

    QVBoxLayout *preview = new QVBoxLayout;
    preview->addWidget(m_carousel);
    preview->addStretch();

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addLayout(controls);
    layout->addLayout(preview, 1);
    setLayout(layout);

    connect(m_autoPlayCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_wrapCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_indicatorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_intervalSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));

    updateWidget();
}

void CarouselSettingsEditor::updateWidget()
{
    m_carousel->setAutoPlay(m_autoPlayCheckBox->isChecked());
    m_carousel->setWrap(m_wrapCheckBox->isChecked());
    m_carousel->setShowIndicators(m_indicatorsCheckBox->isChecked());
    m_carousel->setAutoPlayInterval(m_intervalSpinBox->value());
}
