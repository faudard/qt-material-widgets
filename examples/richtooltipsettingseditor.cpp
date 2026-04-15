#include "richtooltipsettingseditor.h"

#include "qtmaterialrichtooltip.h"
#include "qtmaterialraisedbutton.h"

#include <QVBoxLayout>

RichTooltipSettingsEditor::RichTooltipSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    m_button = new QtMaterialRaisedButton(QStringLiteral("Hover or click for rich tooltip"), this);
    m_tooltip = new QtMaterialRichTooltip(this);

    m_tooltip->setTarget(m_button);
    m_tooltip->setTitle(QStringLiteral("Camera access"));
    m_tooltip->setSupportingText(QStringLiteral("Rich tooltips can include supporting text and lightweight actions."));
    m_tooltip->setPrimaryActionText(QStringLiteral("Allow"));
    m_tooltip->setSecondaryActionText(QStringLiteral("Later"));

    layout->addWidget(m_button, 0, Qt::AlignCenter);

    connect(m_tooltip, SIGNAL(primaryActionTriggered()), this, SLOT(updateWidget()));
    connect(m_tooltip, SIGNAL(secondaryActionTriggered()), this, SLOT(updateWidget()));
}

RichTooltipSettingsEditor::~RichTooltipSettingsEditor()
{
}

void RichTooltipSettingsEditor::updateWidget()
{
    m_tooltip->hideTooltip();
}
