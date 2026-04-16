#include "appbarbehaviorsettingseditor.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include <QScrollArea>
#include <QListWidget>
#include <QListWidgetItem>

#include "qtmaterialappbar.h"
#include "qtmaterialtopappbarscrollcontroller.h"
#include "qtmaterialappbarbehavior.h"

AppBarBehaviorSettingsEditor::AppBarBehaviorSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    m_appBar = new QtMaterialAppBar(this);
    m_appBar->appBarLayout()->addWidget(new QLabel("Top App Bar Behavior", m_appBar));

    m_scrollArea = new QScrollArea(this);
    QWidget *content = new QWidget;
    QVBoxLayout *contentLayout = new QVBoxLayout(content);
    for (int i = 0; i < 40; ++i) {
        contentLayout->addWidget(new QLabel(QString("Scrollable content row %1").arg(i + 1), content));
    }
    contentLayout->addStretch(1);
    m_scrollArea->setWidget(content);
    m_scrollArea->setWidgetResizable(true);

    QWidget *controls = new QWidget(this);
    QHBoxLayout *controlsLayout = new QHBoxLayout(controls);
    m_modeCombo = new QComboBox(controls);
    m_modeCombo->addItem("Pinned");
    m_modeCombo->addItem("Enter always");
    m_snapCheckBox = new QCheckBox("Snap", controls);
    controlsLayout->addWidget(new QLabel("Behavior:", controls));
    controlsLayout->addWidget(m_modeCombo);
    controlsLayout->addWidget(m_snapCheckBox);
    controlsLayout->addStretch(1);

    m_controller = new QtMaterialTopAppBarScrollController(this);
    m_behavior = new QtMaterialAppBarBehavior(this);
    m_behavior->setController(m_controller);

    connect(m_modeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(updateBehavior()));
    connect(m_snapCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateBehavior()));

    layout->addWidget(m_appBar);
    layout->addWidget(controls);
    layout->addWidget(m_scrollArea, 1);

    updateBehavior();
}

AppBarBehaviorSettingsEditor::~AppBarBehaviorSettingsEditor()
{
}

void AppBarBehaviorSettingsEditor::updateBehavior()
{
    m_behavior->setBehaviorMode(
        m_modeCombo->currentIndex() == 0
            ? QtMaterialAppBarBehavior::PinnedBehavior
            : QtMaterialAppBarBehavior::EnterAlwaysBehavior);
    m_behavior->setSnap(m_snapCheckBox->isChecked());
}
