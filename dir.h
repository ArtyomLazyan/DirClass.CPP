#ifndef DIR_H
#define DIR_H

#include <iostream>
#include <fstream>
#include <dirent.h>
#include <unistd.h>
#include <ftw.h>
#include <vector>
#include <errno.h>
#include <string>

class Dir
{
private:
public:

    /* mkdir */
    static bool createDir(const std::string &path);

    /* rm -r */
    static bool removeDir(const std::string &path);

    /* pwd */
    static void currentPath();

    /* cd */
    static bool changeDir(const std::string &path);

    /* ls current path */
    static void dirList(const std::string &path);

    /* cp -r */
    static bool copyDir(const std::string &path, const std::string &destPath);

    /* mv -r */
    static bool moveDir(const std::string &path, const std::string &destPath);

    static void dirInfo(const std::string &path);

    static bool createPath(const std::string &path);

};

#endif
