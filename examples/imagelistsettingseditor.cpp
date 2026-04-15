#include "imagelistsettingseditor.h"
#include <qtmaterialimagelist.h>

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QSpinBox>
#include <QStandardItemModel>
#include <QVBoxLayout>

ImageListSettingsEditor::ImageListSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    m_list = new QtMaterialImageList(this);
    m_masonryCheckBox = new QCheckBox("Masonry mode", this);
    m_overlayCheckBox = new QCheckBox("Overlay text", this);
    m_widthSpinBox = new QSpinBox(this);
    m_spacingSpinBox = new QSpinBox(this);

    setupForm();
    setupList();
    updateWidget();
}

void ImageListSettingsEditor::setupForm()
{
    m_widthSpinBox->setRange(120, 320);
    m_widthSpinBox->setValue(180);

    m_spacingSpinBox->setRange(0, 40);
    m_spacingSpinBox->setValue(12);

    m_overlayCheckBox->setChecked(true);

    QVBoxLayout *controls = new QVBoxLayout;
    controls->addWidget(m_masonryCheckBox);
    controls->addWidget(m_overlayCheckBox);

    QHBoxLayout *widthRow = new QHBoxLayout;
    widthRow->addWidget(new QLabel("Column width"));
    widthRow->addWidget(m_widthSpinBox);
    controls->addLayout(widthRow);

    QHBoxLayout *spacingRow = new QHBoxLayout;
    spacingRow->addWidget(new QLabel("Spacing"));
    spacingRow->addWidget(m_spacingSpinBox);
    controls->addLayout(spacingRow);
    controls->addStretch(1);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_list, 1);
    layout->addLayout(controls);

    connect(m_masonryCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_overlayCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_widthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_spacingSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
}

void ImageListSettingsEditor::setupList()
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel *>(m_list->model());

    for (int i = 0; i < 8; ++i) {
        QtMaterialImageListItem *item = new QtMaterialImageListItem(QString("Image %1").arg(i + 1));
        item->setSecondaryText(QString("Supporting text %1").arg(i + 1));
        QPixmap px(320, 220 + (i % 3) * 40);
        px.fill(QColor::fromHsv((i * 35) % 360, 96, 220));
        item->setPixmap(px);
        item->setMasonryHeight(140 + (i % 3) * 44);
        item->setOverlayTextEnabled(i % 2 == 0);
        model->appendRow(item);
    }
}

void ImageListSettingsEditor::updateWidget()
{
    m_list->setMasonryMode(m_masonryCheckBox->isChecked());
    m_list->setShowOverlayText(m_overlayCheckBox->isChecked());
    m_list->setColumnWidth(m_widthSpinBox->value());
    m_list->setItemSpacing(m_spacingSpinBox->value());
}
