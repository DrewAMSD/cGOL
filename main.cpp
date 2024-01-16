#include <iostream>
#include <vector>
#include <string>

class Cell {
public:
    //0 = dead, 1 = alive
    bool state = 0;

    void changeCellState() {
        this->state = this->state ? 0 : 1;
    }
};

class Grid {
public:
    int size;
    std::vector<std::vector<Cell> > grid;

    //init grid with dead cells
    void initGrid(int n) {
        this->size = n;
        for (int i = 0; i < n; i++) {
            std::vector<Cell> row;
            for (int j = 0; j < n; j++) {
                row.push_back(Cell());
            }
            grid.push_back(row);
        }
    }

    void printDashes() {
        std::cout << "-";
        for (int i = 0; i < 4; i++) {
            std::cout << " ";
        }
        for (int i = 1; i < size*4; i++){
            std::cout << "-";
        }
        std::cout << std::endl;
    }

    void printBoard() {
        //print columns indices
        std::cout << "G";
        for (int i = 0; i < 4; i++) {
            std::cout << " ";
        }
        for (int i = 1; i <= this->size; i++) {
            std::cout << "-"<< i << "-";
            if (i < 10) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
        //print rest of board
        for (int i = 1; i <= this->size; i++) {
            printDashes();
            std::cout << i << (i < 10 ? "  " : " ");
            for (int j = 0; j < this->size; j++) {
                std::cout << " | " << grid[i-1][j-1].state;
            }
            std::cout << " |" << std::endl;
        }
        printDashes();
    }
};

void runGame() {
    //runGame
}

int main() {
    //create and init grid
    int n = 15;
    Grid grid;
    grid.initGrid(n);
    grid.printBoard();

    //take in coordinates to set to alive before starting
    std::cout << "--enter coords('row col') of cell to change its state--" << std::endl;
    std::cout << "--input -1 -1 to start simulation--" << std::endl;
    bool setCoords = true;
    while (setCoords) {
        int n, m;
        try {
            std::cin >> n >> m;
            //check if start of simulation
            if (n == -1 && m == -1) {
                setCoords = false;
                break;
            }

        }
        catch (int coord) {
            std::cout << "Error, incorrect coordinate: " << coord << std::endl;
        }
    }
    std::cout << "start game";

    //run simulation after setting up board
    runGame();

    return 0;
}