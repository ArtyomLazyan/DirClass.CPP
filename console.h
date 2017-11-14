#ifndef CONSOLE_H
#define CONSOLE_H

#include <vector>
#include <string>

class Console
{
private:
    int width;
    int height;

    /* SumOfCharacter's const */
    enum COMMANDS {
        CREATEDIR = 947,
        REMOVEDIR = 973,
        CURRENTPATH = 1200,
        CHANGEDIR = 933,
        DIRLIST = 763,
        COPYDIR = 762,
        MOVEDIR = 758,
        DIRINFO = 747,
        CREATEPATH = 1057,
        RENAME = 632,
        CLEAR = 519,
        EXIT = 442
    };

public:
    Console();
    void startConsole();
    void clearScreen();
    void controller();
    int parser(std::vector<std::string> &);
    bool errorhandling(COMMANDS, const std::vector<std::string> &);
};
#endif
