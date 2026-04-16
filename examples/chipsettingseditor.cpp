#include "chipsettingseditor.h"
#include "qtmaterialchip.h"

#include <QButtonGroup>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStyle>
#include <QVBoxLayout>

ChipSettingsEditor::ChipSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    m_actionChip = new QtMaterialChip("Action chip");
    m_filterChip = new QtMaterialChip("Filter chip");
    m_choiceChip1 = new QtMaterialChip("Choice A");
    m_choiceChip2 = new QtMaterialChip("Choice B");
    m_choiceChip3 = new QtMaterialChip("Choice C");
    m_removableChip = new QtMaterialChip("Removable chip");

    m_actionChip->setLeadingIcon(style()->standardIcon(QStyle::SP_FileDialogDetailedView));
    m_actionChip->setTrailingIcon(style()->standardIcon(QStyle::SP_ArrowForward));
    m_actionChip->setShowLeadingIcon(true);

    m_filterChip->setCheckable(true);
    m_filterChip->setChecked(true);
    m_filterChip->setLeadingIcon(style()->standardIcon(QStyle::SP_DialogApplyButton));
    m_filterChip->setShowLeadingIcon(true);

    m_choiceChip1->setCheckable(true);
    m_choiceChip2->setCheckable(true);
    m_choiceChip3->setCheckable(true);
    m_choiceChip2->setChecked(true);

    m_choiceGroup = new QButtonGroup(this);
    m_choiceGroup->setExclusive(true);
    m_choiceGroup->addButton(m_choiceChip1);
    m_choiceGroup->addButton(m_choiceChip2);
    m_choiceGroup->addButton(m_choiceChip3);

    m_removableChip->setLeadingIcon(style()->standardIcon(QStyle::SP_FileIcon));
    m_removableChip->setShowLeadingIcon(true);
    m_removableChip->setClosable(true);

    m_checkableCheckBox = new QCheckBox("Checkable");
    m_checkedCheckBox = new QCheckBox("Checked");
    m_closableCheckBox = new QCheckBox("Closable");
    m_leadingIconCheckBox = new QCheckBox("Leading icon");
    m_trailingIconCheckBox = new QCheckBox("Trailing icon");
    m_themeColorsCheckBox = new QCheckBox("Use theme colors");
    m_restoreButton = new QPushButton("Restore removable chip");

    m_themeColorsCheckBox->setChecked(true);
    m_leadingIconCheckBox->setChecked(true);

    QVBoxLayout *controls = new QVBoxLayout;
    controls->addWidget(new QLabel("Preview controls"));
    controls->addWidget(m_checkableCheckBox);
    controls->addWidget(m_checkedCheckBox);
    controls->addWidget(m_closableCheckBox);
    controls->addWidget(m_leadingIconCheckBox);
    controls->addWidget(m_trailingIconCheckBox);
    controls->addWidget(m_themeColorsCheckBox);
    controls->addSpacing(12);
    controls->addWidget(m_restoreButton);
    controls->addStretch(1);

    QVBoxLayout *preview = new QVBoxLayout;
    preview->setSpacing(18);

    auto addSection = [preview](const QString &title, QLayout *row) {
        preview->addWidget(new QLabel(title));
        preview->addLayout(row);
    };

    QHBoxLayout *actionRow = new QHBoxLayout;
    actionRow->addWidget(m_actionChip);
    actionRow->addStretch(1);

    QHBoxLayout *filterRow = new QHBoxLayout;
    filterRow->addWidget(m_filterChip);
    filterRow->addStretch(1);

    QHBoxLayout *choiceRow = new QHBoxLayout;
    choiceRow->addWidget(m_choiceChip1);
    choiceRow->addWidget(m_choiceChip2);
    choiceRow->addWidget(m_choiceChip3);
    choiceRow->addStretch(1);

    QHBoxLayout *removableRow = new QHBoxLayout;
    removableRow->addWidget(m_removableChip);
    removableRow->addStretch(1);

    addSection("Action chip", actionRow);
    addSection("Filter chip", filterRow);
    addSection("Choice chips", choiceRow);
    addSection("Removable chip", removableRow);
    preview->addStretch(1);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addLayout(controls);
    layout->addLayout(preview, 1);

    connect(m_checkableCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_checkedCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_closableCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_leadingIconCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_trailingIconCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_themeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_restoreButton, SIGNAL(clicked(bool)), this, SLOT(restoreRemovableChip()));
    connect(m_removableChip, SIGNAL(closeClicked()), m_removableChip, SLOT(hide()));

    updateWidget();
}

void ChipSettingsEditor::updateWidget()
{
    const bool useTheme = m_themeColorsCheckBox->isChecked();

    QList<QtMaterialChip *> chips;
    chips << m_actionChip << m_filterChip << m_choiceChip1
          << m_choiceChip2 << m_choiceChip3 << m_removableChip;

    foreach (QtMaterialChip *chip, chips) {
        chip->setUseThemeColors(useTheme);
        if (!useTheme) {
            chip->setBackgroundColor(QColor("#eeeeee"));
            chip->setTextColor(QColor("#212121"));
            chip->setSelectedColor(QColor("#00bcd4"));
            chip->setDisabledColor(QColor("#bdbdbd"));
        }
    }

    m_actionChip->setCheckable(m_checkableCheckBox->isChecked());
    m_actionChip->setChecked(m_checkedCheckBox->isChecked());
    m_actionChip->setClosable(m_closableCheckBox->isChecked());

    m_actionChip->setLeadingIcon(style()->standardIcon(QStyle::SP_FileDialogDetailedView));
    m_actionChip->setShowLeadingIcon(m_leadingIconCheckBox->isChecked());

    m_actionChip->setTrailingIcon(style()->standardIcon(QStyle::SP_ArrowForward));
    m_actionChip->setShowTrailingIcon(m_trailingIconCheckBox->isChecked());

    if (!m_actionChip->isCheckable()) {
        m_checkedCheckBox->setChecked(false);
        m_checkedCheckBox->setEnabled(false);
    } else {
        m_checkedCheckBox->setEnabled(true);
    }

    m_actionChip->updateGeometry();
    m_actionChip->update();
}

void ChipSettingsEditor::restoreRemovableChip()
{
    m_removableChip->show();
}
