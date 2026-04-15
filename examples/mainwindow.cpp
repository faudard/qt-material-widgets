#include "mainwindow.h"

#include <QHBoxLayout>
#include <QListWidget>
#include <QStackedLayout>
#include <QWidget>

#include "appbarsettingseditor.h"
#include "autocompletesettingseditor.h"
#include "avatarsettingseditor.h"
#include "badgesettingseditor.h"
#include "carouselsettingseditor.h"
#include "checkboxsettingseditor.h"
#include "circularprogresssettingseditor.h"
#include "dialogsettingseditor.h"
#include "dividersettingseditor.h"
#include "drawersettingseditor.h"
#include "fabsettingseditor.h"
#include "flatbuttonsettingseditor.h"
#include "gridlistsettingseditor.h"
#include "iconbuttonsettingseditor.h"
#include "listitemsettingseditor.h"
#include "listsettingseditor.h"
#include "loadingprogresssettingseditor.h"
#include "menusettingseditor.h"
#include "papersettingseditor.h"
#include "progresssettingseditor.h"
#include "radiobuttonsettingseditor.h"
#include "raisedbuttonsettingseditor.h"
#include "scrollbarsettingseditor.h"
#include "slidersettingseditor.h"
#include "searchfieldsettingseditor.h"
#include "selectfieldsettingseditor.h"
#include "snackbarlayoutsettingseditor.h"
#include "snackbarsettingseditor.h"
#include "steppersettingseditor.h"
#include "tablesettingseditor.h"
#include "tabssettingseditor.h"
#include "textfieldsettingseditor.h"
#include "togglesettingseditor.h"
#include "toolbarsettingseditor.h"
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
    CarouselSettingsEditor *carousel = new CarouselSettingsEditor;
    CheckBoxSettingsEditor *checkbox = new CheckBoxSettingsEditor;
    FloatingActionButtonSettingsEditor *fab = new FloatingActionButtonSettingsEditor;
    RaisedButtonSettingsEditor *raisedButton = new RaisedButtonSettingsEditor;
    FlatButtonSettingsEditor *flatButton = new FlatButtonSettingsEditor;
    GridListSettingsEditor *gridList = new GridListSettingsEditor;
    IconButtonSettingsEditor *iconButton = new IconButtonSettingsEditor;
    ListSettingsEditor *materialList = new ListSettingsEditor;
    ListItemSettingsEditor *listItem = new ListItemSettingsEditor;
    LoadingProgressSettingsEditor *loadingProgress = new LoadingProgressSettingsEditor;
    ProgressSettingsEditor *progress = new ProgressSettingsEditor;
    CircularProgressSettingsEditor *circularProgress = new CircularProgressSettingsEditor;
    SliderSettingsEditor *slider = new SliderSettingsEditor;
    RadioButtonSettingsEditor *radioButton = new RadioButtonSettingsEditor;
    ToggleSettingsEditor *toggle = new ToggleSettingsEditor;
    TextFieldSettingsEditor *textField = new TextFieldSettingsEditor;
    TabsSettingsEditor *tabs = new TabsSettingsEditor;
    SearchFieldSettingsEditor *searchField = new SearchFieldSettingsEditor;
    SelectFieldSettingsEditor *selectField = new SelectFieldSettingsEditor;
    SnackbarSettingsEditor *snackbar = new SnackbarSettingsEditor;
    SnackbarLayoutSettingsEditor *snackbarLayout = new SnackbarLayoutSettingsEditor;
    StepperSettingsEditor *stepper = new StepperSettingsEditor;
    DialogSettingsEditor *dialog = new DialogSettingsEditor;
    DividerSettingsEditor *divider = new DividerSettingsEditor;
    DrawerSettingsEditor *drawer = new DrawerSettingsEditor;
    ScrollBarSettingsEditor *scrollBar = new ScrollBarSettingsEditor;
    AppBarSettingsEditor *appBar = new AppBarSettingsEditor;
    AutoCompleteSettingsEditor *autocomplete = new AutoCompleteSettingsEditor;
    PaperSettingsEditor *paper = new PaperSettingsEditor;
    MenuSettingsEditor *menu = new MenuSettingsEditor;
    TableSettingsEditor *table = new TableSettingsEditor;
    ToolbarSettingsEditor *toolbar = new ToolbarSettingsEditor;
    TreeSettingsEditor *tree = new TreeSettingsEditor;

    stack->addWidget(appBar);
    stack->addWidget(autocomplete);
    stack->addWidget(avatar);
    stack->addWidget(badge);
    stack->addWidget(carousel);
    stack->addWidget(checkbox);
    stack->addWidget(circularProgress);
    stack->addWidget(dialog);
    stack->addWidget(divider);
    stack->addWidget(drawer);
    stack->addWidget(fab);
    stack->addWidget(flatButton);
    stack->addWidget(gridList);
    stack->addWidget(iconButton);
    stack->addWidget(materialList);
    stack->addWidget(listItem);
    stack->addWidget(loadingProgress);
    stack->addWidget(menu);
    stack->addWidget(paper);
    stack->addWidget(progress);
    stack->addWidget(radioButton);
    stack->addWidget(raisedButton);
    stack->addWidget(scrollBar);
    stack->addWidget(slider);
    stack->addWidget(snackbar);
    stack->addWidget(snackbarLayout);
    stack->addWidget(searchField);
    stack->addWidget(selectField);
    stack->addWidget(stepper);
    stack->addWidget(table);
    stack->addWidget(tabs);
    stack->addWidget(textField);
    stack->addWidget(toggle);
    stack->addWidget(toolbar);
    stack->addWidget(tree);

    list->addItem("App Bar");
    list->addItem("Auto Complete");
    list->addItem("Avatar");
    list->addItem("Badge");
    list->addItem("Carousel");
    list->addItem("Checkbox");
    list->addItem("Circular Progress");
    list->addItem("Dialog");
    list->addItem("Divider");
    list->addItem("Drawer");
    list->addItem("Floating Action Button");
    list->addItem("Flat Button");
    list->addItem("Grid List");
    list->addItem("Icon Button");
    list->addItem("List");
    list->addItem("List Item");
    list->addItem(QStringLiteral("Loading + Progress"));
    list->addItem("Menu");
    list->addItem("Paper");
    list->addItem("Progress");
    list->addItem("Radio Button");
    list->addItem("Raised Button");
    list->addItem("ScrollBar");
    list->addItem("Slider");
    list->addItem("Snackbar");
    list->addItem("Snackbar Layout");
    list->addItem("Search Field");
    list->addItem("Select Field");
    list->addItem("Stepper");
    list->addItem("Table");
    list->addItem("Tabs");
    list->addItem("Text Field");
    list->addItem("Toggle");
    list->addItem("Toolbar");
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
