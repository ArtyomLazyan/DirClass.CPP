#ifndef CONSOLE_H
#define CONSOLE_H

#include <vector>

class Console
{
private:
    int width;
    int height;
public:
    Console();
    void startConsole();
    void clearScreen();
    void controller();
};
#endif
