#include "mainwindow.h"

#include <QHBoxLayout>
#include <QListWidget>
#include <QStackedLayout>
#include <QWidget>

#include "appbarsettingseditor.h"
#include "autocompletesettingseditor.h"
#include "avatarsettingseditor.h"
#include "badgesettingseditor.h"
#include "checkboxsettingseditor.h"
#include "circularprogresssettingseditor.h"
#include "dialogsettingseditor.h"
#include "drawersettingseditor.h"
#include "fabsettingseditor.h"
#include "flatbuttonsettingseditor.h"
#include "iconbuttonsettingseditor.h"
#include "listitemsettingseditor.h"
#include "listsettingseditor.h"
#include "menusettingseditor.h"
#include "progresssettingseditor.h"
#include "radiobuttonsettingseditor.h"
#include "raisedbuttonsettingseditor.h"
#include "scrollbarsettingseditor.h"
#include "slidersettingseditor.h"
#include "snackbarsettingseditor.h"
#include "tablesettingseditor.h"
#include "tabssettingseditor.h"
#include "textfieldsettingseditor.h"
#include "togglesettingseditor.h"
#include "treesettingseditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *widget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;
    widget->setLayout(layout);

    QStackedLayout *stack = new QStackedLayout;
    QListWidget *list = new QListWidget;

    layout->addWidget(list);
    layout->addLayout(stack);
    layout->setStretch(1, 2);
    setCentralWidget(widget);

    AvatarSettingsEditor *avatar = new AvatarSettingsEditor;
    BadgeSettingsEditor *badge = new BadgeSettingsEditor;
    CheckBoxSettingsEditor *checkbox = new CheckBoxSettingsEditor;
    FloatingActionButtonSettingsEditor *fab = new FloatingActionButtonSettingsEditor;
    RaisedButtonSettingsEditor *raisedButton = new RaisedButtonSettingsEditor;
    FlatButtonSettingsEditor *flatButton = new FlatButtonSettingsEditor;
    IconButtonSettingsEditor *iconButton = new IconButtonSettingsEditor;
    ListSettingsEditor *materialList = new ListSettingsEditor;
    ListItemSettingsEditor *listItem = new ListItemSettingsEditor;
    ProgressSettingsEditor *progress = new ProgressSettingsEditor;
    CircularProgressSettingsEditor *circularProgress = new CircularProgressSettingsEditor;
    SliderSettingsEditor *slider = new SliderSettingsEditor;
    RadioButtonSettingsEditor *radioButton = new RadioButtonSettingsEditor;
    ToggleSettingsEditor *toggle = new ToggleSettingsEditor;
    TextFieldSettingsEditor *textField = new TextFieldSettingsEditor;
    TabsSettingsEditor *tabs = new TabsSettingsEditor;
    SnackbarSettingsEditor *snackbar = new SnackbarSettingsEditor;
    DialogSettingsEditor *dialog = new DialogSettingsEditor;
    DrawerSettingsEditor *drawer = new DrawerSettingsEditor;
    ScrollBarSettingsEditor *scrollBar = new ScrollBarSettingsEditor;
    AppBarSettingsEditor *appBar = new AppBarSettingsEditor;
    AutoCompleteSettingsEditor *autocomplete = new AutoCompleteSettingsEditor;
    MenuSettingsEditor *menu = new MenuSettingsEditor;
    TableSettingsEditor *table = new TableSettingsEditor;
    TreeSettingsEditor *tree = new TreeSettingsEditor;

    stack->addWidget(appBar);
    stack->addWidget(autocomplete);
    stack->addWidget(avatar);
    stack->addWidget(badge);
    stack->addWidget(checkbox);
    stack->addWidget(circularProgress);
    stack->addWidget(dialog);
    stack->addWidget(drawer);
    stack->addWidget(fab);
    stack->addWidget(flatButton);
    stack->addWidget(iconButton);
    stack->addWidget(materialList);
    stack->addWidget(listItem);
    stack->addWidget(menu);
    stack->addWidget(progress);
    stack->addWidget(radioButton);
    stack->addWidget(raisedButton);
    stack->addWidget(scrollBar);
    stack->addWidget(slider);
    stack->addWidget(snackbar);
    stack->addWidget(table);
    stack->addWidget(tabs);
    stack->addWidget(textField);
    stack->addWidget(toggle);
    stack->addWidget(tree);

    list->addItem("App Bar");
    list->addItem("Auto Complete");
    list->addItem("Avatar");
    list->addItem("Badge");
    list->addItem("Checkbox");
    list->addItem("Circular Progress");
    list->addItem("Dialog");
    list->addItem("Drawer");
    list->addItem("Floating Action Button");
    list->addItem("Flat Button");
    list->addItem("Icon Button");
    list->addItem("List");
    list->addItem("List Item");
    list->addItem("Menu");
    list->addItem("Progress");
    list->addItem("Radio Button");
    list->addItem("Raised Button");
    list->addItem("ScrollBar");
    list->addItem("Slider");
    list->addItem("Snackbar");
    list->addItem("Table");
    list->addItem("Tabs");
    list->addItem("Text Field");
    list->addItem("Toggle");
    list->addItem("Tree");

    list->setCurrentRow(0);

    QObject::connect(list, &QListWidget::currentItemChanged,
                     [=](QListWidgetItem *current, QListWidgetItem *previous) {
        Q_UNUSED(current)
        Q_UNUSED(previous)
        stack->setCurrentIndex(list->currentRow());
    });
}

MainWindow::~MainWindow()
{
}
