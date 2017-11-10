#ifndef DIR_H
#define DIR_H

class Dir
{
private:
public:

    /* mkdir */
    static void createDir(const std::vector<std::string>& dirName);

    /* rm -r */
    static void removeDir(const std::vector<std::string>& dirName);

    /* pwd */
    static void currentPath();

    /* cd */
    static void changeDir(const std::vector<std::string>& dirName);

    /* ls current path */
    static void dirList(const std::vector<std::string>& dirName);

    /* cp -r */
    static void copyDir(const std::vector<std::string>& dirName);
    /* mv -r */
    static void moveDir(const std::vector<std::string>& dirName);
};

#endif
