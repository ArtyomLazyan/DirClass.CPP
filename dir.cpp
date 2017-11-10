#include <iostream>
#include <fstream>
#include <dirent.h>
#include <unistd.h>
#include <ftw.h>
#include <vector>
#include "dir.h"

/* recurent functions for copydir and removedir */
namespace NFTW {

    /* function which is called from Dir::removedir() / nftw() function */
    int deleteDirTree(const char *fpath, const struct stat *sb,
            int tflag, struct FTW *ftwbuf)
    {
        int rv = remove(fpath);

        if (rv)
            perror(fpath);

        return rv;
    }

    // destination path for copy
    std::string to;

    /* function which is called from Dir::copyDir() nftw() function */
    int display_info(const char *fpath, const struct stat *sb,
                         int tflag, struct FTW *ftwbuf)
    {
        // complete destination path for copy folder
        std::string destPath = to;
        destPath.append("/");
        destPath.append(fpath);

        switch (tflag)
        {
            // tflag 's
            // if dir then mkdir, if file then create file
            case 1:
                mkdir(destPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                break;

            case 0:
                std::ifstream  src(fpath, std::ios::binary);
                std::ofstream  dst(destPath.c_str(), std::ios::binary);
                dst << src.rdbuf();
                break;
        }

        return 0; /* To tell nftw() to continue */
    }
}

/* ****************************************************** */

void Dir::createDir(const std::vector<std::string>& dirName)
{
  /*  File mode bits:

        S_IRWXU
            read, write, execute/search by owner
        S_IRUSR
            read permission, owner
        S_IWUSR
            write permission, owner
        S_IXUSR
            execute/search permission, owner
        S_IRWXG
            read, write, execute/search by group
        S_IRGRP
            read permission, group
        S_IWGRP
            write permission, group
        S_IXGRP
            execute/search permission, group
        S_IRWXO
            read, write, execute/search by others
        S_IROTH
            read permission, others
        S_IWOTH
            write permission, others
        S_IXOTH
            execute/search permission, others
        S_ISUID
            set-user-ID on execution
        S_ISGID
            set-group-ID on execution
        S_ISVTX
            on directories, restricted deletion flag
    */


    /*
     * int mkdir(const char *path, mode_t mode);
     */
    if (mkdir(dirName[1].c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
    {
       // Interprets the value of errno as an error message
       perror("createdir");
    }
    else
    {
        std::cout << "File was successfully created!\n";
    }
}

void Dir::removeDir(const std::vector<std::string>& dirName)
{
    // nftw() walks through the directory tree that is located under the directory dirpath,
    // and calls deleteDirTree() once for each entry in the tree

    if (dirName.size() == 1)
    {
        std::cout << "Error: Enter folder name.\n";
    }
    else
    {
       if (nftw(dirName[1].c_str(), NFTW::deleteDirTree, 20, FTW_DEPTH) != 0)
            perror("removedir");
        else
            std::cout << "directory was deleted succsessfully.\n";
    }
 }

void Dir::currentPath()
{
    char buff[1024];

    /*
     * char *getcwd(char *buf, size_t size);
     * @return buf
     */
    if (getcwd(buff, sizeof(buff)) == NULL)
    {
        std::cout << "Error: can't display current directory.";
    }
    else
    {
        std::cout << buff;
    }
}

void Dir::changeDir(const std::vector<std::string>& dirName)
{
    /*
     * int chdir(const char *path);
     */
    if (chdir(dirName[1].c_str()) == -1)
    {
      perror("changedir");
    }
}

void Dir::dirList(const std::vector<std::string>& dirName)
{
    DIR *dir = 0;

    if (dirName.size() != 2)
    {
        dir = opendir(".");
    }
    else
    {
        dir = opendir(dirName[1].c_str());
    }

    // struct
    dirent *entry;

    if (!dir)
    {
        perror("dirlist");
    }
    else
    {
        // struct dirent *readdir(DIR *dirp);
        while ( (entry = readdir(dir)) != NULL )
        {
            std::cout << "/" << entry->d_name << std::endl;
        }

        closedir(dir);
    }
}

void Dir::copyDir(const std::vector<std::string>& dirName)
{
    if (dirName.size() != 3)
    {
        std::cout << "Wrond input arguments.\n";
    }
    else
    {
        // destination path for copy folder
        NFTW::to = dirName[2];
        if (nftw(dirName[1].c_str(), NFTW::display_info, 20, FTW_CONTINUE) == -1)
	{
	    perror("copydir");
	}

        std::cout << dirName[1] << " : was copy succsessfully.\n";
    }
}

void Dir::moveDir(const std::vector<std::string>& dirName)
{
    if (dirName.size() != 3)
    {
        std::cout << "Wrond input arguments.\n";
    }
    else
    {
        // destination path for copy folder
        NFTW::to = dirName[2];
        if (nftw(dirName[1].c_str(), NFTW::display_info, 20, FTW_CONTINUE) == -1)
	{
	    perror("copydir");
	}

        Dir::removeDir(dirName);
        std::cout << dirName[1] << " : was moved succsessfully.\n";

    }
}
