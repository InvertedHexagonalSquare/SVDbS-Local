#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <print>


namespace fs = std::filesystem;


bool running = true;
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
    //string path to filesystem path
    dbPath = readConfig("dbPath: ");
    fs::path fsdbPath(dbPath);
    
    std::cout << "Welcome to SVDbS" << std::endl;
    while (running)
    {
        std::cout << "> ";
        std::cin >> userInput;
        if (userInput == "databases")
        {
            std::cout << "Listing databases:" << std::endl;
            ls(fsdbPath);
        }
        else if (userInput == "help" || userInput == "?")
        {
            std::cout << "Showing commands" << std::endl;
        }
        
        
    }
    


    return 0;
}