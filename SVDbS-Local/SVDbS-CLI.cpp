#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <print>

namespace fs = std::filesystem;

fs::path dbPath;
fs::path cwd = fs::current_path();
fs::path configPath = cwd / "SVDbS-Local" / "Config" / "Config.txt";
std::string userInput;

void ls(fs::path path) {
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        std::cout << entry.path().filename().string();
    }
}

void readConfig(std::string configKeyword) {
    std::ifstream configFetch(configPath);
    std::string currentline;
    if (!configFetch.is_open())
    {
        std::cerr << "Error fetching Config File, verify Config.txt directory";
    }
    while (std::getline(configFetch, currentline))
    {
        size_t pos = currentline.find(configKeyword);
        if (currentline.find(configKeyword) != std::string::npos)
        {
            
        }
        
    }
    configFetch.close();    
}

int main() {
    std::cout << "Welcome to SVDbS" << std::endl;
    while (true)
    {
        
    }
    return 0;
}