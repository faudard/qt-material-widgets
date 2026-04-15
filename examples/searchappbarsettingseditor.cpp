#include "searchappbarsettingseditor.h"
#include "qtmaterialsearchappbar.h"

#include <QVBoxLayout>
#include <QLabel>

SearchAppBarSettingsEditor::SearchAppBarSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QtMaterialSearchAppBar *bar = new QtMaterialSearchAppBar(this);
    layout->addWidget(bar);
    layout->addWidget(new QLabel("Search App Bar example placeholder", this));
    layout->addStretch(1);
}
