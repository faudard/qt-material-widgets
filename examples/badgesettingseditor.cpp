#include "badgesettingseditor.h"
#include "qtmaterialbadge.h"
#include "qtmaterialbadgedecorator.h"
#include "qtmaterialiconbutton.h"

#include <QVBoxLayout>
#include <QLabel>

BadgeSettingsEditor::BadgeSettingsEditor(QWidget *parent)
    : QWidget(parent),
      m_badge(new QtMaterialBadge(this)),
      m_targetButton(new QtMaterialIconButton(QIcon(), this)),
      m_decorator(new QtMaterialBadgeDecorator(m_targetButton, this))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Badge examples", this));
    layout->addWidget(m_badge, 0, Qt::AlignLeft);
    layout->addWidget(m_targetButton, 0, Qt::AlignLeft);
    layout->addStretch(1);

    m_badge->setText("NEW");
    m_badge->setCountMode(false);

    m_targetButton->setText("Inbox");
    m_decorator->setCountMode(true);
    m_decorator->setCount(7);
}

void BadgeSettingsEditor::updateBadge()
{
}
