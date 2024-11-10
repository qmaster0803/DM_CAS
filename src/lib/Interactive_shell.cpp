// Author: Komarov Daniil 3381

#include "../include/Interactive_shell.h"

Interactive_shell::Interactive_shell()
{
    // initializing the screen
    initscr();
    keypad(stdscr, TRUE);
    
    // creating windows
    std::size_t screen_width, screen_height;
    getmaxyx(stdscr, screen_height, screen_width);
    _prev_term_height = screen_height;
    _prev_term_width  = screen_width;
    _main_window = subwin(stdscr, screen_height, screen_width, 0, 0);
    
    std::size_t left_win_width = screen_width * COLUMNS_SPLIT_RATIO;
    std::size_t right_win_width = screen_width - left_win_width;
    
    _left_window = subwin(_main_window, screen_height, left_win_width, 0, 0);
    box(_left_window, 0, 0);
    
    _right_window = subwin(_main_window, screen_height, right_win_width, 0, left_win_width);
    box(_right_window, 0, 0);

    wrefresh(_main_window);

    // Initializing the UI
    _shell_lines.emplace_back("Welcome to DM CAS, written by Komarov Daniil & Ivanov Artem, group 3381.");
    _redraw_UI(true);
}

Interactive_shell::~Interactive_shell()
{
    endwin();
}

void Interactive_shell::_resize_UI(std::size_t new_term_height, std::size_t new_term_width)
{
    // clear all the previous data
    wclear(_main_window);

    // calculate new column width
    std::size_t left_win_width = new_term_width * COLUMNS_SPLIT_RATIO;
    std::size_t right_win_width = new_term_width - left_win_width;
    
    wresize(_left_window, new_term_height, left_win_width);
    
    wresize(_right_window, new_term_height, right_win_width);
    mvderwin(_right_window, 0, left_win_width);
}

void Interactive_shell::_redraw_UI(bool full_redraw)
{
    // redraw shell
    wclear(_left_window);
    box(_left_window, 0, 0);
    for(std::size_t line = _shell_first_line;
        line < (_shell_first_line + _prev_term_height - 2) && line < _shell_lines.size();
        line++) {
        wmove(_left_window, line+1, 1);
        waddstr(_left_window, std::to_string(line).c_str());
    }
}

void Interactive_shell::update()
{
    // check terminal size, resize UI if needed
    std::size_t screen_width, screen_height;
    getmaxyx(stdscr, screen_height, screen_width);
    if(screen_height != _prev_term_height || screen_width != _prev_term_width) {
        _resize_UI(screen_height, screen_width);
        
        _prev_term_height = screen_height;
        _prev_term_width  = screen_width;
        
        // fully redraw the UI
        _redraw_UI(true);
    }
    getch();
}
