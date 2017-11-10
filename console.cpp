#include <iostream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include "dir.h"
#include "console.h"

Console::Console()
{
    //consol size
    width = 110;
    height = 200;
}

void Console::startConsole()
{
    std::cout << "\n Commands: | dirlist | createdir | removedir | currentpath | changedir | copydir | movedir | clear | exit \n\n";

    for (int j = 0; j < width; j++)
        std::cout << "\u2593";
        std::cout << std::endl;

    while (true)
    {
        std::cout << "\n";
        Dir::currentPath();
        std::cout << " |\u279C ";

        Console::controller();
    }
}

void Console::controller()
{

    /* SumOfCharacter's const */
    enum { CREATEDIR = 947, REMOVEDIR = 973, CURRENTPATH = 1200, CHANGEDIR = 933, DIRLIST = 763, COPYDIR = 762, MOVEDIR = 758, CLEAR = 519, EXIT = 442 };

    // sum of char command for switch
    int sumOfChar = 0;

    // path (command + pathFrom + destinationPath)
    std::vector<std::string> path;
    std::string text;
    std::string word;

    std::getline(std::cin, text);
    std::stringstream ss(text);

    // path[0] = command path[1] = pathFrom path[2] = destinationPath
    while (ss >> word)
    {
        path.push_back(word);
    }

    // Subtract all caracter's of command
    for ( int k = 0; path[0][k] != '\0'; sumOfChar += path[0][k], k++ );

//    std::cout << sumOfChar << std::endl;

    // controll command
    switch (sumOfChar)
    {
        case CREATEDIR:
            Dir::createDir(path);
            break;

        case REMOVEDIR:
            Dir::removeDir(path);
            break;

        case CURRENTPATH:
            Dir::currentPath();
            break;

        case CHANGEDIR:
            Dir::changeDir(path);
            break;

        case DIRLIST:
            Dir::dirList(path);
            break;

        case COPYDIR:
            Dir::copyDir(path);
            break;

        case MOVEDIR:
            Dir::moveDir(path);
            break;

        case CLEAR:
            Console::clearScreen();
            break;

        case EXIT:
            exit(1);
            break;

        default:
            std::cout << "Error: Command not found.\n";
    }
}

void Console::clearScreen()
{
    // clear screen
    std:: cout << "\033[2J\033[1;1H";

    std::cout << "\n Commands: | dirlist | createdir | removedir | currentpath | changedir | copydir | movedir | clear | exit \n\n";

    for (int j = 0; j < width; j++)
        std::cout << "\u2593";
        std::cout << std::endl;
}


