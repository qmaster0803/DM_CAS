#include "../include/Interactive_shell.h"
#include <ncurses.h>
#include <cstddef>
#include <string>

Interactive_shell::Interactive_shell()
{
    // initializing the screen
    initscr();
    
    // creating windows
    std::size_t screen_width, screen_height;
    getmaxyx(stdscr, screen_height, screen_width);
    _main_window = subwin(stdscr, screen_height, screen_width, 0, 0);
    
    std::size_t left_win_width = screen_width * COLUMNS_SPLIT_RATIO;
    std::size_t right_win_width = screen_width - left_win_width;
    
    _left_window = subwin(_main_window, getmaxy(_main_window), left_win_width, 0, 0);
    box(_left_window, 0, 0);
    
    _right_window = subwin(_main_window, getmaxy(_main_window), right_win_width, 0, left_win_width);
    box(_right_window, 0, 0);

    wrefresh(_main_window);
}

Interactive_shell::~Interactive_shell()
{
    endwin();
}

void Interactive_shell::resize_UI()
{
    std::string out = "New X: " + std::to_string(getmaxx(stdscr));
    wmove(_left_window, 1, 1);
    waddstr(_left_window, out.c_str());
    wrefresh(_left_window);
}

void Interactive_shell::update()
{
    getch();
}
