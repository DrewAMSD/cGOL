#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

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
                Cell c;
                row.push_back(c);
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

    void printGrid() {
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
        //print rest of grid
        for (int i = 0; i < this->size; i++) {
            printDashes();
            std::cout << i+1 << (i+1 < 10 ? "  " : " ");
            for (int j = 0; j < this->size; j++) {
                std::cout << " | " << (grid[i][j].state ? "X" : " ");
            }
            std::cout << " |" << std::endl;
        }
        printDashes();
    }

    bool simOver() {
        for (int i = 0; i < this->size; i++) {
            for (int j = 0; j < this->size; j++) {
                if (grid[i][j].state) {
                    return false;
                } 
            }
        }

        return true;
    }

    int countNeighbors(int r, int c) {
        int count = 0;
        for (int i = r - 1; i <= r + 1; i++) {
        for (int j = c - 1; j <= c + 1; j++) {
            if ((i != r || j != c) && i < 15 && i >= 0 && j < 15 && j >= 0) {
            if (grid[i][j].state) {
                count = count + 1;
            }
            }
        }
        }
        return count;
    }

    void nextGen() {
        //find and put next gen into a bool array
        bool nextGen[this->size][this->size];
        for (int i = 0; i < this->size; i++) {
            for (int j = 0; j < this->size; j++) {
                nextGen[i][j] = grid[i][j].state;
                int count = countNeighbors(i, j);
                if (grid[i][j].state) {
                    //cell is alive and doesn't have num of neighbors to survive
                    if (count != 2 && count != 3) {
                        nextGen[i][j] = 0;
                    }
                } else {
                    //cell is dead and has 3 neighbors to become alive
                    if (count == 3) {
                        nextGen[i][j] = 1;
                    }
                }
            }
        }
        //update grid to next gen using bool array
        for (int i = 0; i < this->size; i++) {
            for (int j = 0; j < this->size; j++) {
                if (nextGen[i][j] != grid[i][j].state) {
                    grid[i][j].changeCellState();
                }
            }
        }
    }
};

void runGame(int allowedGens, Grid mainGrid) {
    std::cout << "run game" << std::endl;
    int gen = 1;
    while (gen < allowedGens) {
        //find next gen and print board
        mainGrid.nextGen();
        mainGrid.printGrid();
        
        //check if every cell is dead
        if (mainGrid.simOver()) {
            break;
        }
        gen++;
        sleep(1);
    }
    //if the game ended due to max allowed gens being played, let the player know
    if (gen >= allowedGens) {
        std::cout << "Simulation over, " << allowedGens << " generations passed" << std::endl;
    } else {
        std::cout << "Simulation over, all cells are dead" << std::endl;
    }
}

int main() {
    //create and init grid
    int sizeGrid = 15;
    Grid mainGrid;
    mainGrid.initGrid(sizeGrid);
    mainGrid.printGrid();

    //take in coordinates to set to alive before starting sim
    std::cout << "--enter coords('row col') of cell to change its state--" << std::endl;
    std::cout << "--input -1 in one of the coordinates to start simulation--" << std::endl;
    bool setCoords = true;
    while (setCoords) {
        int n, m;
        try {
            std::cout << "coords: ";
            std::cin >> n >> m;
            //check if start of sim or incorrect coord
            if (n > 15 || n < 1) {
                throw n;
            }
            if (m > 15 || m < 1) {
                throw m;
            }
            //change cell and print grid
            mainGrid.grid[n-1][m-1].changeCellState();
            mainGrid.printGrid();
        }
        catch (int coord) {
            if (coord == -1) {
                setCoords = false;
            } else {
                std::cout << "Error, incorrect coordinate: " << coord << std::endl;
            }
        }
    }

    //run simulation after setting up board
    runGame(100, mainGrid);

    return 0;
}