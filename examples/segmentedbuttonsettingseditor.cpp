#include "segmentedbuttonsettingseditor.h"
#include "qtmaterialsegmentedbutton.h"
#include "qtmaterialavatar.h"

#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QStyle>

SegmentedButtonSettingsEditor::SegmentedButtonSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *title = new QLabel(tr("Segmented Button"));
    title->setStyleSheet("font-size: 18px; font-weight: bold;");

    m_segmentedButton = new QtMaterialSegmentedButton;
    m_segmentedButton->addSegment(tr("Day"), style()->standardIcon(QStyle::SP_FileDialogDetailedView));
    m_segmentedButton->addSegment(tr("Week"), style()->standardIcon(QStyle::SP_FileDialogListView));
    m_segmentedButton->addSegment(tr("Month"), style()->standardIcon(QStyle::SP_DesktopIcon));
    m_segmentedButton->setCurrentIndex(0);

    m_useThemeColors = new QCheckBox(tr("Use theme colors"));
    m_useThemeColors->setChecked(true);
    m_exclusive = new QCheckBox(tr("Exclusive"));
    m_exclusive->setChecked(true);
    m_showIcons = new QCheckBox(tr("Show icons"));
    m_showIcons->setChecked(true);

    connect(m_useThemeColors, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_exclusive, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_showIcons, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));

    layout->addWidget(title);
    layout->addWidget(m_segmentedButton);
    layout->addSpacing(16);
    layout->addWidget(m_useThemeColors);
    layout->addWidget(m_exclusive);
    layout->addWidget(m_showIcons);
    layout->addStretch(1);
}

void SegmentedButtonSettingsEditor::updateWidget()
{
    m_segmentedButton->setUseThemeColors(m_useThemeColors->isChecked());
    m_segmentedButton->setExclusive(m_exclusive->isChecked());
    m_segmentedButton->setShowIcons(m_showIcons->isChecked());
}
