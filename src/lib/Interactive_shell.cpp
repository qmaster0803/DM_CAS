// Author: Komarov Daniil 3381

#include "../include/Interactive_shell.h"
#include <curses.h>

Interactive_shell::Interactive_shell()
{
    // initializing the screen
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    
    // creating windows
    std::size_t screen_width, screen_height;
    getmaxyx(stdscr, screen_height, screen_width);
    _prev_term_height = screen_height;
    _prev_term_width  = screen_width;
    _main_window = subwin(stdscr, screen_height, screen_width, 0, 0);
    
    std::size_t left_win_width = screen_width * COLUMNS_SPLIT_RATIO;
    std::size_t right_win_width = screen_width - left_win_width;
    _prev_left_width  = left_win_width;
    _prev_right_width = right_win_width;
    
    _left_window = subwin(_main_window, screen_height-1, left_win_width, 0, 0);
    box(_left_window, 0, 0);
    
    _right_window = subwin(_main_window, screen_height-1, right_win_width, 0, left_win_width);
    box(_right_window, 0, 0);
    

    // Initializing the UI
    _shell_lines.emplace_back("Welcome to DM CAS, written by Komarov Daniil & Ivanov Artem, group 3381.");
    _shell_lines.emplace_back("-> ");
    _cursor_pos = 3;
    _redraw_all();
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

    // resize windows
    wresize(_main_window, new_term_height, new_term_width);
    
    wresize(_left_window, new_term_height-1, left_win_width);
    
    wresize(_right_window, new_term_height-1, right_win_width);
    mvderwin(_right_window, 0, left_win_width);

    // save some values
    _prev_term_height = new_term_height;
    _prev_term_width  = new_term_width;
    _prev_left_width  = left_win_width;
    _prev_right_width = right_win_width;
}

void Interactive_shell::_redraw_all()
{
    _redraw_Shell();
    _redraw_Help();
    _redraw_Hotkeys_help();
}

void Interactive_shell::_redraw_Shell()
{
    wclear(_left_window);
    box(_left_window, 0, 0);
    wrefresh(_left_window);
}

void Interactive_shell::_redraw_Help()
{
    wclear(_right_window);
    box(_right_window, 0, 0);
}

void Interactive_shell::_redraw_Hotkeys_help()
{
    std::vector<std::string> hotkeys;
    hotkeys.emplace_back((_autoscroll) ? "F3 - autoscroll: on " : "F3 - autoscroll: off");
    hotkeys.emplace_back("F4 - scroll help down");
    hotkeys.emplace_back("F5 - scroll help up");

    // summary length of mesgs
    std::size_t total_help_msg_len = 0;
    for(const std::string &i : hotkeys)
        total_help_msg_len += i.length();

    // spacing between msgs
    std::size_t spacing = (_prev_term_width - total_help_msg_len) / (hotkeys.size() + 1);

    std::string result = std::string(spacing, ' ');
    for(const std::string &i : hotkeys) {
        result += i;
        result += std::string(spacing, ' ');
    }
    
    wmove(_main_window, _prev_term_height-1, 0);
    waddstr(_main_window, result.c_str());
    wrefresh(_main_window);
}

