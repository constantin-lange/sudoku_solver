#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

void print_sudoku(std::vector<std::vector<int>> sudoku){
	for(int i = 0; i < sudoku.size(); i++){
		for(int j = 0; j < sudoku.at(0).size(); j++){
			std::cout << sudoku.at(i).at(j) << " ";
		}
		std::cout << std::endl;
	}
}

bool is_threatened(std::vector<std::vector<int>> sudoku, int row, int column){
	for(int i = 0; i < sudoku.size(); i++){
		if(i != row && sudoku.at(i).at(column) == sudoku.at(row).at(column)){
			return true;
		}
	}
	for(int j = 0; j < sudoku.size(); j++){
		if(j != column && sudoku.at(row).at(j) == sudoku.at(row).at(column)){
			return true;
		}
	}
	int min_block_row = (row / 3) * 3;
	int max_block_row = min_block_row + 3;
	int min_block_column = (column / 3) * 3;
	int max_block_column = min_block_column + 3;
	for(int i = min_block_row; i < max_block_row; i++){
		for(int j = min_block_column; j < max_block_column; j++){
			if(i != row && j != column && sudoku.at(i).at(j) == sudoku.at(row).at(column)){
				return true;
			}
		}
	}
	return false;
}

bool is_finished(int row, int column){
	if(row == 8 && column == 8){
		return true;
	}
	return false;
}

void set_field(std::vector<std::vector<int>> sudoku, int row, int column){
	int new_column = (column + 1) % 9;
	int new_row = (column == 8) ? (row + 1) : row;
	if(sudoku.at(row).at(column) != 0){	
		set_field(sudoku, new_row, new_column);
	} else{
		for(int i = 1; i < 10; i++){
			sudoku.at(row).at(column) = i;
			if(!is_threatened(sudoku, row, column)){
				if(is_finished(row, column)){
					std::cout << "Solved: " << std::endl;
					print_sudoku(sudoku);
					exit(0);
				}
				else{
					set_field(sudoku, new_row, new_column);
				}
			}
			sudoku.at(row).at(column) = 0;
		}
	}
}

int main(int argc, char *argv[]){
   // convert sudoku text file to 2D int vector
   std::vector<std::vector<int>> sudoku;
   std::string line;
   std::ifstream sudoku_file("../test_sudoku.txt");
   char space_char = ' ';
   while(getline(sudoku_file,line))
    {
    	if(line == ""){
    		continue;
    		std::cout << "test" << std::endl;
    	}
      	line.erase(std::remove(line.begin(), line.end(), space_char), line.end());
      	std::vector<int> row;
      	for(int i = 0; i < line.length(); i++){
      		if(line.at(i) == 'X'){
      			row.push_back(0);
      		}
      		else{
      			row.push_back(line[i] - '0');
      		}

      	}    	
      	sudoku.push_back(row);
    }
    sudoku_file.close();

    // solve sudoku
    std::cout << "Unsolved: " << std::endl;
    print_sudoku(sudoku);
    std::cout << std::endl;

    set_field(sudoku, 0, 0);

   return 0;
}