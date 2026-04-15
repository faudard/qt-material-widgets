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
#include "datetimepickersettingseditor.h"
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
#include "navigationsettingseditor.h"
#include "menusettingseditor.h"
#include "papersettingseditor.h"
#include "progresssettingseditor.h"
#include "radiobuttonsettingseditor.h"
#include "raisedbuttonsettingseditor.h"
#include "scrollbarsettingseditor.h"
#include "searchfieldsettingseditor.h"
#include "selectfieldsettingseditor.h"
#include "slidersettingseditor.h"
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

    AppBarSettingsEditor *appBar = new AppBarSettingsEditor;
    AutoCompleteSettingsEditor *autocomplete = new AutoCompleteSettingsEditor;
    AvatarSettingsEditor *avatar = new AvatarSettingsEditor;
    BadgeSettingsEditor *badge = new BadgeSettingsEditor;
    CarouselSettingsEditor *carousel = new CarouselSettingsEditor;
    CheckBoxSettingsEditor *checkbox = new CheckBoxSettingsEditor;
    CircularProgressSettingsEditor *circularProgress = new CircularProgressSettingsEditor;
    DateTimePickerSettingsEditor *dateTimePicker = new DateTimePickerSettingsEditor;
    DialogSettingsEditor *dialog = new DialogSettingsEditor;
    DividerSettingsEditor *divider = new DividerSettingsEditor;
    DrawerSettingsEditor *drawer = new DrawerSettingsEditor;
    FlatButtonSettingsEditor *flatButton = new FlatButtonSettingsEditor;
    FloatingActionButtonSettingsEditor *fab = new FloatingActionButtonSettingsEditor;
    GridListSettingsEditor *gridList = new GridListSettingsEditor;
    IconButtonSettingsEditor *iconButton = new IconButtonSettingsEditor;
    ListSettingsEditor *materialList = new ListSettingsEditor;
    ListItemSettingsEditor *listItem = new ListItemSettingsEditor;
    LoadingProgressSettingsEditor *loadingProgress = new LoadingProgressSettingsEditor;
    NavigationSettingsEditor *navigation = new NavigationSettingsEditor;
    MenuSettingsEditor *menu = new MenuSettingsEditor;
    PaperSettingsEditor *paper = new PaperSettingsEditor;
    ProgressSettingsEditor *progress = new ProgressSettingsEditor;
    RadioButtonSettingsEditor *radioButton = new RadioButtonSettingsEditor;
    RaisedButtonSettingsEditor *raisedButton = new RaisedButtonSettingsEditor;
    ScrollBarSettingsEditor *scrollBar = new ScrollBarSettingsEditor;
    SearchFieldSettingsEditor *searchField = new SearchFieldSettingsEditor;
    SelectFieldSettingsEditor *selectField = new SelectFieldSettingsEditor;
    SliderSettingsEditor *slider = new SliderSettingsEditor;
    SnackbarSettingsEditor *snackbar = new SnackbarSettingsEditor;
    SnackbarLayoutSettingsEditor *snackbarLayout = new SnackbarLayoutSettingsEditor;
    StepperSettingsEditor *stepper = new StepperSettingsEditor;
    TableSettingsEditor *table = new TableSettingsEditor;
    TabsSettingsEditor *tabs = new TabsSettingsEditor;
    TextFieldSettingsEditor *textField = new TextFieldSettingsEditor;
    ToggleSettingsEditor *toggle = new ToggleSettingsEditor;
    ToolbarSettingsEditor *toolbar = new ToolbarSettingsEditor;
    TreeSettingsEditor *tree = new TreeSettingsEditor;

    stack->addWidget(appBar);
    stack->addWidget(autocomplete);
    stack->addWidget(avatar);
    stack->addWidget(badge);
    stack->addWidget(carousel);
    stack->addWidget(checkbox);
    stack->addWidget(circularProgress);
    stack->addWidget(dateTimePicker);
    stack->addWidget(dialog);
    stack->addWidget(divider);
    stack->addWidget(drawer);
    stack->addWidget(flatButton);
    stack->addWidget(fab);
    stack->addWidget(gridList);
    stack->addWidget(iconButton);
    stack->addWidget(materialList);
    stack->addWidget(listItem);
    stack->addWidget(loadingProgress);
    stack->addWidget(navigation);
    stack->addWidget(menu);
    stack->addWidget(paper);
    stack->addWidget(progress);
    stack->addWidget(radioButton);
    stack->addWidget(raisedButton);
    stack->addWidget(scrollBar);
    stack->addWidget(searchField);
    stack->addWidget(selectField);
    stack->addWidget(slider);
    stack->addWidget(snackbar);
    stack->addWidget(snackbarLayout);
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
    list->addItem("Date && Time Picker");
    list->addItem("Dialog");
    list->addItem("Divider");
    list->addItem("Drawer");
    list->addItem("Flat Button");
    list->addItem("Floating Action Button");
    list->addItem("Grid List");
    list->addItem("Icon Button");
    list->addItem("List");
    list->addItem("List Item");
    list->addItem("Loading + Progress");
    list->addItem("Navigation Bar");
    list->addItem("Menu");
    list->addItem("Paper");
    list->addItem("Progress");
    list->addItem("Radio Button");
    list->addItem("Raised Button");
    list->addItem("ScrollBar");
    list->addItem("Search Field");
    list->addItem("Select Field");
    list->addItem("Slider");
    list->addItem("Snackbar");
    list->addItem("Snackbar Layout");
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
