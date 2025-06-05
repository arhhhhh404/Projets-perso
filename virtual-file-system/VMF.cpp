#include <iostream>
#include <string>
#include <vector>
#include <memory>

struct File {
    std::string name;
    std::string content;

    File(const std::string& n) : name(n), content("") {};
};

struct Directory : std::enable_shared_from_this<Directory> {
    std::string name;
    std::vector < std::shared_ptr<File> > files;
    std::vector < std::shared_ptr<Directory> > subdirs;
    std::weak_ptr<Directory> parent;

    Directory(const std::string& m, std::shared_ptr<Directory> p = nullptr): name(m), parent(p) {};

    std::shared_ptr<Directory> getSubdir(const std::string& dirname) {
        for (auto& d : subdirs) {
            if (d->name == dirname)
            return d;
        }
        return nullptr;
    }

    std::shared_ptr<File> getFile(const std::string& filename) {
        for (auto& f : files) {
            if (f->name == filename)
                return f;
        }
        return nullptr;
    }

    void create_subdir(const std::string& dirname) {
        if (getSubdir(dirname) == nullptr) {
            subdirs.push_back(std::make_shared<Directory>(dirname, shared_from_this()));
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
    };
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

    void cd(const std::string& dirname) {
        if (dirname == "/") {
            current = root;
        } else if (dirname == "..") {
            if (auto parentDir = current->parent.lock()) {
                current = parentDir;
            } else {
                std::cout << "[!]: Already at root." << std::endl;
            }
        } else {
            auto next = current->getSubdir(dirname);
            if(next) {
                current = next;
            } else {
                std::cout << "[!]: Directory not found: " << dirname << std::endl;
            }
        }
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
        } else if(cmd == "cd") {
            std::cin >> arg;
            vfs.cd(arg);
        } else {
            std::cout << "[!]: Commande not found" << std::endl;
            std::getline(std::cin, arg);
        }
    }
    return 0;
}