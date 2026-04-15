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