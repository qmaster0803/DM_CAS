#include "include/Interactive_shell.h"
#include <signal.h>


int main()
{
    Interactive_shell shell;

    while(!shell.exit) {
        shell.update();
    }
    return 0;
}
