#include "bannersettingseditor.h"
#include "qtmaterialbanner.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QFrame>

BannerSettingsEditor::BannerSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(16);

    m_banner = new QtMaterialBanner;
    m_banner->setText(QStringLiteral("Your trial expires in 3 days"));
    m_banner->setSupportingText(QStringLiteral("Upgrade now to keep access to syncing and backup features."));
    m_banner->setPrimaryActionText(QStringLiteral("UPGRADE"));
    m_banner->setSecondaryActionText(QStringLiteral("LATER"));
    m_banner->setLeadingIcon(QIcon(":/icons/icons/navigation/svg/production/ic_menu_24px.svg"));
    m_banner->setShowLeadingIcon(true);

    QFrame *canvas = new QFrame;
    canvas->setFrameShape(QFrame::StyledPanel);
    canvas->setStyleSheet("background:white;");
    QVBoxLayout *canvasLayout = new QVBoxLayout(canvas);
    canvasLayout->addWidget(m_banner);
    canvasLayout->addStretch();

    QWidget *controls = new QWidget;
    QGridLayout *grid = new QGridLayout(controls);

    m_titleEdit = new QLineEdit(QStringLiteral("Your trial expires in 3 days"));
    m_supportingEdit = new QLineEdit(QStringLiteral("Upgrade now to keep access to syncing and backup features."));
    m_iconCheck = new QCheckBox(QStringLiteral("Show leading icon"));
    m_dismissibleCheck = new QCheckBox(QStringLiteral("Dismissible"));
    m_supportingCheck = new QCheckBox(QStringLiteral("Show supporting text"));

    m_iconCheck->setChecked(true);
    m_dismissibleCheck->setChecked(true);
    m_supportingCheck->setChecked(true);

    grid->addWidget(new QLabel(QStringLiteral("Title")), 0, 0);
    grid->addWidget(m_titleEdit, 0, 1);
    grid->addWidget(new QLabel(QStringLiteral("Supporting text")), 1, 0);
    grid->addWidget(m_supportingEdit, 1, 1);
    grid->addWidget(m_iconCheck, 2, 0);
    grid->addWidget(m_dismissibleCheck, 2, 1);
    grid->addWidget(m_supportingCheck, 3, 0);

    layout->addWidget(canvas, 1);
    layout->addWidget(controls);

    connect(m_titleEdit, SIGNAL(textChanged(QString)), this, SLOT(updateBanner()));
    connect(m_supportingEdit, SIGNAL(textChanged(QString)), this, SLOT(updateBanner()));
    connect(m_iconCheck, SIGNAL(toggled(bool)), this, SLOT(updateBanner()));
    connect(m_dismissibleCheck, SIGNAL(toggled(bool)), this, SLOT(updateBanner()));
    connect(m_supportingCheck, SIGNAL(toggled(bool)), this, SLOT(updateBanner()));
}

void BannerSettingsEditor::updateBanner()
{
    m_banner->setText(m_titleEdit->text());
    m_banner->setShowLeadingIcon(m_iconCheck->isChecked());
    m_banner->setDismissible(m_dismissibleCheck->isChecked());

    if (m_supportingCheck->isChecked()) {
        m_banner->setSupportingText(m_supportingEdit->text());
    } else {
        m_banner->setSupportingText(QString());
    }
}
