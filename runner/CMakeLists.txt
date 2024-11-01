cmake_minimum_required(VERSION 3.10)

project(runner VERSION 0.0.1 LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    runner.cpp
    )

target_link_libraries(${PROJECT_NAME}
    alu
    parser
    )

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    CXX_STANDARD 20
    LINKER_LANGUAGE CXX
    )
