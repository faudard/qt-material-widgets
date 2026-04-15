#include "toolbarsettingseditor.h"

#include <QCheckBox>
#include <QColorDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

#include "qtmaterialiconbutton.h"
#include "qtmaterialtheme.h"
#include "qtmaterialtoolbar.h"

ToolbarSettingsEditor::ToolbarSettingsEditor(QWidget *parent)
    : QWidget(parent),
      m_toolBar(new QtMaterialToolBar),
      m_navButton(new QtMaterialIconButton(QtMaterialTheme::icon("navigation", "menu"))),
      m_searchButton(new QtMaterialIconButton(QtMaterialTheme::icon("action", "search"))),
      m_moreButton(new QtMaterialIconButton(QtMaterialTheme::icon("navigation", "more_vert"))),
      m_useThemeColorsCheckBox(new QCheckBox("Use theme colors")),
      m_denseCheckBox(new QCheckBox("Dense")),
      m_centeredTitleCheckBox(new QCheckBox("Centered title")),
      m_titleLineEdit(new QLineEdit),
      m_subtitleLineEdit(new QLineEdit),
      m_backgroundColorLineEdit(new QLineEdit)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    QWidget *controls = new QWidget;
    QWidget *canvas = new QWidget;
    canvas->setStyleSheet("QWidget { background: white; }");

    mainLayout->addWidget(controls);
    mainLayout->addWidget(canvas);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    QFormLayout *form = new QFormLayout;
    controls->setLayout(form);

    QToolButton *backgroundButton = new QToolButton;
    backgroundButton->setText("...");
    backgroundButton->setObjectName("backgroundColorToolButton");

    QWidget *backgroundWidget = new QWidget;
    QHBoxLayout *backgroundLayout = new QHBoxLayout;
    backgroundWidget->setLayout(backgroundLayout);
    backgroundLayout->setContentsMargins(0, 0, 0, 0);
    backgroundLayout->addWidget(m_backgroundColorLineEdit);
    backgroundLayout->addWidget(backgroundButton);

    form->addRow(m_useThemeColorsCheckBox);
    form->addRow(m_denseCheckBox);
    form->addRow(m_centeredTitleCheckBox);
    form->addRow("Title", m_titleLineEdit);
    form->addRow("Subtitle", m_subtitleLineEdit);
    form->addRow("Background", backgroundWidget);

    QVBoxLayout *canvasLayout = new QVBoxLayout;
    canvas->setLayout(canvasLayout);
    canvasLayout->setContentsMargins(0, 0, 0, 0);
    canvasLayout->addWidget(m_toolBar);
    canvasLayout->addStretch(1);

    m_navButton->setColor(Qt::white);
    m_searchButton->setColor(Qt::white);
    m_moreButton->setColor(Qt::white);
    m_navButton->setFixedWidth(42);
    m_searchButton->setFixedWidth(42);
    m_moreButton->setFixedWidth(42);

    m_toolBar->leadingLayout()->addWidget(m_navButton);
    m_toolBar->actionsLayout()->addWidget(m_searchButton);
    m_toolBar->actionsLayout()->addWidget(m_moreButton);
    m_toolBar->setTitle("Inbox");
    m_toolBar->setSubtitle("All messages");

    m_useThemeColorsCheckBox->setChecked(true);
    m_titleLineEdit->setText("Inbox");
    m_subtitleLineEdit->setText("All messages");

    connect(m_useThemeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_denseCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_centeredTitleCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_titleLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateWidget()));
    connect(m_subtitleLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateWidget()));
    connect(backgroundButton, SIGNAL(pressed()), this, SLOT(selectColor()));

    updateWidget();
}

ToolbarSettingsEditor::~ToolbarSettingsEditor()
{
}

void ToolbarSettingsEditor::updateWidget()
{
    m_toolBar->setUseThemeColors(m_useThemeColorsCheckBox->isChecked());
    m_toolBar->setDense(m_denseCheckBox->isChecked());
    m_toolBar->setCenteredTitle(m_centeredTitleCheckBox->isChecked());
    m_toolBar->setTitle(m_titleLineEdit->text());
    m_toolBar->setSubtitle(m_subtitleLineEdit->text());

    const QColor fg = m_toolBar->useThemeColors() ? Qt::white : m_toolBar->foregroundColor();
    m_navButton->setColor(fg);
    m_searchButton->setColor(fg);
    m_moreButton->setColor(fg);
}

void ToolbarSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec()) {
        QColor color = dialog.selectedColor();
        m_toolBar->setBackgroundColor(color);
        m_backgroundColorLineEdit->setText(color.name(QColor::HexRgb));
        updateWidget();
    }
}
