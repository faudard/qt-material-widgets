#include "gridlistsettingseditor.h"

#include <QCheckBox>
#include <QColorDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QStandardItemModel>
#include <QVBoxLayout>

#include "qtmaterialgridlist.h"
#include "qtmaterialgridlistitem.h"

GridListSettingsEditor::GridListSettingsEditor(QWidget *parent)
    : QWidget(parent),
      m_gridList(new QtMaterialGridList),
      m_model(new QStandardItemModel(this)),
      m_useThemeColorsCheckBox(0),
      m_overlayTextCheckBox(0),
      m_cellWidthSpinBox(0),
      m_cellHeightSpinBox(0),
      m_spacingSpinBox(0),
      m_backgroundColorButton(0),
      m_textColorButton(0)
{
    init();
}

GridListSettingsEditor::~GridListSettingsEditor()
{
}

void GridListSettingsEditor::setupForm()
{
    m_useThemeColorsCheckBox->setChecked(m_gridList->useThemeColors());
    m_overlayTextCheckBox->setChecked(m_gridList->showOverlayText());
    m_cellWidthSpinBox->setValue(m_gridList->cellWidth());
    m_cellHeightSpinBox->setValue(m_gridList->cellHeight());
    m_spacingSpinBox->setValue(m_gridList->spacing());
}

void GridListSettingsEditor::updateWidget()
{
    m_gridList->setUseThemeColors(m_useThemeColorsCheckBox->isChecked());
    m_gridList->setShowOverlayText(m_overlayTextCheckBox->isChecked());
    m_gridList->setCellWidth(m_cellWidthSpinBox->value());
    m_gridList->setCellHeight(m_cellHeightSpinBox->value());
    m_gridList->setSpacing(m_spacingSpinBox->value());
}

void GridListSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (!dialog.exec()) {
        return;
    }

    const QColor color = dialog.selectedColor();
    const QString senderName = sender()->objectName();

    if (senderName == QLatin1String("backgroundColorButton")) {
        m_gridList->setBackgroundColor(color);
    } else if (senderName == QLatin1String("textColorButton")) {
        m_gridList->setTextColor(color);
    }

    setupForm();
}

void GridListSettingsEditor::init()
{
    QVBoxLayout *rootLayout = new QVBoxLayout;
    rootLayout->setContentsMargins(20, 20, 20, 20);
    setLayout(rootLayout);

    QWidget *controls = new QWidget;
    QFormLayout *form = new QFormLayout;
    controls->setLayout(form);

    m_useThemeColorsCheckBox = new QCheckBox;
    m_overlayTextCheckBox = new QCheckBox;

    m_cellWidthSpinBox = new QSpinBox;
    m_cellWidthSpinBox->setRange(80, 400);

    m_cellHeightSpinBox = new QSpinBox;
    m_cellHeightSpinBox->setRange(80, 400);

    m_spacingSpinBox = new QSpinBox;
    m_spacingSpinBox->setRange(0, 48);

    m_backgroundColorButton = new QPushButton(tr("Choose"));
    m_backgroundColorButton->setObjectName("backgroundColorButton");

    m_textColorButton = new QPushButton(tr("Choose"));
    m_textColorButton->setObjectName("textColorButton");

    form->addRow(tr("Use theme colors"), m_useThemeColorsCheckBox);
    form->addRow(tr("Overlay text"), m_overlayTextCheckBox);
    form->addRow(tr("Cell width"), m_cellWidthSpinBox);
    form->addRow(tr("Cell height"), m_cellHeightSpinBox);
    form->addRow(tr("Spacing"), m_spacingSpinBox);
    form->addRow(tr("Background color"), m_backgroundColorButton);
    form->addRow(tr("Text color"), m_textColorButton);

    QWidget *canvas = new QWidget;
    canvas->setStyleSheet("QWidget { background: white; }");
    QVBoxLayout *canvasLayout = new QVBoxLayout;
    canvas->setLayout(canvasLayout);
    canvasLayout->addWidget(m_gridList);

    rootLayout->addWidget(controls);
    rootLayout->addWidget(canvas, 1);

    populateModel();
    m_gridList->setModel(m_model);

    setupForm();

    connect(m_useThemeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_overlayTextCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_cellWidthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_cellHeightSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_spacingSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_backgroundColorButton, SIGNAL(clicked()), this, SLOT(selectColor()));
    connect(m_textColorButton, SIGNAL(clicked()), this, SLOT(selectColor()));
}

void GridListSettingsEditor::populateModel()
{
    static const char *titles[] = {
        "Mountains", "Architecture", "Studio", "Night city", "Workspace", "Travel"
    };
    static const char *subtitles[] = {
        "Image tile", "Two-line tile", "Overlay title", "City lights", "Desk setup", "Weekend plan"
    };

    for (int i = 0; i < 6; ++i) {
        QtMaterialGridListItem *item = new QtMaterialGridListItem(QString::fromLatin1(titles[i]));
        item->setSecondaryText(QString::fromLatin1(subtitles[i]));
        item->setOverlayTextEnabled((i % 2) == 0);

        QPixmap pixmap(240, 120);
        pixmap.fill(QColor::fromHsv((i * 45) % 360, 96, 210));
        item->setPixmap(pixmap);

        m_model->appendRow(item);
    }
}
