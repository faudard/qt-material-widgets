#include "subheadersettingseditor.h"
#include "qtmaterialsubheader.h"

#include <QCheckBox>
#include <QComboBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSlider>
#include <QVBoxLayout>

SubheaderSettingsEditor::SubheaderSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    QVBoxLayout *panelLayout = new QVBoxLayout;
    QWidget *canvas = new QWidget;
    canvas->setMinimumWidth(360);
    canvas->setStyleSheet("background: white;");

    QVBoxLayout *canvasLayout = new QVBoxLayout(canvas);
    canvasLayout->setContentsMargins(24, 24, 24, 24);
    canvasLayout->setSpacing(0);

    m_subheader = new QtMaterialSubheader;
    m_subheader->setText("RECENT CONTACTS");
    m_subheader->setShowDivider(true);

    QLabel *body = new QLabel("Example content section below the subheader.");
    body->setMinimumHeight(80);
    body->setStyleSheet("color: rgba(0,0,0,0.54);");

    canvasLayout->addWidget(m_subheader);
    canvasLayout->addWidget(body);
    canvasLayout->addStretch();

    m_textField = new QLineEdit("RECENT CONTACTS");
    m_insetSlider = new QSlider(Qt::Horizontal);
    m_insetSlider->setRange(0, 72);
    m_insetSlider->setValue(16);

    m_denseCheckBox = new QCheckBox;
    m_dividerCheckBox = new QCheckBox;
    m_dividerCheckBox->setChecked(true);
    m_themeCheckBox = new QCheckBox;
    m_themeCheckBox->setChecked(true);

    m_alignmentCombo = new QComboBox;
    m_alignmentCombo->addItem("Left", static_cast<int>(Qt::AlignLeft | Qt::AlignVCenter));
    m_alignmentCombo->addItem("Center", static_cast<int>(Qt::AlignHCenter | Qt::AlignVCenter));
    m_alignmentCombo->addItem("Right", static_cast<int>(Qt::AlignRight | Qt::AlignVCenter));

    QFormLayout *form = new QFormLayout;
    form->addRow("Text", m_textField);
    form->addRow("Inset", m_insetSlider);
    form->addRow("Alignment", m_alignmentCombo);
    form->addRow("Dense", m_denseCheckBox);
    form->addRow("Divider", m_dividerCheckBox);
    form->addRow("Use theme colors", m_themeCheckBox);

    panelLayout->addLayout(form);
    panelLayout->addStretch();

    mainLayout->addLayout(panelLayout, 0);
    mainLayout->addWidget(canvas, 1);

    connect(m_textField, SIGNAL(textChanged(QString)), this, SLOT(updateWidget()));
    connect(m_insetSlider, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_denseCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_dividerCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_themeCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_alignmentCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));

    updateWidget();
}

SubheaderSettingsEditor::~SubheaderSettingsEditor()
{
}

void SubheaderSettingsEditor::updateWidget()
{
    m_subheader->setText(m_textField->text());
    m_subheader->setInset(m_insetSlider->value());
    m_subheader->setDense(m_denseCheckBox->isChecked());
    m_subheader->setShowDivider(m_dividerCheckBox->isChecked());
    m_subheader->setUseThemeColors(m_themeCheckBox->isChecked());
    m_subheader->setAlignment(static_cast<Qt::Alignment>(m_alignmentCombo->currentData().toInt()));
}
