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

bool Dir::createDir(const std::string &path)
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
    if (mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
    {
        // Interprets the value of errno as an error message
        perror("createdir");
        return false;
    }
    else
    {
        std::cout << "File was successfully created!\n";
        return true;
    }
}

bool Dir::removeDir(const std::string &path)
{
    // nftw() walks through the directory tree that is located under the directory dirpath,
    // and calls deleteDirTree() once for each entry in the tree

        if (nftw(path.c_str(), NFTW::deleteDirTree, 20, FTW_DEPTH) != 0)
        {
            perror("removedir");
            return false;
        }
        else
        {
            std::cout << "directory was deleted succsessfully.\n";
            return true;
        }
}

void Dir::currentPath()
{
    char buf[1024];

    /*
     * char *getcwd(char *buf, size_t size);
     * @return buf
     */
    if (getcwd(buf, sizeof(buf)) == NULL)
    {
        std::cout << "Error: can't display current directory.";
    }
    else
    {
        std::cout << buf;
    }
}

bool Dir::changeDir(const std::string &path)
{
    /*
     * int chdir(const char *path);
     */
    if (chdir(path.c_str()) == -1)
    {
        perror("changedir");
        return false;
    }
    else
    {
        return true;
    }
}

void Dir::dirList(const std::string &path)
{
    DIR *dir = 0;

    dir = opendir(path.c_str());

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

bool Dir::copyDir(const std::string &path, const std::string &destPath)
{
    // destination path for copy folder
    NFTW::to = destPath;

    if (nftw(path.c_str(), NFTW::display_info, 20, FTW_CONTINUE) == -1)
    {
        perror("copydir");
        return false;
    }

    std::cout << path << " : was copy succsessfully.\n";
    return true;
}

bool Dir::moveDir(const std::string &path, const std::string &destPath)
{
    // destination path for copy folder
    NFTW::to = destPath;
    if (nftw(path.c_str(), NFTW::display_info, 20, FTW_CONTINUE) == -1)
    {
        perror("copydir");
        return false;
    }

    Dir::removeDir(path);
    std::cout << path << " : was moved succsessfully.\n";
    return true;
}

void Dir::dirInfo(const std::string &path)
{
    struct stat sb;

    if (stat(path.c_str(), &sb) == -1)
    {
        perror("dirinfo");
    }
    else if ((sb.st_mode & S_IFMT) == S_IFDIR) {
        std::cout << "File type: Directory\n";
        std::cout << "File size: " << (long long) sb.st_size << " bytes" << std::endl;
        std::cout << "Last status change: " << ctime(&sb.st_ctime);
        std::cout << "Last file access: " << ctime(&sb.st_atime);
        std::cout << "Last file modification: " << ctime(&sb.st_mtime);
    }
    else
    {
        std::cout << "Error: It is not a directory.\n";
    }

}

bool Dir::createPath(const std::string &fullPath)
{
    std::string path = fullPath;
    std::string delimiter = "/";

    // path.find() return the pos delimeter if endofline then return npos string
    size_t pos = 0;
    std::string token;
    while ((pos = path.find(delimiter)) != std::string::npos) {

        if (pos == 0)
        {
            path.erase(0, 1);
        }
        else
        {
            token = path.substr(0, pos);
            Dir::createDir(token);
            Dir::changeDir(token);
            path.erase(0, pos + delimiter.length());
        }
    }
    Dir::createDir(path);
    Dir::changeDir(path);

    return true;
}

bool Dir::renameDir(const std::string &path, const std::string &destPath)
{
    if (!(rename(path.c_str(), destPath.c_str())))
    {
        std::cout << "Dir renamed." << std::endl;
        return true;
    }
    else
    {
        perror("rename");
        return false;
    }
}
