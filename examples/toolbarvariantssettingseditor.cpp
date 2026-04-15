#include "toolbarvariantssettingseditor.h"
#include "qtmaterialdockedtoolbar.h"
#include "qtmaterialfloatingtoolbar.h"
#include "qtmaterialiconbutton.h"

#include <QVBoxLayout>
#include <QBoxLayout>

ToolbarVariantsSettingsEditor::ToolbarVariantsSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->setSpacing(24);

  QtMaterialDockedToolBar *docked = new QtMaterialDockedToolBar;
  QBoxLayout *dockedLayout = qobject_cast<QBoxLayout *>(docked->layout());
  if (dockedLayout) {
    dockedLayout->addWidget(new QtMaterialIconButton(QIcon(), docked));
    dockedLayout->addStretch(1);
    dockedLayout->addWidget(new QtMaterialIconButton(QIcon(), docked));
  }

  QtMaterialFloatingToolBar *floating = new QtMaterialFloatingToolBar;
  QBoxLayout *floatingLayout = qobject_cast<QBoxLayout *>(floating->layout());
  if (floatingLayout) {
    floatingLayout->addWidget(new QtMaterialIconButton(QIcon(), floating));
    floatingLayout->addWidget(new QtMaterialIconButton(QIcon(), floating));
    floatingLayout->addWidget(new QtMaterialIconButton(QIcon(), floating));
  }

  layout->addWidget(docked);
  layout->addWidget(floating, 0, Qt::AlignHCenter);
  layout->addStretch(1);
}