void Interactive_shell::update()
{
    // check terminal size, resize UI if needed
    std::size_t screen_width, screen_height;
    getmaxyx(stdscr, screen_height, screen_width);
    if(screen_height != _prev_term_height || screen_width != _prev_term_width) {
        _resize_UI(screen_height, screen_width);
                
        _redraw_all();
    }
    // else
    //     _redraw_all();

    // Print the shell line
    const std::size_t last_available_line = _prev_term_height - 6;
    std::size_t current_shell_line = 0;
    std::size_t current_term_line  = 1; // 0 line occupied by the box()
    
    while(current_term_line != last_available_line &&
          current_shell_line + _first_shell_line != _shell_lines.size()) {
        std::string line = _shell_lines[current_shell_line + _first_shell_line];
        
        // insert line breaks if the string is greater than window width
        for(std::size_t i = 0; i < line.length(); i += _prev_left_width - 2) {
            wmove(_left_window, current_term_line, 1);
            waddstr(_left_window, line.substr(i, _prev_left_width - 2).c_str());
            ++current_term_line;
        }

        ++current_shell_line;
    }
    
    --current_term_line; // correct overshoot caused by adding every line the same way
    // move cursor to the correct place
    std::size_t cur_x = _cursor_pos % (_prev_left_width - 2);
    move(current_term_line + (_cursor_pos > 0 && cur_x == 0), 1+cur_x);
    wrefresh(_left_window);

    int ch = getch();
    if(ch >= 32 && ch <= 126) { // "normal" (printable) char
        _shell_lines[_shell_lines.size() - 1].insert(_cursor_pos, 1, static_cast<char>(ch));
        ++_cursor_pos;
    }
    else if(ch == KEY_BACKSPACE) {
        if(_cursor_pos > 3) {
            _shell_lines[_shell_lines.size() - 1].erase(_cursor_pos-1, 1);
            --_cursor_pos;
            _redraw_Shell();
        }
    }
    else if(ch == '\n') {        
        // calculate the result
        std::string result = "= ";
        // <TODO>
        result += " result goes here";
        _shell_lines.emplace_back(result);
        
        // scroll down if autoscroll is enabled
        if(!_autoscroll && (current_term_line + 1) >= last_available_line) {
            // add space for the result
            _first_shell_line += (_shell_lines[_shell_lines.size() - 1].length() / (_prev_left_width - 2)) + 1;
            // add space for the cmd itself
            _first_shell_line += (_shell_lines[_shell_lines.size() - 2].length() / (_prev_left_width - 2)) + 1;
            // undo user scroll
            _first_shell_line -= _scroll_pos;
        }
        else if(_autoscroll)
            _first_shell_line = _shell_lines.size() - 2;

        // Add prompt
        _shell_lines.emplace_back("-> ");
        _cursor_pos = 3;
        _scroll_pos = 0;
        _redraw_Shell();

        // Reset rewind index
        _rewind_index = _shell_lines.size() - 1;
    }
    else if(ch == KEY_LEFT) {
        if(_cursor_pos > 3)
            --_cursor_pos;
    }
    else if(ch == KEY_RIGHT) {
        if(_cursor_pos < _shell_lines[_shell_lines.size() - 1].length())
            ++_cursor_pos;
    }
    else if(ch == KEY_UP) {
        if(_rewind_index > 1) {
            --_rewind_index;
            _shell_lines[_shell_lines.size() - 1] = _shell_lines[_rewind_index];
            _cursor_pos = _shell_lines[_rewind_index].length();
            if(_shell_lines[_shell_lines.size() - 1][0] == '=') {
                // fix line a little if rewinding to the result
                _shell_lines[_shell_lines.size() - 1][0] = '-';
                _shell_lines[_shell_lines.size() - 1][1] = '>';
            }
            _redraw_Shell();
        }
    }
    else if(ch == KEY_DOWN) {
        if(_rewind_index < (_shell_lines.size() - 2)) {
            ++_rewind_index;
            _shell_lines[_shell_lines.size() - 1] = _shell_lines[_rewind_index];
            _cursor_pos = _shell_lines[_rewind_index].length();
            if(_shell_lines[_shell_lines.size() - 1][0] == '=') {
                // fix line a little if rewinding to the result
                _shell_lines[_shell_lines.size() - 1][0] = '-';
                _shell_lines[_shell_lines.size() - 1][1] = '>';
            }
            _redraw_Shell();
        }
    }
    else if(ch == KEY_NPAGE) {
        if(_first_shell_line < (_shell_lines.size() - 1)) {
            ++_first_shell_line;
            ++_scroll_pos;
            _redraw_Shell();
        }
    }
    else if(ch == KEY_PPAGE) {
        if(_first_shell_line > 0) {
            --_first_shell_line;
            --_scroll_pos;
            _redraw_Shell();
        }
    }
    else if(ch == KEY_HOME) {
        _cursor_pos = 3;
    }
    else if(ch == KEY_END) {
        _cursor_pos = _shell_lines[_shell_lines.size() - 1].length();
    }
    else if(ch == KEY_F(3)) {
        _autoscroll = !_autoscroll;
        _redraw_Hotkeys_help();
    }
}
