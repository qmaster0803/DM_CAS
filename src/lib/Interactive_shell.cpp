// Author: Komarov Daniil 3381

#include <algorithm>
#include <stdexcept>
#include "../include/Interactive_shell.h"

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
    _shell_lines.emplace_back("Welcome to DM CAS, written by Komarov Daniil & Ivanov Artyom, group 3381.");
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

    // reset help scroll position
    _first_help_line = 0;
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

    std::vector<std::string> help_msg_arr;
    help_msg_arr.push_back("In line with \"->\" you can write operations, which you want to calculate. In line \"=\" you can see calculated result;");
    help_msg_arr.push_back("F3 - to enable/disable autoscroll;");
    help_msg_arr.push_back("F4 - by default, all numbers interpreted as Natural, to switch calculation mode you need to press F4 key. So program have only four calculation modes: Natural, Integer, Rational, Polynomial. To use another data type without switch between modes, you need to add suffix: n - for Natural, i - for Integer, r - for Rational, p - for Polynomial;");
    help_msg_arr.push_back("F5 and F6 - to scroll help message;");
    help_msg_arr.push_back("To scroll in main area you need to use Page Up and Page Down buttons;");
    help_msg_arr.push_back("Also you can scroll by results and expressions by pressing Up arrow and Down arrow keys on keyboard.");
    help_msg_arr.push_back("Examples of writing types:");
    help_msg_arr.push_back("Natural: 1, 0, 2342, 43n;");
    help_msg_arr.push_back("Integer: -1098, 0, 213125, 12i;");
    help_msg_arr.push_back("Rational: -12/13, -15/-13, 23/-5, 5.6, 0.10, 0/5, 23, -5, 90/34r;");
    help_msg_arr.push_back("Polynomial: 1, 5, {5/3^3;1^0} (for polynomial like: (5/3)x^3 + 1), {56^2;1}p.");

    std::vector<std::string> actual_lines;
    for(const std::string &help_msg : help_msg_arr) {
        for(std::size_t i = 0, help_len = help_msg.length(); i < help_len; i += _prev_right_width - 3)
            actual_lines.push_back(help_msg.substr(i, _prev_right_width-3));
        actual_lines.push_back("");
    }

    std::size_t term_pos = 1;
    std::size_t vec_pos = _first_help_line;
    while(term_pos != (_prev_term_height - 2) &&
          vec_pos != actual_lines.size()) {
        wmove(_right_window, term_pos++, 1);
        waddstr(_right_window, actual_lines[vec_pos++].c_str());
    }

    wrefresh(_right_window);
    _prev_help_lines_count = actual_lines.size();
}

