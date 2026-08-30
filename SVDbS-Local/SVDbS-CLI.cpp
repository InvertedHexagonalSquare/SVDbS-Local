#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <print>
#include <vector>
#include <cstdlib>


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

//simple single-line editing of datasheets
void writeToFile(fs::path filePath) {
    std::ofstream writeFile(filePath, std::ios::app);
    std::string writeLine;

    if (!writeFile.is_open())
    {
        std::cerr << "could not create/open file" << std::endl;
        return;
    }
    
    std::cout << "Type in text here according to your database format (like CSV)" << std::endl;
    std::cin >> writeLine;
    writeFile << writeLine << std::endl;
}


std::vector<std::vector<std::string>> get_matrix_from_DB(const fs::path& setDbPath) {
    std::vector<std::vector<std::string>> matrix;
    std::ifstream dataset(setDbPath);
    std::string line;
    if (!dataset.is_open())
    {
        std::cerr << "Database not found or path invalid. Please reselect database or verify database directory" << std::endl;
        std::exit(1);
    }
    

    while (std::getline(dataset, line))
    {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ','))
        {
            row.push_back(cell);    
        }
        matrix.push_back(row);
    }
    dataset.close();
    return matrix;
}

void printMatrix(const std::vector<std::vector<std::string>>& matrix) {
    for (const auto& row : matrix)
    {
        for (const auto& cell : row)
        {
            std::cout << cell << " ";
        }
        std::cout << "\n";
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

    //initialize user defined variables
    std::string selectedDatabase;
    std::string enteredFilename;
    fs::path completedFilepath;
    fs::path completedDBPath;

    //debug messages
    std::cout << "dbpath: " << dbPath << std::endl;
    std::cout << "configPath: " << configPath << std::endl; 
    
    std::system("cls");
    std::cout << "Welcome to SVDbS" << std::endl;
    while (running)
    {
        std::cout << "> ";
        std::cin >> userInput;
        if (userInput == "lsdatabases")
        {
            std::cout << "Listing databases:" << std::endl;
            ls(fsdbPath);
            std::cout << "\n";
        }
        else if (userInput == "help" || userInput == "?")
        {
            std::cout << "Showing commands" << std::endl;
            std::cout << "help or ?\nexit\nlsdatabases\ncls or clear\nreadDB\nselectdb\neditdb" << std::endl;
            
        }
        else if (userInput == "cls" || userInput == "clear")
        {
            std::system("cls");
        }
        else if (userInput == "exit")
        {
            return 0;
        }
        else if (userInput == "selectdb")
        {
            std::cout << "Type the name of the database you want to use (including the proper file extensions)" << std::endl;
            std::cout << "Available Databases are: " << std::endl;
            ls(fsdbPath);
            std::cin >> selectedDatabase;
            std::cout << "Selected " << selectedDatabase << std::endl;
        }
        else if (userInput == "readdb")
        {
            completedDBPath = fsdbPath / selectedDatabase;
            auto data = get_matrix_from_DB(completedDBPath);
            printMatrix(data);
        }
        else if (userInput == "editdb")
        {
            std::cout << "Enter full name of file to be edited/created" << std::endl;
            std::cin >> enteredFilename;
            if (enteredFilename != "cancel")
            {
                completedFilepath = fsdbPath / enteredFilename;
                writeToFile(completedFilepath);
            }
            
        }
        else 
        {
            std::cout << userInput << " is not a valid command" << std::endl;
        }
    }
    return 0;
}