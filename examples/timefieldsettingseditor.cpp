#include "timefieldsettingseditor.h"
#include "qtmaterialtimefield.h"
#include "qtmaterialinputtimepicker.h"
#include <QVBoxLayout>

TimeFieldSettingsEditor::TimeFieldSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QtMaterialTimeField);
    layout->addWidget(new QtMaterialInputTimePicker);
    layout->addStretch();
}
