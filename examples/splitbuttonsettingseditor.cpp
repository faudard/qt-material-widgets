#include "splitbuttonsettingseditor.h"
#include "../components/qtmaterialsplitbutton.h"

#include <QAction>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QVBoxLayout>

SplitButtonSettingsEditor::SplitButtonSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    m_button = new QtMaterialSplitButton(this);
    m_button->setText("Create");
    QMenu *menu = new QMenu(m_button);
    menu->addAction("Create file");
    menu->addAction("Create folder");
    menu->addAction("Create project");
    m_button->setMenu(menu);

    m_useThemeColors = new QCheckBox("Use theme colors", this);
    m_useThemeColors->setChecked(true);
    m_dense = new QCheckBox("Dense", this);
    m_textField = new QLineEdit("Create", this);

    layout->addWidget(m_button);
    layout->addWidget(new QLabel("Text", this));
    layout->addWidget(m_textField);
    layout->addWidget(m_useThemeColors);
    layout->addWidget(m_dense);
    layout->addStretch(1);

    connect(m_useThemeColors, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_dense, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_textField, SIGNAL(textChanged(QString)), this, SLOT(updateWidget()));

    updateWidget();
}

void SplitButtonSettingsEditor::updateWidget()
{
    m_button->setUseThemeColors(m_useThemeColors->isChecked());
    m_button->setDense(m_dense->isChecked());
    m_button->setText(m_textField->text());
}
