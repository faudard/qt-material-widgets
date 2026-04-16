#include "topappbarvariantssettingseditor.h"
#include "qtmaterialsmalltopappbar.h"
#include "qtmaterialmediumtopappbar.h"
#include "qtmateriallargetopappbar.h"
#include <QVBoxLayout>
#include <QLabel>
TopAppBarVariantsSettingsEditor::TopAppBarVariantsSettingsEditor(QWidget *parent): QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    auto *small = new QtMaterialSmallTopAppBar;
    auto *medium = new QtMaterialMediumTopAppBar;
    auto *large = new QtMaterialLargeTopAppBar;
    medium->setTitle("Medium top app bar"); medium->setSubtitle("Flexible header variant");
    large->setTitle("Large top app bar"); large->setSubtitle("Flexible header variant");
    layout->addWidget(new QLabel("Top App Bar variants"));
    layout->addWidget(small); layout->addWidget(medium); layout->addWidget(large); layout->addStretch();
}
