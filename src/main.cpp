#include "include/Interactive_shell.h"
#include <signal.h>


// some magic here to pass signal to the shell
bool sigwinch_occured = false;
void sigwinch_handler(int signal) { sigwinch_occured = true; }


int main()
{
    Interactive_shell shell;
    // signal(SIGWINCH, sigwinch_handler);

    while(!shell.exit) {
        shell.update();
        // shell.resize_UI();
    }
    return 0;
}
