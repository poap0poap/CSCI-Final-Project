#ifndef SAVE_MANAGER_H
#define SAVE_MANAGER_H

#include <string>
#include <array>

class Save{
private:
    //default filename
    const std::string _file_name = "save";
    const std::string _list_file_saves = "list-saves.txt";
    static constexpr int _DATA_ITEMS = 2; 
    static constexpr int _MAX_SIZE = 10;
    
public:
    Save();

    /*
    Save to file
    array first item
    roll next value
    */
    void saveToFile(const std::vector<std::vector<char>>& gameBoard, const int& rollNumber, const int& boardSize, const std::vector<std::vector<char>>& treasureBoard);

    //Load from file {does work, am not using at the moment}
    void loadFromFile();

    //Editiors
    void saveFileNameCheck(const std::string& fileName, const std::string& text);
};

#endif
