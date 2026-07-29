#include <string>
#include <iostream>
#include <array>
#include <vector>
#include <fstream>
#include "save_manager.h"


Save::Save(){};

bool isTextOnly(const std::string& string){
    for(unsigned int i=0; i<string.length(); i++){
        if(!isalnum(string[i]) && string[i] != ' '){
            return false;
        }
    }
    return true;
};

/*
Gets rid of spaces in file names
1 to replace space with delim
0 to replace delim with space
*/
void replaceSpaces(std::string& text, char delim, bool toDelim) {
    for (unsigned int i = 0; i < text.length(); i++) {
        if (toDelim) {
            if (text[i] == ' ') {
                text[i] = delim;
            }
        }
        else {
            if (text[i] == delim) {
                text[i] = ' ';
            }
        }
    }
}

void Save::saveToFile(const std::vector<std::vector<char>>& gameBoard, const int& rollNumber, const int& treasureFound, const std::vector<std::vector<char>>& treasureBoard){
    bool validInput = false;
    std::string inputValue;
    std::string fileName = _file_name;
    while (validInput == false){
        std::cout << "Please input save file name\n" << "ONLY USE LETTERS NUMBERS AND SPACES" << std::endl;
        std::getline(std::cin,inputValue);
        if (inputValue == ""){
            validInput = true;
        }else if (isTextOnly(inputValue)){
            fileName = inputValue;
            validInput = true;
        }
    }
    
    replaceSpaces(fileName,'_',1);
    saveFileNameCheck(_list_file_saves, fileName);

    fileName += ".txt";
    std::ofstream save_file(fileName);

    if (gameBoard.empty()) {
        std::cout << "Error: Game board data is empty" << std::endl;
        return;
    }
    if (treasureBoard.empty()){
        std::cout << "Error: Treasure board data is empty" << std::endl;
        return;
    }

    save_file << "Game Board";
    for (unsigned int i = 0; i < gameBoard.size(); i++){
        save_file << "\n";
        for (unsigned int j = 0; j < gameBoard[i].size(); j++){
            save_file << gameBoard[i][j] << " ";
        }
        
    }
    save_file << "\n";
    save_file << "Treasure Board";
    for (unsigned int i = 0; i < treasureBoard.size(); i++){
        save_file << "\n";
        for (unsigned int j = 0; j < treasureBoard[i].size(); j++){
            save_file << treasureBoard[i][j] << " ";
        }
        
    }
    save_file << "\n";
    save_file << "Roll Number: " << rollNumber << std::endl;
    save_file << "Treasure Found: " << treasureFound << std::endl;
    save_file.close(); 
    std::cout << "Game Saved" << "\033[?25l"; //Only shows for final thing
    
};


/*
Checks if the save name is already in the list, avoids dupes
First is the requested file name
Second is the string to check
DOES NOT NEED FILE FAILED TO FIND
*/
void Save::saveFileNameCheck(const std::string& fileName, const std::string& text) {
    std::ifstream inFile(fileName);
    std::string line;
    bool found = false;

    // Check if the string already exists
    while (getline(inFile, line)) {
        if (line == text) {
            found = true;
            break;
        }
    }

    inFile.close();

    // If not found, append it
    if (!found) {
        std::ofstream outFile(fileName, std::ios::app);

        outFile << text << std::endl;

        outFile.close();
    }
}



void Save::loadFromFile(){
    std::vector<std::string> saves;
    
    std::ifstream inFile(_list_file_saves);
    std::string line;

    if (!inFile.is_open()){
        std::cout << "No save file avaliable" << std::endl;
        return;
    }

    while (getline(inFile,line)){
        replaceSpaces(line,'_',0);
        saves.push_back(line);
    }

    inFile.close();

    std::cout << "List of Saves" << std::endl;
    for(unsigned int i=0; i<saves.size(); i++){
        std::cout << i+1 << ": " << saves[i] << std::endl;
    }

    //need to implement data handling and loading
};


