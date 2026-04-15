#include "snackbarlayoutsettingseditor.h"

#include <QCheckBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>

#include <qtmaterialflatbutton.h>
#include <layouts/qtmaterialsnackbarlayout.h>

SnackbarLayoutSettingsEditor::SnackbarLayoutSettingsEditor(QWidget *parent)
    : QWidget(parent),
      m_dense(new QCheckBox("Dense mode")),
      m_showAction(new QCheckBox("Show action")),
      m_multiLine(new QCheckBox("Use multi-line message")),
      m_widthSlider(new QSlider(Qt::Horizontal)),
      m_preview(new QWidget),
      m_messageLabel(new QLabel),
      m_actionButton(new QtMaterialFlatButton("UNDO")),
      m_layout(new QtMaterialSnackbarLayout)
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    QWidget *controls = new QWidget;
    QWidget *canvas = new QWidget;
    canvas->setStyleSheet("QWidget { background: white; }");

    layout->addWidget(controls);
    layout->addWidget(canvas);
    layout->setContentsMargins(20, 20, 20, 20);

    QFormLayout *form = new QFormLayout;
    controls->setLayout(form);

    m_widthSlider->setRange(240, 640);

    form->addRow(QString(), m_dense);
    form->addRow(QString(), m_showAction);
    form->addRow(QString(), m_multiLine);
    form->addRow("Preview width", m_widthSlider);

    QVBoxLayout *canvasLayout = new QVBoxLayout;
    canvas->setLayout(canvasLayout);
    canvasLayout->addStretch();
    canvasLayout->addWidget(m_preview, 0, Qt::AlignHCenter | Qt::AlignBottom);
    canvasLayout->addStretch();

    m_preview->setObjectName("snackbarPreview");
    m_preview->setStyleSheet("#snackbarPreview { background: #323232; border-radius: 4px; }");
    m_preview->setLayout(m_layout);

    m_messageLabel->setWordWrap(true);
    m_messageLabel->setStyleSheet("QLabel { color: white; }");
    m_actionButton->setUseThemeColors(false);
    m_actionButton->setForegroundColor(QColor("#FFCA28"));
    m_actionButton->setOverlayStyle(Material::TintedOverlay);
    m_actionButton->setHaloVisible(false);
    m_actionButton->setBackgroundMode(Qt::TransparentMode);

    m_layout->addWidget(m_messageLabel);
    m_layout->addWidget(m_actionButton);

    connect(m_dense, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_showAction, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_multiLine, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_widthSlider, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));

    setupForm();
}

SnackbarLayoutSettingsEditor::~SnackbarLayoutSettingsEditor()
{
}

void SnackbarLayoutSettingsEditor::setupForm()
{
    m_showAction->setChecked(true);
    m_widthSlider->setValue(420);
    updateWidget();
}

void SnackbarLayoutSettingsEditor::updateWidget()
{
    m_layout->setDense(m_dense->isChecked());
    m_preview->setFixedWidth(m_widthSlider->value());
    m_preview->setMinimumHeight(m_layout->heightForWidth(m_preview->width()));

    if (m_multiLine->isChecked()) {
        m_messageLabel->setText(QStringLiteral("Your draft has been saved locally. You can continue editing or sync your changes later."));
    } else {
        m_messageLabel->setText(QStringLiteral("Archived conversation"));
    }

    m_actionButton->setVisible(m_showAction->isChecked());
    m_layout->invalidate();
    m_preview->setMinimumHeight(m_layout->heightForWidth(m_preview->width()));
    m_preview->updateGeometry();
    m_preview->update();
}