void Interactive_shell::_redraw_Hotkeys_help()
{
    std::vector<std::string> hotkeys;
    hotkeys.emplace_back((_autoscroll) ? "F3 - autoscroll: on " : "F3 - autoscroll: off");
    hotkeys.emplace_back("F4 - default type: ");
    switch(_deftype) {
        case default_vartype::VARTYPE_NATURAL:
            *(hotkeys.rbegin()) += "natural";
            break;
        case default_vartype::VARTYPE_INTEGER:
            *(hotkeys.rbegin()) += "integer";
            break;
        case default_vartype::VARTYPE_RATIONAL:
            *(hotkeys.rbegin()) += "rational";
            break;
        case default_vartype::VARTYPE_POLYNOMIAL:
            *(hotkeys.rbegin()) += "polynomial";
            break;
    }
    hotkeys.emplace_back("F5 - scroll help down");
    hotkeys.emplace_back("F6 - scroll help up");

    // summary length of mesgs
    std::size_t total_help_msg_len = 0;
    for(const std::string &i : hotkeys)
        total_help_msg_len += i.length();

    // spacing between msgs
    std::string result;
    if(_prev_term_width < total_help_msg_len + 4) {
        result = "Too small to show hotkeys";
    }
    else {
        std::size_t spacing = (_prev_term_width - total_help_msg_len) / (hotkeys.size() + 1);
        result = std::string(spacing, ' ');
        for(const std::string &i : hotkeys) {
            result += i;
            result += std::string(spacing, ' ');
        }
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

    // Print the shell line
    const std::size_t last_available_line = _prev_term_height - 6;
    std::size_t current_shell_line = 0;
    std::size_t current_term_line  = 1; // 0 line occupied by the box()
    
    while(current_term_line != last_available_line &&
          current_shell_line + _first_shell_line != _shell_lines.size()) {
        std::string line = _shell_lines[current_shell_line + _first_shell_line];

        // if line doesn't fit the screen, don't print it
        if(line.length() > ((_prev_left_width - 2)*(_prev_term_height-3)))
            line = "Line is too long to display, try resizing the window";
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
        // here goes the logic to fetch result into the variable
        const std::string &actual_line =_shell_lines[_shell_lines.size() - 1];
        std::size_t eq_sgn_count = std::count(actual_line.begin(), actual_line.end(), '=');
        std::string cmd;
        std::string varname;
        bool calc = true;
        
        if(eq_sgn_count == 0)
            cmd = actual_line.substr(3);
        else if(eq_sgn_count == 1) {
            cmd = actual_line.substr(actual_line.find('=') + 1);
            varname = actual_line.substr(3, actual_line.find('=') - 3);
            // prepare varname
            while(varname[0] == ' ') { varname.erase(varname.begin()); }
            while(*(varname.rbegin()) == ' ') { varname.erase(varname.end() - 1); }

            // analyze varname for wrong chars
            // <TODO>
        }
        else {
            calc = false;
            _shell_lines.push_back("!= Bad input string: wrong \"=\" usage");
            _rewind_skip_lines.insert(_shell_lines.size() - 1);
        }

        // Prepare cmd - replace variables with corresponding values
        while(std::count(cmd.begin(), cmd.end(), '$')) {
            // Get variable name
            std::size_t var_begin = cmd.find('$');
            std::size_t var_end   = cmd.find(' ', var_begin+1);
            std::string var_to_replace = cmd.substr(var_begin+1, var_end - var_begin - 1);

            if(_vars.count(var_to_replace) == 0) {
                calc = false;
                _shell_lines.push_back("!= Unknown variable: " + var_to_replace);
                _rewind_skip_lines.insert(_shell_lines.size() - 1);
                break;
            }
            cmd.erase(var_begin, var_end - var_begin);
            cmd.insert(var_begin, _vars[var_to_replace]);
        }

        // calculating the result
        if(calc) {
            try {
                std::string result = _parser.calc(_deftype, cmd);
                if(eq_sgn_count == 0)
                    _shell_lines.push_back("=  " + result);
                else {
                    _shell_lines.push_back("#= Result saved to the variable " + varname);
                    _rewind_skip_lines.insert(_shell_lines.size() - 1);
                    // save result to variable
                    _vars[varname] = result;
                }
            }
            catch (std::invalid_argument e) {
                _shell_lines.push_back("!= " + static_cast<std::string>(e.what()));
                _rewind_skip_lines.insert(_shell_lines.size() - 1);
            }
        }
        
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
            std::size_t prev_rew_i = _rewind_index;
            do {
                --_rewind_index;
            } while(_rewind_skip_lines.count(_rewind_index) != 0 &&
                    _rewind_index > 1);

            if(_rewind_skip_lines.count(_rewind_index) == 0) {
                _shell_lines[_shell_lines.size() - 1] = _shell_lines[_rewind_index];
                _cursor_pos = _shell_lines[_rewind_index].length();
                if(_shell_lines[_shell_lines.size() - 1][0] == '=') {
                    // fix line a little if rewinding to the result
                    _shell_lines[_shell_lines.size() - 1][0] = '-';
                    _shell_lines[_shell_lines.size() - 1][1] = '>';
                }
                _redraw_Shell();
            }
            else {
                _rewind_index = prev_rew_i;
            }
        }
    }
    else if(ch == KEY_DOWN) {
        if(_rewind_index < (_shell_lines.size() - 2)) {
            std::size_t prev_rew_i = _rewind_index;
            do {
                ++_rewind_index;
            } while(_rewind_skip_lines.count(_rewind_index) != 0 &&
                    _rewind_index < (_shell_lines.size() - 2));
            
            if(_rewind_skip_lines.count(_rewind_index) == 0) {
                _shell_lines[_shell_lines.size() - 1] = _shell_lines[_rewind_index];
                _cursor_pos = _shell_lines[_rewind_index].length();
                if(_shell_lines[_shell_lines.size() - 1][0] == '=') {
                    // fix line a little if rewinding to the result
                    _shell_lines[_shell_lines.size() - 1][0] = '-';
                    _shell_lines[_shell_lines.size() - 1][1] = '>';
                }
                _redraw_Shell();
            }
            else {
                _rewind_index = prev_rew_i;
            }
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
    else if(ch == KEY_F(4)) {
        _deftype = static_cast<default_vartype>((static_cast<int>(_deftype) + 1) % 4);
        _redraw_Hotkeys_help();
    }
    else if(ch == KEY_F(5)) {
        if((_first_help_line + 1) < _prev_help_lines_count) {
            ++_first_help_line;
            _redraw_Help();
        }
    }
    else if(ch == KEY_F(6)) {
        if(_first_help_line > 0) {
            --_first_help_line;
            _redraw_Help();
        }
    }
}
