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
        if(sigwinch_occured) {
            shell.resize_UI();
            sigwinch_occured = false;
        }
        // shell.update();
        shell.resize_UI();
    }
    return 0;
}
