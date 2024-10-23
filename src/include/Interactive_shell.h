#pragma once
#include <ncurses.h>

#define COLUMNS_SPLIT_RATIO 0.7

class Interactive_shell
{
public:
    bool exit = false;
    
    Interactive_shell();
    ~Interactive_shell();

    void update();
    void resize_UI();
private:
    WINDOW *_main_window;
    WINDOW *_left_window;
    WINDOW *_right_window;
};
