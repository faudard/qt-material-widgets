file(GLOB EXAMPLE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

file(GLOB EXAMPLE_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

file(GLOB EXAMPLE_FORMS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.ui"
)

set(EXAMPLE_RESOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/examples.qrc"
)

add_executable(examples-exe
    ${EXAMPLE_SOURCES}
    ${EXAMPLE_HEADERS}
    ${EXAMPLE_FORMS}
    ${EXAMPLE_RESOURCES}
)

target_link_libraries(examples-exe
    PRIVATE
        components
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
)

target_include_directories(examples-exe
    PRIVATE
        ${CMAKE_SOURCE_DIR}/components
)