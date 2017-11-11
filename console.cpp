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
    std::cout << "\n Commands: | dirlist | createdir | removedir | currentpath | changedir | copydir | movedir | clear | exit \n\n\
           | dirinfo | createpath |    \n\n";

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

bool Console::errorhandling(COMMANDS command, const std::vector<std::string> &buff)
{

    if (buff.empty())
    {
        std::cout << "Enter command." << std::endl;
        return false;
    }

    // controll command
    switch (command)
    {
        case CREATEDIR:
        case CREATEPATH:
        case REMOVEDIR:
        case CHANGEDIR:
            if (buff.size() != 2)
            {
                std::cout << "Invalid number of arguments." << std::endl;
                return false;
            }
            else
                return true;
            break;

        case COPYDIR:
        case MOVEDIR:
                if (buff.size() != 3)
                {
                    std::cout << "Invalid number of arguments." << std::endl;
                    return false;
                }
                else
                    return true;
                break;

        case DIRLIST:
                if (buff.size() == 2)
                    return true;
                else
                    return false;
        case CURRENTPATH:
        case DIRINFO:
        case CLEAR:
        case EXIT:
                return true;
                break;

        default:
            std::cout << "Error: Command not found.\n";
            return false;
    }

    return true;
}

int Console::parser(std::vector<std::string> &buff)
{
    int sumOfChar = 0;
    std::string text;
    std::string word;

    std::getline(std::cin, text);
    std::stringstream ss(text);

    // path[0] = command path[1] = pathFrom path[2] = destinationPath
    while (ss >> word)
    {
        buff.push_back(word);
    }

    // Subtract all caracter's of buff[0] - command
    for ( int k = 0; buff[0][k] != '\0'; sumOfChar += buff[0][k], k++ );

    // return sumof characters command for switch
    return sumOfChar;
}

void Console::controller()
{

    // path (command + pathFrom + destinationPath)
    std::vector<std::string> buff;
    std::string path;
    std::string destPath;

    // sum of char command for switch
    COMMANDS command = COMMANDS(Console::parser(buff));

    //std::cout << sumOfChar << std::endl;
    bool flag = Console::errorhandling(command, buff);

    if ((command == DIRLIST) && !flag)
    {
        path = ".";
        Dir::dirList(path);
    }

    if(flag)
    {
       // controll command
        switch (command)
        {
            case CREATEDIR:
                path = buff[1];
                Dir::createDir(path);
                break;

            case CREATEPATH:
                path = buff[1];
                Dir::createPath(path);
                break;

            case REMOVEDIR:
                path = buff[1];
                Dir::removeDir(path);
                break;

            case CURRENTPATH:
                Dir::currentPath();
                break;

            case CHANGEDIR:
                path = buff[1];
                Dir::changeDir(path);
                break;

            case DIRLIST:
                path = buff[1];
                Dir::dirList(path);
                break;

            case COPYDIR:
                path = buff[1];
                destPath = buff[2];
                Dir::copyDir(path, destPath);
                break;

            case MOVEDIR:
                path = buff[1];
                destPath = buff[2];
                Dir::moveDir(path, destPath);
                break;

            case DIRINFO:
                Dir::dirInfo(path);
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
 }

void Console::clearScreen()
{
    // clear screen
    std:: cout << "\033[2J\033[1;1H";

    std::cout << "\n Commands: | dirlist | createdir | removedir | currentpath | changedir | copydir | movedir | clear | exit \n\n\
           | dirinfo | createpath |    \n\n";
    for (int j = 0; j < width; j++)
        std::cout << "\u2593";
        std::cout << std::endl;
}


