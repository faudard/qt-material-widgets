#include "loadingprogresssettingseditor.h"

#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>

#include "qtmaterialprogress.h"
#include "qtmaterialcircularprogress.h"

LoadingProgressSettingsEditor::LoadingProgressSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    m_linear = new QtMaterialProgress;
    m_circular = new QtMaterialCircularProgress;
    m_showLabels = new QCheckBox(tr("Show percentage"));
    m_roundedCaps = new QCheckBox(tr("Rounded caps"));
    m_thickness = new QSlider(Qt::Horizontal);
    m_value = new QSlider(Qt::Horizontal);
    m_mode = new QComboBox;

    m_mode->addItem(tr("Determinate"), Material::DeterminateProgress);
    m_mode->addItem(tr("Indeterminate"), Material::IndeterminateProgress);

    m_thickness->setRange(2, 12);
    m_thickness->setValue(6);

    m_value->setRange(0, 100);
    m_value->setValue(45);

    m_roundedCaps->setChecked(true);

    m_linear->setRange(0, 100);
    m_linear->setValue(45);

    m_circular->setRange(0, 100);
    m_circular->setValue(45);

    QVBoxLayout *controls = new QVBoxLayout;
    controls->addWidget(m_showLabels);
    controls->addWidget(m_roundedCaps);
    controls->addWidget(new QLabel(tr("Thickness")));
    controls->addWidget(m_thickness);
    controls->addWidget(new QLabel(tr("Value")));
    controls->addWidget(m_value);
    controls->addWidget(new QLabel(tr("Mode")));
    controls->addWidget(m_mode);
    controls->addStretch();

    QVBoxLayout *preview = new QVBoxLayout;
    preview->addWidget(m_linear);
    preview->addSpacing(24);
    preview->addWidget(m_circular, 0, Qt::AlignHCenter);
    preview->addStretch();

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addLayout(preview, 2);
    layout->addLayout(controls, 1);

    connect(m_showLabels, SIGNAL(toggled(bool)), this, SLOT(updateWidgets()));
    connect(m_roundedCaps, SIGNAL(toggled(bool)), this, SLOT(updateWidgets()));
    connect(m_thickness, SIGNAL(valueChanged(int)), this, SLOT(updateWidgets()));
    connect(m_value, SIGNAL(valueChanged(int)), this, SLOT(updateWidgets()));
    connect(m_mode, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidgets()));

    updateWidgets();
}

void LoadingProgressSettingsEditor::updateWidgets()
{
    const Material::ProgressType type = static_cast<Material::ProgressType>(
        m_mode->currentData().toInt());

    m_linear->setProgressType(type);
    m_linear->setTrackThickness(m_thickness->value());
    m_linear->setRoundedCaps(m_roundedCaps->isChecked());
    m_linear->setShowPercentage(m_showLabels->isChecked());
    m_linear->setValue(m_value->value());

    m_circular->setProgressType(type);
    m_circular->setLineWidth(m_thickness->value());
    m_circular->setRoundedCaps(m_roundedCaps->isChecked());
    m_circular->setShowPercentage(m_showLabels->isChecked());
    m_circular->setValue(m_value->value());
}
