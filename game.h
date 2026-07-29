#ifndef GAME_H
#define GAME_H

#include <vector>
#include "save_manager.h"

class Game{
    private:
    static constexpr int _DATA_ITEMS = 2; 
    static constexpr int _PLAYER_STATS = 4;
        
    public:
    Game();
    void run();
};

class GameBoard{
    private:
        int rows;
        int cols;
        char _VAL = '+';
        std::vector<std::vector<char>> grid;
        std::vector<std::vector<char>> treasure;

    public:
        GameBoard(int r, int c) : rows(r), cols(c){
            grid.resize(r, std::vector<char>(c,'0'));
            treasure.resize(r, std::vector<char>(c,'0'));
        }

        bool checkTile(const int& r, const int& c){
            if(grid[r][c] == _VAL){
                return false;
            }
            else{return true;}
            return false;
        }

        void printBoard(){
            const std::string GREEN = "\033[48;5;106m";
            const std::string BROWN = "\033[48;5;130m";
            //headers
            std::cout << "   ";
            for (int i = 0; i < cols; i++){
                std::cout << i+1 << " ";
            }
            
            std::cout << std::endl << " ";
            for (int i = 0; i <= cols; i++){
                std::cout << "--";
            }
            std::cout << std::endl;



            for (int i=0;i<rows;i++){
                std::cout << (char)('A' + i) << "|"; // Print row number and a border
                std::cout << " ";
                for(int j = 0; j < cols; j++){
                    if(grid[i][j] == _VAL){
                        std::cout << BROWN << grid[i][j];
                    }
                    else{
                        std::cout << GREEN << grid[i][j];
                    }
                    std::cout << GREEN << " ";
                }
                std::cout << "\033[0m";
                std::cout << std::endl;
            }
            
        }
        
        void setTile(int r, int c){
            if (r >= 0 && r < rows && c >= 0 && c < cols){
                grid[r][c] = (char)(_VAL);
            }
        }

        //getting for grid
        const std::vector<std::vector<char>>& getGrid() const {
            return grid;
        }

        const std::vector<std::vector<char>>& getTreasure() const {
            return treasure;
        }

        //Checks if a tile is treasure
        bool isTreause(int r, int c){
            if(treasure[r][c] == 'T'){
                return true;
            }
            return false;
        }

        //Loads treasure to the treasure grid
        void loadTreaure(int boardSize){
            int treasureAmount;
            switch (boardSize)
            {
            case 6://small
                treasureAmount = 10;//number of treasure
                break;
            case 8://medioum
                treasureAmount = 16;
                break;
            case 10://large
                treasureAmount = 22;
                break;
            
            default:
                treasureAmount = 25;//Error should never appear
                break;
            }

            int spawned = 0;
            while(spawned < treasureAmount){
                // Pick two random numbers within the board size
                int r = rand() % boardSize;
                int c = rand() % boardSize;

                // Only place treasure if the tile is empty ('0')
                if (treasure[r][c] == '0') {
                    treasure[r][c] = 'T'; // 'T' for treasure
                    spawned++;
                }
            }
        }
        
};

#endif
