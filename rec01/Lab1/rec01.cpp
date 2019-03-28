//
//  rec01.cpp
//  Lab1
//  Conways Game of Life
//
//  Created by Helal Chowdhury on 2/1/19.
//  Copyright © 2019 Helal Chowdhury. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

//  Checks if the boxes are inside the grid
bool valid(vector<string>& grid, int row, int col){
    if (row > grid.size() || col > grid[1].size()){
        return false;
    }
    else{
        return true;
    }
}

//  Creates a new grid with the next generation
void newGeneration(vector<string>& grid, vector<string>& newGrid, int row, int col){
        for(int r = 0; r < row; ++r) {
            for(int c = 0; c < col; ++c) {
                int neighbors = 0;
                if(valid(grid, r-1, c-1) == true && grid[r-1][c-1] == '*'){
                    neighbors ++;
                }
                if(valid(grid, r-1, c) == true && grid[r-1][c] == '*'){
                    neighbors ++;
                }
                if(valid(grid, r-1, c+1) == true && grid[r-1][c+1] == '*'){
                    neighbors ++;
                }
                if(valid(grid, r, c+1) == true && grid[r][c+1] == '*'){
                    neighbors ++;
                }
                if(valid(grid, r+1, c+1) == true && grid[r+1][c+1] == '*'){
                    neighbors ++;
                }
                if(valid(grid, r+1, c) == true && grid[r+1][c] == '*'){
                    neighbors ++;
                }
                if(valid(grid, r+1, c-1) == true && grid[r+1][c-1] == '*'){
                    neighbors ++;
                }
                if(valid(grid, r, c-1) == true && grid[r][c-1] == '*'){
                    neighbors ++;
                }
                if (grid[r][c] == '*'){
                    if(neighbors < 2 || neighbors > 3) {
                        newGrid[r][c] = '-';
                    }
                    else{
                        newGrid[r][c] = '*';
                    }
                }
                else{
                    if(neighbors == 3){
                        newGrid[r][c] = '*';
                    }
                    else{
                        newGrid[r][c] = '-';
                    }
                }
            }
        }
}

// Creates the first initial world and calls to print the next 10 generations
int main(){
    ifstream life("life.txt");
    int row = 0;
    int col = 0;
    vector<string> grid;
    vector<string> newGrid;
    string line;
    
    while(getline(life, line)) {
        row ++;
        grid.push_back(line);
    }
    col = grid[1].size();
    
    cout << "Initial World" << endl;
    for(size_t i = 0; i < grid.size(); i ++) {
        cout << grid[i] << endl;
    }
    newGrid = grid;
    for(int generations = 1; generations < 11; generations++){
        newGeneration(grid, newGrid, row, col);
        cout << "Generation: " << generations << endl;
        for(size_t i = 0; i < newGrid.size(); i ++) {
             cout << newGrid[i] << endl;
        }
        cout << endl;
        grid = newGrid;
    }
}
