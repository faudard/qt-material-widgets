#include "bottomappbarsettingseditor.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QSpinBox>
#include <QLabel>
#include <QFrame>

#include "qtmaterialbottomappbar.h"
#include "qtmaterialiconbutton.h"

BottomAppBarSettingsEditor::BottomAppBarSettingsEditor(QWidget *parent)
    : QWidget(parent),
      m_bottomAppBar(new QtMaterialBottomAppBar),
      m_navButton(new QtMaterialIconButton(QIcon::fromTheme("go-previous"))),
      m_searchButton(new QtMaterialIconButton(QIcon::fromTheme("edit-find"))),
      m_moreButton(new QtMaterialIconButton(QIcon::fromTheme("open-menu-symbolic"))),
      m_centerFabCheckBox(new QCheckBox("Center FAB cradle")),
      m_showCradleCheckBox(new QCheckBox("Show FAB cradle")),
      m_fabDiameterSpinBox(new QSpinBox)
{
    setupForm();
    updateWidget();
}

void BottomAppBarSettingsEditor::setupForm()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(24, 24, 24, 24);
    layout->setSpacing(16);

    QLabel *title = new QLabel("Bottom App Bar");
    QFont font = title->font();
    font.setPointSize(font.pointSize() + 4);
    font.setBold(true);
    title->setFont(font);

    QFrame *canvas = new QFrame;
    canvas->setFrameShape(QFrame::StyledPanel);
    canvas->setMinimumHeight(180);
    QVBoxLayout *canvasLayout = new QVBoxLayout(canvas);
    canvasLayout->addStretch();
    canvasLayout->addWidget(m_bottomAppBar);

    m_bottomAppBar->bottomAppBarLayout()->addWidget(m_navButton);
    m_bottomAppBar->bottomAppBarLayout()->addStretch();
    m_bottomAppBar->bottomAppBarLayout()->addWidget(m_searchButton);
    m_bottomAppBar->bottomAppBarLayout()->addWidget(m_moreButton);

    m_centerFabCheckBox->setChecked(true);
    m_showCradleCheckBox->setChecked(true);
    m_fabDiameterSpinBox->setRange(40, 96);
    m_fabDiameterSpinBox->setValue(56);

    connect(m_centerFabCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_showCradleCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_fabDiameterSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));

    QHBoxLayout *controls = new QHBoxLayout;
    controls->addWidget(m_centerFabCheckBox);
    controls->addWidget(m_showCradleCheckBox);
    controls->addWidget(new QLabel("FAB diameter"));
    controls->addWidget(m_fabDiameterSpinBox);
    controls->addStretch();

    layout->addWidget(title);
    layout->addWidget(canvas);
    layout->addLayout(controls);
}

void BottomAppBarSettingsEditor::updateWidget()
{
    m_bottomAppBar->setCenterFab(m_centerFabCheckBox->isChecked());
    m_bottomAppBar->setShowFabCradle(m_showCradleCheckBox->isChecked());
    m_bottomAppBar->setFabDiameter(m_fabDiameterSpinBox->value());
}
