#include "tablesettingseditor.h"

#include <QCheckBox>
#include <QColorDialog>
#include <QFormLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QStandardItemModel>
#include <QVBoxLayout>

#include "qtmaterialtable.h"

TableSettingsEditor::TableSettingsEditor(QWidget *parent)
    : QWidget(parent),
      m_table(new QtMaterialTable),
      m_model(new QStandardItemModel(this)),
      m_disabledCheckBox(new QCheckBox),
      m_denseCheckBox(new QCheckBox),
      m_useThemeColorsCheckBox(new QCheckBox),
      m_headerColorButton(new QPushButton),
      m_textColorButton(new QPushButton),
      m_backgroundColorButton(new QPushButton),
      m_alternateBackgroundColorButton(new QPushButton),
      m_gridColorButton(new QPushButton),
      m_selectedRowColorButton(new QPushButton),
      m_hoverRowColorButton(new QPushButton)
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    QWidget *settingsWidget = new QWidget;
    QWidget *canvas = new QWidget;
    canvas->setStyleSheet("QWidget { background: white; }");

    layout->addWidget(settingsWidget);
    layout->addWidget(canvas);
    layout->setContentsMargins(20, 20, 20, 20);

    QFormLayout *form = new QFormLayout;
    settingsWidget->setLayout(form);

    form->addRow("Disabled", m_disabledCheckBox);
    form->addRow("Dense", m_denseCheckBox);
    form->addRow("Use theme colors", m_useThemeColorsCheckBox);
    form->addRow("Header color", m_headerColorButton);
    form->addRow("Text color", m_textColorButton);
    form->addRow("Background color", m_backgroundColorButton);
    form->addRow("Alternate background", m_alternateBackgroundColorButton);
    form->addRow("Grid color", m_gridColorButton);
    form->addRow("Selected row color", m_selectedRowColorButton);
    form->addRow("Hover row color", m_hoverRowColorButton);

    m_headerColorButton->setObjectName("headerColor");
    m_textColorButton->setObjectName("textColor");
    m_backgroundColorButton->setObjectName("backgroundColor");
    m_alternateBackgroundColorButton->setObjectName("alternateBackgroundColor");
    m_gridColorButton->setObjectName("gridColor");
    m_selectedRowColorButton->setObjectName("selectedRowColor");
    m_hoverRowColorButton->setObjectName("hoverRowColor");

    QVBoxLayout *canvasLayout = new QVBoxLayout;
    canvas->setLayout(canvasLayout);
    canvasLayout->addWidget(m_table);
    canvasLayout->setContentsMargins(0, 0, 0, 0);

    m_table->setMinimumHeight(320);
    m_table->setModel(m_model);

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#else
    m_table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
