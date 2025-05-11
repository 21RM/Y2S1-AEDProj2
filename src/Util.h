#ifndef AED_PROJ_2_UTIL_H
#define AED_PROJ_2_UTIL_H

#include <iostream>
#include <sys/ioctl.h>

int getTerminalWidth() {
    struct winsize w{};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}
#endif // AED_PROJ_2_UTIL_H
