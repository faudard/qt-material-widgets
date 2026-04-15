#include "skeletonsettingseditor.h"

#include "qtmaterialcheckbox.h"
#include "qtmaterialraisedbutton.h"
#include "qtmaterialskeleton.h"

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>

SkeletonSettingsEditor::SkeletonSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    m_blockSkeleton = new QtMaterialSkeleton;
    m_textSkeleton = new QtMaterialSkeleton;
    m_avatarSkeleton = new QtMaterialSkeleton;
    m_avatarTextSkeleton = new QtMaterialSkeleton;

    m_textSkeleton->setDisplayMode(QtMaterialSkeleton::TextLines);
    m_textSkeleton->setLineCount(3);
    m_textSkeleton->setMinimumWidth(260);

    m_avatarSkeleton->setCircular(true);
    m_avatarSkeleton->setFixedSize(48, 48);

    m_animationCheckBox = new QtMaterialCheckBox;
    m_animationCheckBox->setText("Animation");
    m_animationCheckBox->setChecked(true);

    m_themeColorsCheckBox = new QtMaterialCheckBox;
    m_themeColorsCheckBox->setText("Use theme colors");
    m_themeColorsCheckBox->setChecked(true);

    m_circularCheckBox = new QtMaterialCheckBox;
    m_circularCheckBox->setText("Block is circular");

    m_modeComboBox = new QComboBox;
    m_modeComboBox->addItem("Single block");
    m_modeComboBox->addItem("Text lines");

    m_linesSlider = new QSlider(Qt::Horizontal);
    m_linesSlider->setRange(1, 5);
    m_linesSlider->setValue(3);

    m_radiusSlider = new QSlider(Qt::Horizontal);
    m_radiusSlider->setRange(0, 16);
    m_radiusSlider->setValue(4);

    QVBoxLayout *controls = new QVBoxLayout;
    controls->addWidget(m_animationCheckBox);
    controls->addWidget(m_themeColorsCheckBox);
    controls->addWidget(m_circularCheckBox);
    controls->addWidget(new QLabel("Display mode"));
    controls->addWidget(m_modeComboBox);
    controls->addWidget(new QLabel("Line count"));
    controls->addWidget(m_linesSlider);
    controls->addWidget(new QLabel("Corner radius"));
    controls->addWidget(m_radiusSlider);
    controls->addStretch(1);

    QVBoxLayout *preview = new QVBoxLayout;
    preview->setSpacing(24);
    preview->addWidget(m_blockSkeleton);
    preview->addWidget(m_textSkeleton);

    m_avatarTextSkeleton->setDisplayMode(QtMaterialSkeleton::TextLines);
    m_avatarTextSkeleton->setLineCount(2);
    m_avatarTextSkeleton->setMinimumWidth(200);

    QHBoxLayout *avatarRow = new QHBoxLayout;
    avatarRow->addWidget(m_avatarSkeleton);
    avatarRow->addWidget(m_avatarTextSkeleton, 1);
    preview->addLayout(avatarRow);
    preview->addStretch(1);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addLayout(controls);
    layout->addSpacing(24);
    layout->addLayout(preview, 1);

    connect(m_animationCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_themeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_circularCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_modeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(m_linesSlider, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_radiusSlider, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));

    updateWidget();
}

void SkeletonSettingsEditor::updateWidget()
{
    const bool animation = m_animationCheckBox->isChecked();
    const bool themeColors = m_themeColorsCheckBox->isChecked();
    const bool circular = m_circularCheckBox->isChecked();
    const QtMaterialSkeleton::DisplayMode mode =
        m_modeComboBox->currentIndex() == 0 ? QtMaterialSkeleton::SingleBlock : QtMaterialSkeleton::TextLines;

    m_blockSkeleton->setUseThemeColors(themeColors);
    m_blockSkeleton->setAnimationEnabled(animation);
    m_blockSkeleton->setCircular(circular);
    m_blockSkeleton->setDisplayMode(mode);
    m_blockSkeleton->setLineCount(m_linesSlider->value());
    m_blockSkeleton->setCornerRadius(m_radiusSlider->value());
    if (circular) {
        m_blockSkeleton->setFixedSize(56, 56);
    } else {
        m_blockSkeleton->setMinimumSize(240, mode == QtMaterialSkeleton::TextLines ? 72 : 24);
        m_blockSkeleton->setMaximumHeight(mode == QtMaterialSkeleton::TextLines ? 96 : 24);
    }

    m_textSkeleton->setUseThemeColors(themeColors);
    m_textSkeleton->setAnimationEnabled(animation);
    m_textSkeleton->setCircular(false);
    m_textSkeleton->setDisplayMode(QtMaterialSkeleton::TextLines);
    m_textSkeleton->setLineCount(m_linesSlider->value());
    m_textSkeleton->setCornerRadius(m_radiusSlider->value());

    m_avatarSkeleton->setUseThemeColors(themeColors);
    m_avatarSkeleton->setAnimationEnabled(animation);
    m_avatarSkeleton->setCircular(true);
    m_avatarSkeleton->setCornerRadius(m_radiusSlider->value());

    m_avatarTextSkeleton->setUseThemeColors(themeColors);
    m_avatarTextSkeleton->setAnimationEnabled(animation);
    m_avatarTextSkeleton->setCircular(false);
    m_avatarTextSkeleton->setDisplayMode(QtMaterialSkeleton::TextLines);
    m_avatarTextSkeleton->setLineCount(qMax(2, m_linesSlider->value() - 1));
    m_avatarTextSkeleton->setCornerRadius(m_radiusSlider->value());
}
