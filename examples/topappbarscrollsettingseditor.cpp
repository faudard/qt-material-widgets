#include "topappbarscrollsettingseditor.h"
#include "qtmaterialtopappbarscrollcontroller.h"
#include "qtmaterialmediumtopappbar.h"

#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>

TopAppBarScrollSettingsEditor::TopAppBarScrollSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    m_appBar = new QtMaterialMediumTopAppBar;
    m_appBar->setMinimumHeight(152);
    m_appBar->setMaximumHeight(152);
    layout->addWidget(m_appBar);

    m_scrollArea = new QScrollArea;
    m_scrollContents = new QWidget;
    m_scrollLayout = new QVBoxLayout(m_scrollContents);

    for (int i = 0; i < 30; ++i) {
        m_scrollLayout->addWidget(new QLabel(QString("Scroll row %1").arg(i + 1)));
    }

    m_scrollArea->setWidget(m_scrollContents);
    m_scrollArea->setWidgetResizable(true);
    layout->addWidget(m_scrollArea);

    m_controller = new QtMaterialTopAppBarScrollController(this);
    m_controller->setTarget(m_appBar);
    m_controller->setScrollArea(m_scrollArea);
    m_controller->setExpandedHeight(152);
    m_controller->setCollapsedHeight(64);
}

TopAppBarScrollSettingsEditor::~TopAppBarScrollSettingsEditor()
{
}
