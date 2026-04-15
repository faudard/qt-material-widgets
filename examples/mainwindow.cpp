#include "mainwindow.h"

#include <QHBoxLayout>
#include <QListWidget>
#include <QStackedLayout>
#include <QWidget>

#include "appbarsettingseditor.h"
#include "autocompletesettingseditor.h"
#include "avatarsettingseditor.h"
#include "badgesettingseditor.h"
#include "bannersettingseditor.h"
#include "bottomappbarsettingseditor.h"
#include "bottomsheetsettingseditor.h"
#include "buttongroupsettingseditor.h"
#include "carouselsettingseditor.h"
#include "centeredslidersettingseditor.h"
#include "checkboxsettingseditor.h"
#include "circularprogresssettingseditor.h"
#include "connectedbuttongroupsettingseditor.h"
#include "datepickervariantssettingseditor.h"
#include "daterangepickersettingseditor.h"
#include "datetimepickersettingseditor.h"
#include "dialogsettingseditor.h"
#include "dividersettingseditor.h"
#include "drawersettingseditor.h"
#include "expansionPanelSettingsEditor.h"
#include "fabmenusettingseditor.h"
#include "fabsettingseditor.h"
#include "flatbuttonsettingseditor.h"
#include "gridlistsettingseditor.h"
#include "iconbuttonsettingseditor.h"
#include "imagelistsettingseditor.h"
#include "listitemsettingseditor.h"
#include "listsettingseditor.h"
#include "loadingindicatorsettingseditor.h"
#include "loadingprogresssettingseditor.h"
#include "menusettingseditor.h"
#include "navigationrailsettingseditor.h"
#include "navigationsettingseditor.h"
#include "papersettingseditor.h"
#include "progresssettingseditor.h"
#include "radiobuttonsettingseditor.h"
#include "raisedbuttonsettingseditor.h"
#include "rangeslidersettingseditor.h"
#include "richtooltipsettingseditor.h"
#include "scrollbarsettingseditor.h"
#include "searchappbarsettingseditor.h"
#include "searchbarsettingseditor.h"
#include "searchfieldsettingseditor.h"
#include "searchviewsettingseditor.h"
#include "segmentedbuttonsettingseditor.h"
#include "selectfieldsettingseditor.h"
#include "sidesheetsettingseditor.h"
#include "skeletonsettingseditor.h"
#include "slidersettingseditor.h"
#include "snackbarlayoutsettingseditor.h"
#include "snackbarsettingseditor.h"
#include "speeddialsettingseditor.h"
#include "splitbuttonsettingseditor.h"
#include "steppersettingseditor.h"
#include "subheadersettingseditor.h"
#include "tablesettingseditor.h"
#include "tabssettingseditor.h"
#include "textfieldsettingseditor.h"
#include "toggleiconbuttonsettingseditor.h"
#include "togglesettingseditor.h"
#include "toolbarsettingseditor.h"
#include "toolbarvariantssettingseditor.h"
#include "tooltipsettingseditor.h"
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
    BannerSettingsEditor *banner = new BannerSettingsEditor;
    BottomAppBarSettingsEditor *bottomAppBar = new BottomAppBarSettingsEditor;
    BottomSheetSettingsEditor *bottomsheet = new BottomSheetSettingsEditor;
    ButtonGroupSettingsEditor *buttonGroupEditor = new ButtonGroupSettingsEditor;
    CarouselSettingsEditor *carousel = new CarouselSettingsEditor;
    CenteredSliderSettingsEditor *centeredSlider = new CenteredSliderSettingsEditor;
    CheckBoxSettingsEditor *checkbox = new CheckBoxSettingsEditor;
    CircularProgressSettingsEditor *circularProgress = new CircularProgressSettingsEditor;
    ConnectedButtonGroupSettingsEditor *connectedButtonGroupEditor = new ConnectedButtonGroupSettingsEditor;
    DatePickerVariantsSettingsEditor *datePickerVariants = new DatePickerVariantsSettingsEditor;
    RaisedButtonSettingsEditor *raisedButton = new RaisedButtonSettingsEditor;
    DateTimePickerSettingsEditor *dateTimePicker = new DateTimePickerSettingsEditor;
    DialogSettingsEditor *dialog = new DialogSettingsEditor;
    DividerSettingsEditor *divider = new DividerSettingsEditor;
    DrawerSettingsEditor *drawer = new DrawerSettingsEditor;
    ExpansionPanelSettingsEditor *expansionPanel = new ExpansionPanelSettingsEditor;
    FabMenuSettingsEditor *fabMenu = new FabMenuSettingsEditor;
    FlatButtonSettingsEditor *flatButton = new FlatButtonSettingsEditor;
    FloatingActionButtonSettingsEditor *fab = new FloatingActionButtonSettingsEditor;
    GridListSettingsEditor *gridList = new GridListSettingsEditor;
    IconButtonSettingsEditor *iconButton = new IconButtonSettingsEditor;
    ImageListSettingsEditor *imageList = new ImageListSettingsEditor(this);
    ListSettingsEditor *materialList = new ListSettingsEditor;
    ListItemSettingsEditor *listItem = new ListItemSettingsEditor;
    LoadingIndicatorSettingsEditor *loadingIndicator = new LoadingIndicatorSettingsEditor(this);
    LoadingProgressSettingsEditor *loadingProgress = new LoadingProgressSettingsEditor;
    MenuSettingsEditor *menu = new MenuSettingsEditor;
    NavigationSettingsEditor *navigation = new NavigationSettingsEditor;
    NavigationRailSettingsEditor *navigationRail = new NavigationRailSettingsEditor;
    PaperSettingsEditor *paper = new PaperSettingsEditor;
    ProgressSettingsEditor *progress = new ProgressSettingsEditor;
    RadioButtonSettingsEditor *radioButton = new RadioButtonSettingsEditor;
    RangeSliderSettingsEditor *rangeSlider = new RangeSliderSettingsEditor;
    DateRangePickerSettingsEditor *dateRangePicker = new DateRangePickerSettingsEditor;
    RichTooltipSettingsEditor *richTooltip = new RichTooltipSettingsEditor;
    ScrollBarSettingsEditor *scrollBar = new ScrollBarSettingsEditor;
    SearchAppBarSettingsEditor *searchAppBar = new SearchAppBarSettingsEditor(this);
    SearchBarSettingsEditor *searchBarEditor = new SearchBarSettingsEditor;
    SearchFieldSettingsEditor *searchField = new SearchFieldSettingsEditor;
    SearchViewSettingsEditor *searchView = new SearchViewSettingsEditor(this);
    SegmentedButtonSettingsEditor *segmentedButton = new SegmentedButtonSettingsEditor;
    SelectFieldSettingsEditor *selectField = new SelectFieldSettingsEditor;
    SideSheetSettingsEditor *sideSheet = new SideSheetSettingsEditor;
    SkeletonSettingsEditor *skeleton = new SkeletonSettingsEditor;
    SliderSettingsEditor *slider = new SliderSettingsEditor;
    SnackbarSettingsEditor *snackbar = new SnackbarSettingsEditor;
    SnackbarLayoutSettingsEditor *snackbarLayout = new SnackbarLayoutSettingsEditor;
    SpeedDialSettingsEditor *speedDial = new SpeedDialSettingsEditor;
    SplitButtonSettingsEditor *splitButton = new SplitButtonSettingsEditor(this);
    StepperSettingsEditor *stepper = new StepperSettingsEditor;
    SubheaderSettingsEditor *subheader = new SubheaderSettingsEditor;
    TableSettingsEditor *table = new TableSettingsEditor;
    TabsSettingsEditor *tabs = new TabsSettingsEditor;
    TextFieldSettingsEditor *textField = new TextFieldSettingsEditor;
    ToggleSettingsEditor *toggle = new ToggleSettingsEditor;
    ToggleIconButtonSettingsEditor *toggleIconButton = new ToggleIconButtonSettingsEditor;
    ToolbarSettingsEditor *toolbar = new ToolbarSettingsEditor;
    ToolbarVariantsSettingsEditor *toolbarVariants = new ToolbarVariantsSettingsEditor;
    TooltipSettingsEditor *tooltip = new TooltipSettingsEditor;
    TreeSettingsEditor *tree = new TreeSettingsEditor;

    stack->addWidget(appBar);
    stack->addWidget(autocomplete);
    stack->addWidget(avatar);
    stack->addWidget(badge);
    stack->addWidget(banner);
    stack->addWidget(bottomAppBar);
    stack->addWidget(bottomsheet);
    stack->addWidget(buttonGroupEditor);
    stack->addWidget(carousel);
    stack->addWidget(centeredSlider);
    stack->addWidget(checkbox);
    stack->addWidget(circularProgress);
    stack->addWidget(connectedButtonGroupEditor);
    stack->addWidget(datePickerVariants);
    stack->addWidget(raisedButton);
    stack->addWidget(dateTimePicker);
    stack->addWidget(dialog);
    stack->addWidget(divider);
    stack->addWidget(drawer);
    stack->addWidget(expansionPanel);
    stack->addWidget(fabMenu);
    stack->addWidget(flatButton);
    stack->addWidget(fab);
    stack->addWidget(gridList);
    stack->addWidget(iconButton);
    stack->addWidget(imageList);
    stack->addWidget(materialList);
    stack->addWidget(listItem);
    stack->addWidget(loadingIndicator);
    stack->addWidget(loadingProgress);
    stack->addWidget(menu);
    stack->addWidget(navigation);
    stack->addWidget(navigationRail);
    stack->addWidget(paper);
    stack->addWidget(progress);
    stack->addWidget(radioButton);
    stack->addWidget(rangeSlider);
    stack->addWidget(dateRangePicker);
    stack->addWidget(richTooltip);
    stack->addWidget(scrollBar);
    stack->addWidget(searchAppBar);
    stack->addWidget(searchBarEditor);
    stack->addWidget(searchField);
    stack->addWidget(searchView);
    stack->addWidget(segmentedButton);
    stack->addWidget(selectField);
    stack->addWidget(sideSheet);
    stack->addWidget(skeleton);
    stack->addWidget(slider);
    stack->addWidget(snackbar);
    stack->addWidget(snackbarLayout);
    stack->addWidget(speedDial);
    stack->addWidget(splitButton);
    stack->addWidget(stepper);
    stack->addWidget(subheader);
    stack->addWidget(table);
    stack->addWidget(tabs);
    stack->addWidget(textField);
    stack->addWidget(toggle);
    stack->addWidget(toggleIconButton);
    stack->addWidget(toolbar);
    stack->addWidget(toolbarVariants);
    stack->addWidget(tooltip);
    stack->addWidget(tree);

    list->addItem("App Bar");
    list->addItem("Auto Complete");
    list->addItem("Avatar");
    list->addItem("Badge");
    list->addItem("Banner");
    list->addItem("Bottom App Bar");
    list->addItem("BottomSheet");
    list->addItem("Button Group");
    list->addItem("Carousel");
    list->addItem("Centered Slider");
    list->addItem("Checkbox");
    list->addItem("Circular Progress");
    list->addItem("Connected Button");
    list->addItem("Date Picker Variants");
    list->addItem("Date Range Picker");
    list->addItem("Date && Time Picker");
    list->addItem("Dialog");
    list->addItem("Divider");
    list->addItem("Drawer");
    list->addItem("Expansion Panel");
    list->addItem("FAB Menu");
    list->addItem("Flat Button");
    list->addItem("Floating Action Button");
    list->addItem("Grid List");
    list->addItem("Icon Button");
    list->addItem("Image List");
    list->addItem("List");
    list->addItem("List Item");
    list->addItem("Loading Indicator");
    list->addItem("Loading + Progress");
    list->addItem("Menu");
    list->addItem("Navigation Bar");
    list->addItem("Navigation Rail");
    list->addItem("Paper");
    list->addItem("Progress");
    list->addItem("Radio Button");
    list->addItem("Raised Button");
    list->addItem("Range Slider");
    list->addItem(QStringLiteral("Rich Tooltip"));
    list->addItem("ScrollBar");
    list->addItem("Search App Bar");
    list->addItem("Search Bar");
    list->addItem("Search Field");
    list->addItem("Search View");
    list->addItem("Segmented Button");
    list->addItem("Select Field");
    list->addItem("Side Sheet");
    list->addItem("Skeleton");
    list->addItem("Slider");
    list->addItem("Snackbar");
    list->addItem("Snackbar Layout");
    list->addItem("Speed Dial");
    list->addItem("Split Button");
    list->addItem("Stepper");
    list->addItem("Subheaders");
    list->addItem("Table");
    list->addItem("Tabs");
    list->addItem("Text Field");
    list->addItem("Toggle");
    list->addItem("Toggle Icon Button");
    list->addItem("Toolbar");
    list->addItem("Toolbar variants");
    list->addItem("Tooltips");
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
