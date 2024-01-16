#include <iostream>
#include <vector>

class Cell {
public:
    bool state = 0;

    void changeCellState() {
        this->state = this->state ? 0 : 1;
    }
};

class Grid {
public:
    int size;
    std::vector<std::vector<Cell> > grid;

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
        for (int i = 0; i < 5; i++) {
            std::cout << " ";
        }
        for (int i = 0; i < size*4; i++){
            std::cout << "-";
        }
        std::cout << std::endl;
    }

    void printBoard() {
        for (int i = 0; i < 6; i++) {
            std::cout << " ";
        }
        for (int i = 0; i < this->size; i++) {
            std::cout << i << "   ";
        }
        std::cout << std::endl;
        for (int i = 0; i < this->size; i++) {
            printDashes();
            std::cout << i << (i < 10 ? "  " : " ");
            for (int j = 0; j < this->size; j++) {
                std::cout << " | " << grid[i][j].state;
            }
            std::cout << " |" << std::endl;
        }
        printDashes();
    }
};

int main() {
    int n = 15;
    Grid grid;
    grid.initGrid(n);
    grid.printBoard();
    return 0;
}