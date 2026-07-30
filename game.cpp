//the rules for a file with main() were confusing so this is basically main.cpp but I didnt want to bother with main being mainy.
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <array>
#include <string>
#include <ctime>
#include <cstdlib>
//files
#include "game.h"
#include "save_manager.h"
#include "playerInfo.h"
#include "utility.h"

//For displaying menu and easier updating what can be done
void menuDisplay(){
    std::cout << "1. Roll" << std::endl;
    std::cout << "2. Bounty" << std::endl;
    std::cout << "3. Save" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "5. List Saves" << std::endl;
}


//rolling dice. any size - determned by int value
int diceRoll(int diceSize){
    return 1 + rand() % diceSize;
}

//Returns a number based on the difficulty chosen
int Difficulty(){
    //Board Size
    const int SM = 6;
    const int MD = 8;
    const int LG = 10;

    bool validInput = false;
    while (!validInput){ //Chose Size of board
        std::cout<<"What size would you like to play?\nSmall, Medium, or Large\n";
        std::string difficulty;
        std::getline(std::cin,difficulty);
        if (difficulty == "Small"){
            validInput = true;
            return SM;
            break;
        }else if (difficulty == "Medium"){
            validInput = true;
            return MD;
            break;
        }else if (difficulty == "Large"){
            validInput = true;
            return LG;
            break;
        }
        clearScreen();
        std::cout << "Invalid Size\n";
    }
    std::cout << "error in Size";
    return 0;
}

bool coordCheck(std::string& input, const int& boardSize, std::array<int,2>& outCoords){
    //Is right size
    if (input.length() < 2 || input.length() > 3){
        return false;
    }

    //Is col a letter
    char colChar = std::toupper(input[0]);
    if (!std::isalpha(colChar)) {
        return false;
    }
    int colIndex = colChar - 'A'; //colIndex is the col value

    //is row number
    std::string rowPart = input.substr(1);
    for (char c : rowPart) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    
    int rowNum = std::stoi(rowPart);
    int rowIndex = rowNum - 1; 

    char maxColChar = 'A' + (boardSize - 1);
    if (colChar < 'A' || colChar > maxColChar) {
        return false;
    }
    
    if (rowIndex < 0 || rowIndex >= boardSize) {
        return false;
    }

    outCoords[0] = colIndex;
    outCoords[1] = rowIndex;
    return true;
}

int Rolls(int boardSize,int& diceSize){
    switch (boardSize)
    {
    case 6:
        diceSize = 3;
        return 11;//number of rolls for Small Board
        break;
    case 8:
        diceSize = 4;
        return 15;//number of rolls for Medium Board
        break;
    case 10:
        diceSize = 5;
        return 19;//number of rolls for Large Board
        break;
    
    default:
        return 0;//Error should never appear
        break;
    }
}

Game::Game(){};

void Game::run(){
    srand(time(0)); //seeds rng

    Save Save{};


    int diceSize; //change dice size

    //Variables
    int treasureFound = 0;
    int rollNumber = 0;
    int roll,input; //Roll - the value of the dice roll Input - user input
    std::string remove,diceCoordinate;
    bool running = true; //Used for running game loop
    bool waiting = true; //Used for while loops where checks are needed
    bool rollWaiting = false; //Used for dice rolls.

    clearScreen();
    //Gameboard Initilize
    int boardSize = Difficulty();
    int maxRolls = Rolls(boardSize,diceSize);
    
    //std::cout << boardSize << std::endl;
    clearScreen();

    //Board loading
    GameBoard Board(boardSize, boardSize);
    Board.loadTreaure(boardSize);

    int line = boardSize + 3; //for clearing below board so less refresing
    

    Board.printBoard();
    while (running){
        waiting = true;
        std::cout << "\n";
        menuDisplay();
        while (waiting){
            std::cin >> input;
            std::cin.clear();//was having issues with lingering invalid inputs
            std::getline(std::cin, remove);//clearing all \n from input

            //checks for if only number inputed
            switch (input)
            {
            case 1: //Roll
                clearBelowLine(line);
                roll = diceRoll(diceSize);
                rollNumber++;
                //std::cout << roll;
                waiting = false;
                rollWaiting = true;
                break;
            case 2: //Stats
                clearBelowLine(line);
                std::cout << "Total Treasure: " << treasureFound << std::endl;
                menuDisplay();
                break;
            case 3: //Save
                clearBelowLine(line);
                Save.saveToFile(Board.getGrid(),rollNumber,treasureFound,Board.getTreasure());
                clearBelowLine(line);
                std::cout<<std::endl;
                menuDisplay();
                break;
            case 4: //Quit
                clearBelowLine(line);
                waiting = false;
                running = false;
                break;
            case 5: //Read from file
                clearBelowLine(line);
                std::cout << "\n";
                menuDisplay();
                std::cout << "\n";
                Save.loadFromFile();
                break;
            default:
                clearBelowLine(line);
                std::cout << "Invalid Input" << std::endl;
                menuDisplay();
                break;
            }
        }
        //Gameplay loop
        while (rollWaiting){
            //Only runs as many times as you rolled
            for(int i=roll;i>0;i--){    
                waiting = true;
                std::array<int,2> Coord;
                while (waiting){
                    std::cout << "\nChoices Remaing: " << i << std::endl;
                    std::cout << "\nSelect Cooridinate to search" << std::endl;
                    std::getline(std::cin,diceCoordinate);
                    if (coordCheck(diceCoordinate, boardSize, Coord)){
                        if (Board.checkTile(Coord[0],Coord[1])){
                            Board.setTile(Coord[0],Coord[1]);
                            clearScreen();
                            Board.printBoard();
                            if(Board.isTreause(Coord[0],Coord[1])){
                                treasureFound++;
                                std::cout << "Treasure Found";
                                std::cout << '\a';
                            }
                            waiting = false;
                        }
                        else{
                            clearBelowLine(line);
                            std::cout << "Error Invalid Coordinate";
                        }
                    }   
                    else{
                        clearBelowLine(line);
                        std::cout << "Error Invalid Coordinate";
                    }

                }
            }
            rollWaiting = false;
        }

        //End of game
        if(rollNumber==maxRolls){
            while(running){
                std::string doSave;
                clearBelowLine(line);
                std::cout<<"\nWell Done on this Expidition" << std::endl;
                std::cout<<"Total Treasure Uncovererd is " << treasureFound << std::endl; 
                std::cout<<"Would You Like to Save this Game?" << "\n" << "y or n" << "\033[?25h" << std::endl;
                std::getline(std::cin, doSave);
                if(doSave == "y"){
                    clearBelowLine(12);
                    std::cout<<"\n";
                    Save.saveToFile(Board.getGrid(),rollNumber,treasureFound,Board.getTreasure());
                    running = false;
                }
                else if(doSave == "n"){
                    running = false;
                }
            }
            
        }

    }
    std::cin.get();//keeps terminal until another enter
}