#endif

    populateModel();
    setupForm();

    connect(m_disabledCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_denseCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_useThemeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));

    connect(m_headerColorButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(m_textColorButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(m_backgroundColorButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(m_alternateBackgroundColorButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(m_gridColorButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(m_selectedRowColorButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(m_hoverRowColorButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
}

TableSettingsEditor::~TableSettingsEditor()
{
}

void TableSettingsEditor::populateModel()
{
    m_model->setColumnCount(4);
    m_model->setHorizontalHeaderLabels(QStringList()
        << "Dessert"
        << "Calories"
        << "Fat (g)"
        << "Protein (g)");

    struct RowData
    {
        const char *dessert;
        const char *calories;
        const char *fat;
        const char *protein;
    };

    const RowData rows[] = {
        { "Frozen yogurt", "159", "6.0", "4.0" },
        { "Ice cream sandwich", "237", "9.0", "4.3" },
        { "Eclair", "262", "16.0", "6.0" },
        { "Cupcake", "305", "3.7", "4.3" },
        { "Gingerbread", "356", "16.0", "3.9" }
    };

    for (unsigned int row = 0; row < sizeof(rows) / sizeof(rows[0]); ++row) {
        QList<QStandardItem *> items;

        QStandardItem *dessert = new QStandardItem(QString::fromLatin1(rows[row].dessert));
        dessert->setEditable(false);
        items << dessert;

        QStandardItem *calories = new QStandardItem(QString::fromLatin1(rows[row].calories));
        calories->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        items << calories;

        QStandardItem *fat = new QStandardItem(QString::fromLatin1(rows[row].fat));
        fat->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        items << fat;

        QStandardItem *protein = new QStandardItem(QString::fromLatin1(rows[row].protein));
        protein->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        items << protein;

        m_model->appendRow(items);
    }

    if (m_model->rowCount() > 0) {
        m_table->selectRow(0);
    }
}

void TableSettingsEditor::setupForm()
{
    m_disabledCheckBox->setChecked(!m_table->isEnabled());
    m_denseCheckBox->setChecked(m_table->isDense());
    m_useThemeColorsCheckBox->setChecked(m_table->useThemeColors());

    setButtonColor(m_headerColorButton, m_table->headerColor());
    setButtonColor(m_textColorButton, m_table->textColor());
    setButtonColor(m_backgroundColorButton, m_table->backgroundColor());
    setButtonColor(m_alternateBackgroundColorButton, m_table->alternateBackgroundColor());
    setButtonColor(m_gridColorButton, m_table->gridColor());
    setButtonColor(m_selectedRowColorButton, m_table->selectedRowColor());
    setButtonColor(m_hoverRowColorButton, m_table->hoverRowColor());
}

void TableSettingsEditor::updateWidget()
{
    m_table->setDisabled(m_disabledCheckBox->isChecked());
    m_table->setDense(m_denseCheckBox->isChecked());
    m_table->setUseThemeColors(m_useThemeColorsCheckBox->isChecked());
    setupForm();
}

void TableSettingsEditor::selectColor()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());

    if (!button) {
        return;
    }

    QColor currentColor;

    if ("headerColor" == button->objectName()) {
        currentColor = m_table->headerColor();
    } else if ("textColor" == button->objectName()) {
        currentColor = m_table->textColor();
    } else if ("backgroundColor" == button->objectName()) {
        currentColor = m_table->backgroundColor();
    } else if ("alternateBackgroundColor" == button->objectName()) {
        currentColor = m_table->alternateBackgroundColor();
    } else if ("gridColor" == button->objectName()) {
        currentColor = m_table->gridColor();
    } else if ("selectedRowColor" == button->objectName()) {
        currentColor = m_table->selectedRowColor();
    } else if ("hoverRowColor" == button->objectName()) {
        currentColor = m_table->hoverRowColor();
    }

    const QColor color = QColorDialog::getColor(currentColor, this);

    if (!color.isValid()) {
        return;
    }

    if ("headerColor" == button->objectName()) {
        m_table->setHeaderColor(color);
    } else if ("textColor" == button->objectName()) {
        m_table->setTextColor(color);
    } else if ("backgroundColor" == button->objectName()) {
        m_table->setBackgroundColor(color);
    } else if ("alternateBackgroundColor" == button->objectName()) {
        m_table->setAlternateBackgroundColor(color);
    } else if ("gridColor" == button->objectName()) {
        m_table->setGridColor(color);
    } else if ("selectedRowColor" == button->objectName()) {
        m_table->setSelectedRowColor(color);
    } else if ("hoverRowColor" == button->objectName()) {
        m_table->setHoverRowColor(color);
    }

    m_useThemeColorsCheckBox->setChecked(false);
    setupForm();
}

void TableSettingsEditor::setButtonColor(QPushButton *button, const QColor &color)
{
    if (!button) {
        return;
    }

    button->setText(color.name(QColor::HexRgb));
    button->setStyleSheet(QString(
        "QPushButton {"
        "background-color: %1;"
        "border: 1px solid rgba(0, 0, 0, 32);"
        "padding: 6px 12px;"
        "}"
    ).arg(color.name(QColor::HexRgb)));
}
