#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <print>
#include <optional>

namespace fs = std::filesystem;

fs::path dbPath;
fs::path cwd = fs::current_path();
fs::path configPath = cwd / "Config" / "Config.txt";
std::string userInput;

void ls(fs::path path) {
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        std::cout << entry.path().filename().string() << std::endl;
    }
}



// Note that you will need to pass a path string through 
// a filesystem constructor for correct handling with the ls() function
std::string readConfig(std::string configKeyword) {
    std::ifstream configFetch(configPath);
    std::string currentline;
    std::string result;
    if (!configFetch.is_open())
    {
        std::cerr << "Error fetching Config File, verify Config.txt directory";
    }
    while (std::getline(configFetch, currentline))
    {
        size_t pos = currentline.find(configKeyword);
        if (currentline.find(configKeyword) != std::string::npos)
        {
            configFetch.close();
            result = currentline.substr(pos + configKeyword.length());
            return result;
        }

    }
    configFetch.close();
    return "notfound";
}

int main() {
    std::cout << "Welcome to SVDbS" << std::endl;
    std::cout << readConfig("Lang: ") << std::endl;
    std::cout << readConfig("dbPath: ") << std::endl;
    dbPath = readConfig("dbPath: ");
    fs::path fsdbPath(dbPath);
    ls(fsdbPath);
    return 0;
}