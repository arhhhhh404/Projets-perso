#include <iostream>
#include <string>
#include <vector>
#include <memory>

struct File {
    std::string name;
    std::string content;

    File(const std::string& n) : name(n), content("") {};
};

struct Directory {
    std::string name;
    std::vector < std::shared_ptr<File> > files;
    std::vector < std::shared_ptr<Directory> > subdirs;

    Directory(const std::string& m): name(m) {};

    std::shared_ptr<Directory> getSubdir(const std::string& dirname) {
        for (auto& d : subdirs) {
            if (d->name == dirname)
            return d;
        }
        return nullptr;
    }

    std::shared_ptr<File> getFile(const std::string& filename) {
        for (auto& f : files) {
            if (f->name == filename);
            return f;
        }
        return nullptr;
    }

    void create_subdir(const std::string& dirname) {
        if (getSubdir(dirname) == nullptr) {
            subdirs.push_back(std::make_shared<Directory>(dirname));
            std::cout << "[+]: Dir : " << dirname << " created." << std::endl;
        }
        else {
            std::cout << "[!]: Existing dir." << std::endl;
        }

    };

    void create_file(const std::string& filename) {
        if (getFile(filename) == nullptr) {
            files.push_back(std::make_shared<File>(filename));
            std::cout << "[+]: File : " << filename << " created." << std::endl;
        }
        else {
            std::cout << "[!]: Existing File." << std::endl;
        }
    };

    void list () {
        std::cout << "[?]: Content of " << name << " : " << std::endl;
        for (auto& d : subdirs) {
            std::cout << "(D): " << d->name << std::endl;
        }
        for (auto& f : files) {
            std::cout << "(F): " << f->name << std::endl;
        }
    }
};

class VFS {
    std::shared_ptr<Directory> root;
    std::shared_ptr<Directory> current;

    public:
    VFS() {
        root = std::make_shared<Directory>("root");
        current = root;
    }

    void mkdir(const std::string& dirname) {
        current -> create_subdir(dirname);
    }

    void touch(const std::string& filename) {
        current -> create_file(filename);
    }
    
    void ls() {
        current -> list();
    }
};

int main() {
    VFS vfs;
    std::string cmd;
    std::string arg;

    std::cout << "============| VIRTUAL FILES SYSTEM |============" << std::endl;

    while(true) {
        std::cout << "> ";
        std::cin >> cmd;

        if(cmd == "exit") {
            std::cout << "Goodbye!" << std::endl;
            break;
        } else if(cmd == "ls") {
            vfs.ls();
        } else if(cmd == "mkdir") {
            std::cin >> arg;
            vfs.mkdir(arg);
        } else if(cmd == "touch") {
            std::cin >> arg;
            vfs.touch(arg);
        } else {
            std::cout << "[!]: Commande not found" << std::endl;
            std::getline(std::cin, arg);
        }
    }

    return 0;
}