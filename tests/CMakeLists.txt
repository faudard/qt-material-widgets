find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Test)

include(CTest)

add_executable(test_qtmateriallist
    test_qtmateriallist/test_qtmateriallist.cpp
)

target_link_libraries(test_qtmateriallist
    PRIVATE
        components
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Test
)

target_include_directories(test_qtmateriallist
    PRIVATE
        ${PROJECT_SOURCE_DIR}/components
)

add_test(NAME test_qtmateriallist COMMAND test_qtmateriallist)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test_qtmateriallistitem/test_qtmateriallistitem.cpp")
    add_executable(test_qtmateriallistitem
        test_qtmateriallistitem/test_qtmateriallistitem.cpp
    )

    target_link_libraries(test_qtmateriallistitem
        PRIVATE
            components
            Qt${QT_VERSION_MAJOR}::Core
            Qt${QT_VERSION_MAJOR}::Gui
            Qt${QT_VERSION_MAJOR}::Widgets
            Qt${QT_VERSION_MAJOR}::Test
    )

    target_include_directories(test_qtmateriallistitem
        PRIVATE
            ${PROJECT_SOURCE_DIR}/components
    )

    add_test(NAME test_qtmateriallistitem COMMAND test_qtmateriallistitem)
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test_qtmaterialtable/test_qtmaterialtable.cpp")
    add_executable(test_qtmaterialtable
        test_qtmaterialtable/test_qtmaterialtable.cpp
    )

    target_link_libraries(test_qtmaterialtable PRIVATE components Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Test)
    target_include_directories(test_qtmaterialtable PRIVATE ${PROJECT_SOURCE_DIR}/components)
    add_test(NAME test_qtmaterialtable COMMAND test_qtmaterialtable)
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test_qtmaterialcheckbox/test_qtmaterialcheckbox.cpp")
    add_executable(test_qtmaterialcheckbox
        test_qtmaterialcheckbox/test_qtmaterialcheckbox.cpp
    )

    target_link_libraries(test_qtmaterialcheckbox PRIVATE components Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Test)
    target_include_directories(test_qtmaterialcheckbox PRIVATE ${PROJECT_SOURCE_DIR}/components)
    add_test(NAME test_qtmaterialcheckbox COMMAND test_qtmaterialcheckbox)
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test_qtmaterialtoggle/test_qtmaterialtoggle.cpp")
    add_executable(test_qtmaterialtoggle
        test_qtmaterialtoggle/test_qtmaterialtoggle.cpp
    )

    target_link_libraries(test_qtmaterialtoggle PRIVATE components Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Test)
    target_include_directories(test_qtmaterialtoggle PRIVATE ${PROJECT_SOURCE_DIR}/components)
    add_test(NAME test_qtmaterialtoggle COMMAND test_qtmaterialtoggle)
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test_qtmaterialtextfield/test_qtmaterialtextfield.cpp")
    add_executable(test_qtmaterialtextfield
        test_qtmaterialtextfield/test_qtmaterialtextfield.cpp
    )

    target_link_libraries(test_qtmaterialtextfield PRIVATE components Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Test)
    target_include_directories(test_qtmaterialtextfield PRIVATE ${PROJECT_SOURCE_DIR}/components)
    add_test(NAME test_qtmaterialtextfield COMMAND test_qtmaterialtextfield)
endif()