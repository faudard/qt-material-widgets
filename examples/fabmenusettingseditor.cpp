#include "fabmenusettingseditor.h"
#include "qtmaterialfabmenu.h"

#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>

FabMenuSettingsEditor::FabMenuSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *root = new QVBoxLayout(this);
    QWidget *canvas = new QWidget;
    canvas->setMinimumSize(420, 420);
    canvas->setStyleSheet("background: white;");

    m_menu = new QtMaterialFabMenu(canvas);
    m_menu->resize(canvas->size());
    m_menu->addAction(QIcon(), QStringLiteral("Create"), QStringLiteral("Create"));
    m_menu->addAction(QIcon(), QStringLiteral("Upload"), QStringLiteral("Upload"));
    m_menu->addAction(QIcon(), QStringLiteral("Share"), QStringLiteral("Share"));

    QVBoxLayout *controls = new QVBoxLayout;
    m_labelsVisible = new QCheckBox(QStringLiteral("Labels visible"));
    m_labelsVisible->setChecked(true);

    m_spacing = new QSpinBox;
    m_spacing->setRange(0, 32);
    m_spacing->setValue(12);

    m_corner = new QComboBox;
    m_corner->addItem("Bottom Right", Qt::BottomRightCorner);
    m_corner->addItem("Bottom Left", Qt::BottomLeftCorner);
    m_corner->addItem("Top Right", Qt::TopRightCorner);
    m_corner->addItem("Top Left", Qt::TopLeftCorner);

    controls->addWidget(m_labelsVisible);
    controls->addWidget(new QLabel(QStringLiteral("Action spacing")));
    controls->addWidget(m_spacing);
    controls->addWidget(new QLabel(QStringLiteral("Corner")));
    controls->addWidget(m_corner);
    controls->addStretch(1);

    QHBoxLayout *row = new QHBoxLayout;
    row->addWidget(canvas, 1);
    row->addLayout(controls);
    root->addLayout(row);

    connect(m_labelsVisible, &QCheckBox::toggled, this, &FabMenuSettingsEditor::updateWidget);
    connect(m_spacing, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_corner, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));

    updateWidget();
}

void FabMenuSettingsEditor::updateWidget()
{
    m_menu->setLabelsVisible(m_labelsVisible->isChecked());
    m_menu->setActionSpacing(m_spacing->value());
    m_menu->setCorner(static_cast<Qt::Corner>(m_corner->currentData().toInt()));
    m_menu->resize(m_menu->parentWidget()->size());
}