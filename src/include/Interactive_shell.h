// Author: Komarov Daniil 3381

#pragma once
#include <ncurses.h>
#include <cstddef>
#include <vector>
#include <string>

#define COLUMNS_SPLIT_RATIO 0.7

struct CMD
{
    std::string cmd;
    std::string result;
};

class Interactive_shell
{
public:
    bool exit = false;
    
    Interactive_shell();
    ~Interactive_shell();

    void update();
private:
    // ncurses windows
    WINDOW *_main_window;
    WINDOW *_left_window;
    WINDOW *_right_window;

    // previous terminal size to handle resizing
    std::size_t _prev_term_height, _prev_term_width;

    // what to show in the right column - help or history
    bool _show_help = false;

    // vector that stores history of the commands
    std::vector<CMD> _cmd_history;

    // vector stores every line typed in shell window
    std::vector<std::string> _shell_lines;
    // this variable stores the FIRST displayed line (the oldest one, displayed at the top of the screen)
    std::size_t _shell_first_line = 0;

    void _resize_UI(std::size_t new_term_height, std::size_t new_term_width);
    void _redraw_UI(bool full_redraw = false);
};
