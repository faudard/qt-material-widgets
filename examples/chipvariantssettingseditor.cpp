#include "chipvariantssettingseditor.h"
#include "qtmaterialassistchip.h"
#include "qtmaterialfilterchip.h"
#include "qtmaterialinputchip.h"
#include "qtmaterialsuggestionchip.h"
#include <QVBoxLayout>
#include <QLabel>

ChipVariantsSettingsEditor::ChipVariantsSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(24, 24, 24, 24);
    layout->setSpacing(16);

    auto *title = new QLabel(QStringLiteral("Chip variants"), this);
    layout->addWidget(title);

    auto *assist = new QtMaterialAssistChip(this);
    assist->setLabel(QStringLiteral("Assist"));
    layout->addWidget(assist);

    auto *filter = new QtMaterialFilterChip(this);
    filter->setLabel(QStringLiteral("Filter"));
    filter->setChecked(true);
    layout->addWidget(filter);

    auto *input = new QtMaterialInputChip(this);
    input->setLabel(QStringLiteral("Input"));
    layout->addWidget(input);

    auto *suggestion = new QtMaterialSuggestionChip(this);
    suggestion->setLabel(QStringLiteral("Suggestion"));
    layout->addWidget(suggestion);

    layout->addStretch(1);
}
