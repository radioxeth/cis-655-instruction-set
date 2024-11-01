cmake_minimum_required(VERSION 3.10)

project(parser VERSION 0.0.1 LANGUAGES CXX)

add_library(${PROJECT_NAME}
    parser.cpp
    )

target_include_directories(${PROJECT_NAME}
    PUBLIC
    include
    )

target_link_libraries( ${PROJECT_NAME}
    instructions
    )

add_executable(${PROJECT_NAME}-test
    main.cpp
)

target_link_libraries(${PROJECT_NAME}-test
    ${PROJECT_NAME}
    )

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    LINKER_LANGUAGE CXX
)
