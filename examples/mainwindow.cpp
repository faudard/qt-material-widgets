#include "mainwindow.h"

#include <QHBoxLayout>
#include <QListWidget>
#include <QStackedLayout>
#include <QWidget>

#include "appbarbehaviorsettingseditor.h"
#include "appbarsettingseditor.h"
#include "appbarstatelaysettingseditor.h"
#include "autocompletesettingseditor.h"
#include "avatarsettingseditor.h"
#include "badgesettingseditor.h"
#include "bannersettingseditor.h"
#include "bottomappbarsettingseditor.h"
#include "bottomsheetsettingseditor.h"
#include "bottomsheetvariantssettingseditor.h"
#include "buttongroupsettingseditor.h"
#include "carouselsettingseditor.h"
#include "centeredslidersettingseditor.h"
#include "checkboxsettingseditor.h"
#include "chipvariantssettingseditor.h"
#include "circularprogresssettingseditor.h"
#include "connectedbuttongroupsettingseditor.h"
#include "datepickervariantssettingseditor.h"
#include "daterangepickersettingseditor.h"
#include "datetimepickersettingseditor.h"
#include "dialogsettingseditor.h"
#include "dividersettingseditor.h"
#include "drawersettingseditor.h"
#include "expansionPanelSettingsEditor.h"
#include "extendedfabsettingseditor.h"
#include "fabmenusettingseditor.h"
#include "fabsettingseditor.h"
#include "flatbuttonsettingseditor.h"
#include "flexiblenavigationbarsettingseditor.h"
#include "fulldialogsettingseditor.h"
#include "gridlistsettingseditor.h"
#include "iconbuttonsettingseditor.h"
#include "imagelistsettingseditor.h"
#include "listitemsettingseditor.h"
#include "listsettingseditor.h"
#include "loadingindicatorsettingseditor.h"
#include "loadingprogresssettingseditor.h"
#include "menusettingseditor.h"
#include "navigationbadgessettingseditor.h"
#include "navigationrailsettingseditor.h"
#include "navigationsettingseditor.h"
#include "papersettingseditor.h"
#include "progresssettingseditor.h"
#include "radiobuttonsettingseditor.h"
#include "raisedbuttonsettingseditor.h"
#include "rangeslidersettingseditor.h"
#include "responsivenavigationsettingseditor.h"
#include "richtooltipsettingseditor.h"
#include "scrollbarsettingseditor.h"
#include "searchappbarsettingseditor.h"
#include "searchbarsettingseditor.h"
#include "searchfieldsettingseditor.h"
#include "searchviewmodelsettingseditor.h"
#include "searchviewsettingseditor.h"
#include "segmentedbuttonsettingseditor.h"
#include "selectfieldsettingseditor.h"
#include "sheetdetentsettingseditor.h"
#include "sheethandlesettingseditor.h"
#include "sidesheetsettingseditor.h"
#include "sidesheetvariantssettingseditor.h"
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
#include "timefieldsettingseditor.h"
#include "toggleiconbuttonsettingseditor.h"
#include "togglesettingseditor.h"
#include "toolbarsettingseditor.h"
#include "toolbarvariantssettingseditor.h"
#include "tooltipsettingseditor.h"
#include "topappbarscrollsettingseditor.h"
#include "topappbarvariantssettingseditor.h"
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
    AppBarBehaviorSettingsEditor *appBarBehavior = new AppBarBehaviorSettingsEditor(this);
    AppBarStateLayerSettingsEditor *appBarStateLayer = new AppBarStateLayerSettingsEditor(this);
    AutoCompleteSettingsEditor *autocomplete = new AutoCompleteSettingsEditor;
    AvatarSettingsEditor *avatar = new AvatarSettingsEditor;
    BadgeSettingsEditor *badge = new BadgeSettingsEditor(this);
    BannerSettingsEditor *banner = new BannerSettingsEditor;
    BottomAppBarSettingsEditor *bottomAppBar = new BottomAppBarSettingsEditor;
    BottomSheetVariantsSettingsEditor *bottomSheetVariants = new BottomSheetVariantsSettingsEditor(this);
    BottomSheetSettingsEditor *bottomsheet = new BottomSheetSettingsEditor;
    ButtonGroupSettingsEditor *buttonGroupEditor = new ButtonGroupSettingsEditor;
    CarouselSettingsEditor *carousel = new CarouselSettingsEditor;
    CenteredSliderSettingsEditor *centeredSlider = new CenteredSliderSettingsEditor;
    CheckBoxSettingsEditor *checkbox = new CheckBoxSettingsEditor;
    ChipVariantsSettingsEditor *chipVariants = new ChipVariantsSettingsEditor(this);
    CircularProgressSettingsEditor *circularProgress = new CircularProgressSettingsEditor;
    ConnectedButtonGroupSettingsEditor *connectedButtonGroupEditor = new ConnectedButtonGroupSettingsEditor;
    DatePickerVariantsSettingsEditor *datePickerVariants = new DatePickerVariantsSettingsEditor;
    RaisedButtonSettingsEditor *raisedButton = new RaisedButtonSettingsEditor;
    DateTimePickerSettingsEditor *dateTimePicker = new DateTimePickerSettingsEditor;
    DialogSettingsEditor *dialog = new DialogSettingsEditor;
    DividerSettingsEditor *divider = new DividerSettingsEditor;
    DrawerSettingsEditor *drawer = new DrawerSettingsEditor;
    ExpansionPanelSettingsEditor *expansionPanel = new ExpansionPanelSettingsEditor;
    ExtendedFabSettingsEditor *extendedFab = new ExtendedFabSettingsEditor;
    FabMenuSettingsEditor *fabMenu = new FabMenuSettingsEditor;
    FlatButtonSettingsEditor *flatButton = new FlatButtonSettingsEditor;
    FlexibleNavigationBarSettingsEditor *flexibleNavigationBar = new FlexibleNavigationBarSettingsEditor(this);
    FloatingActionButtonSettingsEditor *fab = new FloatingActionButtonSettingsEditor;
    FullDialogSettingsEditor *fullDialogEditor = new FullDialogSettingsEditor;
    GridListSettingsEditor *gridList = new GridListSettingsEditor;
    IconButtonSettingsEditor *iconButton = new IconButtonSettingsEditor;
    ImageListSettingsEditor *imageList = new ImageListSettingsEditor(this);
    ListSettingsEditor *materialList = new ListSettingsEditor;
    ListItemSettingsEditor *listItem = new ListItemSettingsEditor;
    LoadingIndicatorSettingsEditor *loadingIndicator = new LoadingIndicatorSettingsEditor(this);
    LoadingProgressSettingsEditor *loadingProgress = new LoadingProgressSettingsEditor;
    MenuSettingsEditor *menu = new MenuSettingsEditor;
    NavigationBadgesSettingsEditor *navigationBadges = new NavigationBadgesSettingsEditor;
    NavigationSettingsEditor *navigation = new NavigationSettingsEditor;
    NavigationRailSettingsEditor *navigationRail = new NavigationRailSettingsEditor;
    PaperSettingsEditor *paper = new PaperSettingsEditor;
    ProgressSettingsEditor *progress = new ProgressSettingsEditor;
    RadioButtonSettingsEditor *radioButton = new RadioButtonSettingsEditor;
    RangeSliderSettingsEditor *rangeSlider = new RangeSliderSettingsEditor;
    DateRangePickerSettingsEditor *dateRangePicker = new DateRangePickerSettingsEditor;
    ResponsiveNavigationSettingsEditor *responsiveNavigation = new ResponsiveNavigationSettingsEditor;
    RichTooltipSettingsEditor *richTooltip = new RichTooltipSettingsEditor;
    ScrollBarSettingsEditor *scrollBar = new ScrollBarSettingsEditor;
    SearchAppBarSettingsEditor *searchAppBar = new SearchAppBarSettingsEditor(this);
    SearchBarSettingsEditor *searchBarEditor = new SearchBarSettingsEditor;
    SearchFieldSettingsEditor *searchField = new SearchFieldSettingsEditor;
    SearchViewSettingsEditor *searchView = new SearchViewSettingsEditor(this);
    SearchViewModelSettingsEditor *searchViewModel = new SearchViewModelSettingsEditor;
    SegmentedButtonSettingsEditor *segmentedButton = new SegmentedButtonSettingsEditor;
    SelectFieldSettingsEditor *selectField = new SelectFieldSettingsEditor;
    SheetDetentSettingsEditor *sheetDetent = new SheetDetentSettingsEditor;
    SheetHandleSettingsEditor *sheetHandle = new SheetHandleSettingsEditor(this);
    SideSheetSettingsEditor *sideSheet = new SideSheetSettingsEditor;
    SideSheetVariantsSettingsEditor *sideSheetVariants = new SideSheetVariantsSettingsEditor(this);
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
    TimeFieldSettingsEditor *timeField = new TimeFieldSettingsEditor;
    ToggleSettingsEditor *toggle = new ToggleSettingsEditor;
    ToggleIconButtonSettingsEditor *toggleIconButton = new ToggleIconButtonSettingsEditor;
    ToolbarSettingsEditor *toolbar = new ToolbarSettingsEditor;
    ToolbarVariantsSettingsEditor *toolbarVariants = new ToolbarVariantsSettingsEditor;
    TooltipSettingsEditor *tooltip = new TooltipSettingsEditor;
    TopAppBarVariantsSettingsEditor *topAppBarVariants = new TopAppBarVariantsSettingsEditor(this);
    TopAppBarScrollSettingsEditor *topAppBarScroll = new TopAppBarScrollSettingsEditor;
    TreeSettingsEditor *tree = new TreeSettingsEditor;

    stack->addWidget(appBar);
    stack->addWidget(appBarBehavior);
    // stack->addWidget(appBarStateLayer);
    stack->addWidget(autocomplete);
    stack->addWidget(avatar);
    stack->addWidget(badge);
    stack->addWidget(banner);
    stack->addWidget(bottomAppBar);
    stack->addWidget(bottomSheetVariants);
    stack->addWidget(bottomsheet);
    stack->addWidget(buttonGroupEditor);
    stack->addWidget(carousel);
    stack->addWidget(centeredSlider);
    stack->addWidget(checkbox);
    stack->addWidget(chipVariants);
    stack->addWidget(circularProgress);
    stack->addWidget(connectedButtonGroupEditor);
    stack->addWidget(datePickerVariants);
    stack->addWidget(raisedButton);
    stack->addWidget(dateTimePicker);
    stack->addWidget(dialog);
    stack->addWidget(divider);
    stack->addWidget(drawer);
    stack->addWidget(expansionPanel);
    stack->addWidget(extendedFab);
    stack->addWidget(fabMenu);
    stack->addWidget(flatButton);
    stack->addWidget(flexibleNavigationBar);
    stack->addWidget(fab);
    stack->addWidget(fullDialogEditor);
    stack->addWidget(gridList);
    stack->addWidget(iconButton);
    stack->addWidget(imageList);
    stack->addWidget(materialList);
    stack->addWidget(listItem);
    stack->addWidget(loadingIndicator);
    stack->addWidget(loadingProgress);
    stack->addWidget(menu);
    stack->addWidget(navigationBadges);
    stack->addWidget(navigation);
    stack->addWidget(navigationRail);
    stack->addWidget(paper);
    stack->addWidget(progress);
    stack->addWidget(radioButton);
    stack->addWidget(rangeSlider);
    stack->addWidget(dateRangePicker);
    stack->addWidget(responsiveNavigation);
    stack->addWidget(richTooltip);
    stack->addWidget(scrollBar);
    stack->addWidget(searchAppBar);
    stack->addWidget(searchBarEditor);
    stack->addWidget(searchField);
    stack->addWidget(searchView);
    stack->addWidget(searchViewModel);
    stack->addWidget(segmentedButton);
    stack->addWidget(selectField);
    stack->addWidget(sheetDetent);
    stack->addWidget(sheetHandle);
    stack->addWidget(sideSheet);
    stack->addWidget(sideSheetVariants);
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
    stack->addWidget(timeField);
    stack->addWidget(toggle);
    stack->addWidget(toggleIconButton);
    stack->addWidget(toolbar);
    stack->addWidget(toolbarVariants);
    stack->addWidget(tooltip);
    stack->addWidget(topAppBarVariants);
    stack->addWidget(topAppBarScroll);
    stack->addWidget(tree);

    list->addItem("App Bar");
    list->addItem("App Bar Behavior");
    // list->addItem("App Bar State Layer");
    list->addItem("Auto Complete");
    list->addItem("Avatar");
    list->addItem("Badges");
    list->addItem("Banner");
    list->addItem("Bottom App Bar");
    list->addItem(QStringLiteral("Bottom Sheet Variants"));
    list->addItem("BottomSheet");
    list->addItem("Button Group");
    list->addItem("Carousel");
    list->addItem("Centered Slider");
    list->addItem("Checkbox");
    list->addItem("Chip Variants");
    list->addItem("Circular Progress");
    list->addItem("Connected Button");
    list->addItem("Date Picker Variants");
    list->addItem("Date Range Picker");
    list->addItem("Date && Time Picker");
    list->addItem("Dialog");
    list->addItem("Divider");
    list->addItem("Drawer");
    list->addItem("Expansion Panel");
    list->addItem("Extended FAB");
    list->addItem("FAB Menu");
    list->addItem("Flat Button");
    list->addItem("Flexible Navigation Bar");
    list->addItem("Floating Action Button");
    list->addItem(QStringLiteral("Full-screen Dialog"));
    list->addItem("Grid List");
    list->addItem("Icon Button");
    list->addItem("Image List");
    list->addItem("List");
    list->addItem("List Item");
    list->addItem("Loading Indicator");
    list->addItem("Loading + Progress");
    list->addItem("Menu");
    list->addItem("Navigation badges");
    list->addItem("Navigation Bar");
    list->addItem("Navigation Rail");
    list->addItem("Paper");
    list->addItem("Progress");
    list->addItem("Radio Button");
    list->addItem("Raised Button");
    list->addItem("Range Slider");
    list->addItem(QStringLiteral("Responsive Navigation"));
    list->addItem(QStringLiteral("Rich Tooltip"));
    list->addItem("ScrollBar");
    list->addItem("Search App Bar");
    list->addItem("Search Bar");
    list->addItem("Search Field");
    list->addItem("Search View");
    list->addItem("Search View Model");
    list->addItem("Segmented Button");
    list->addItem("Select Field");
    list->addItem("Sheet Detent");
    list->addItem(QStringLiteral("Sheet Handle"));
    list->addItem("Side Sheet");
    list->addItem("Side Sheet Variants");
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
    list->addItem("Time Field");
    list->addItem("Toggle");
    list->addItem("Toggle Icon Button");
    list->addItem("Toolbar");
    list->addItem("Toolbar variants");
    list->addItem("Tooltips");
    list->addItem("Top App Bar Variants");
    list->addItem("Top AppBar Scroll");
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
