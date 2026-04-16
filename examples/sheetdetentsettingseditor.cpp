#include "sheetdetentsettingseditor.h"
#include "qtmaterialsheetdetentcontroller.h"

#include <QComboBox>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>

SheetDetentSettingsEditor::SheetDetentSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *root = new QHBoxLayout(this);
    QVBoxLayout *controls = new QVBoxLayout;
    QVBoxLayout *preview = new QVBoxLayout;

    m_orientationCombo = new QComboBox;
    m_orientationCombo->addItem("Bottom sheet", QtMaterialSheetDetentController::BottomSheet);
    m_orientationCombo->addItem("Side sheet", QtMaterialSheetDetentController::SideSheet);

    m_collapsedSpin = new QSpinBox;
    m_collapsedSpin->setRange(0, 1200);
    m_collapsedSpin->setValue(72);
    m_halfSpin = new QSpinBox;
    m_halfSpin->setRange(0, 1200);
    m_halfSpin->setValue(320);
    m_expandedSpin = new QSpinBox;
    m_expandedSpin->setRange(0, 1200);
    m_expandedSpin->setValue(560);

    m_collapsedButton = new QPushButton("Collapsed");
    m_halfButton = new QPushButton("Half");
    m_expandedButton = new QPushButton("Expanded");

    controls->addWidget(new QLabel("Orientation"));
    controls->addWidget(m_orientationCombo);
    controls->addWidget(new QLabel("Collapsed extent"));
    controls->addWidget(m_collapsedSpin);
    controls->addWidget(new QLabel("Half extent"));
    controls->addWidget(m_halfSpin);
    controls->addWidget(new QLabel("Expanded extent"));
    controls->addWidget(m_expandedSpin);
    controls->addWidget(m_collapsedButton);
    controls->addWidget(m_halfButton);
    controls->addWidget(m_expandedButton);
    controls->addStretch();

    QWidget *canvas = new QWidget;
    canvas->setMinimumSize(480, 360);
    canvas->setStyleSheet("background:white;");
    m_sheet = new QFrame(canvas);
    m_sheet->setStyleSheet("background:#eeeeee;border:1px solid #cccccc;");
    m_sheet->setGeometry(40, 220, 400, 72);

    preview->addWidget(canvas);

    root->addLayout(controls);
    root->addLayout(preview, 1);

    m_controller = new QtMaterialSheetDetentController(this);
    m_controller->setTarget(m_sheet);

    connect(m_orientationCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(updateController()));
    connect(m_collapsedSpin, SIGNAL(valueChanged(int)), this, SLOT(updateController()));
    connect(m_halfSpin, SIGNAL(valueChanged(int)), this, SLOT(updateController()));
    connect(m_expandedSpin, SIGNAL(valueChanged(int)), this, SLOT(updateController()));
    connect(m_collapsedButton, SIGNAL(clicked()), this, SLOT(setCollapsedDetent()));
    connect(m_halfButton, SIGNAL(clicked()), this, SLOT(setHalfDetent()));
    connect(m_expandedButton, SIGNAL(clicked()), this, SLOT(setExpandedDetent()));

    updateController();
}

void SheetDetentSettingsEditor::updateController()
{
    m_controller->setOrientation(static_cast<QtMaterialSheetDetentController::Orientation>(
        m_orientationCombo->currentData().toInt()));
    m_controller->setCollapsedExtent(m_collapsedSpin->value());
    m_controller->setHalfExpandedExtent(m_halfSpin->value());
    m_controller->setExpandedExtent(m_expandedSpin->value());
    m_controller->applyCurrentDetent();
}

void SheetDetentSettingsEditor::setCollapsedDetent()
{
    m_controller->setCurrentDetent(QtMaterialSheetDetentController::CollapsedDetent);
}

void SheetDetentSettingsEditor::setHalfDetent()
{
    m_controller->setCurrentDetent(QtMaterialSheetDetentController::HalfExpandedDetent);
}

void SheetDetentSettingsEditor::setExpandedDetent()
{
    m_controller->setCurrentDetent(QtMaterialSheetDetentController::ExpandedDetent);
}
