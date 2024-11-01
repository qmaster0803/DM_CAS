#include "include/Interactive_shell.h"

int main()
{
    Interactive_shell shell;

    while(!shell.exit) {
        shell.update();
    }
    return 0;
}
