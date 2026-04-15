file(GLOB_RECURSE COMPONENT_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

file(GLOB_RECURSE COMPONENT_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

set(COMPONENT_RESOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc"
)

add_library(components STATIC
    ${COMPONENT_SOURCES}
    ${COMPONENT_HEADERS}
    ${COMPONENT_RESOURCES}
)

target_link_libraries(components
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
)

target_include_directories(components
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/layouts
)