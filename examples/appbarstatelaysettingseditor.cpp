#include "appbarstatelaysettingseditor.h"
#include "qtmaterialappbarstatelayer.h"

#include <QVBoxLayout>
#include <QSlider>
#include <QCheckBox>
#include <QLabel>

AppBarStateLayerSettingsEditor::AppBarStateLayerSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel("App bar state layer preview", this);
    m_layer = new QtMaterialAppBarStateLayer(this);
    m_layer->setMinimumHeight(64);

    m_progressSlider = new QSlider(Qt::Horizontal, this);
    m_progressSlider->setRange(0, 100);

    m_liftOnScroll = new QCheckBox("Lift on scroll", this);
    m_liftOnScroll->setChecked(true);

    layout->addWidget(label);
    layout->addWidget(m_layer);
    layout->addWidget(m_progressSlider);
    layout->addWidget(m_liftOnScroll);
    layout->addStretch(1);

    connect(m_progressSlider, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_liftOnScroll, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));

    updateWidget();
}

void AppBarStateLayerSettingsEditor::updateWidget()
{
    m_layer->setScrollProgress(m_progressSlider->value() / 100.0);
    m_layer->setLiftOnScroll(m_liftOnScroll->isChecked());
}
