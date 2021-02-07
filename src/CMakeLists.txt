set (CMAKE_CXX_FLAGS "-Wall -Werror -std=c++17 -g -O0")

add_executable(ai-2048
    Game.cc
    Statistic.cc
    Table.cc
    Ui.cc
    UiText.cc
    main_text.cc
    )

target_link_libraries(ai-2048
    ncurses
    )

enable_testing()

add_subdirectory(test)
