#include <cstring>
#include <iostream>
#include <string>
using namespace std;
#define GRID_SIZE 3

class Game{
	public:
		char grid[GRID_SIZE][GRID_SIZE];
		int index_counter = 0;

		void generateGrid(){
			for(int x = 0; x < GRID_SIZE; x++){
				for(int y = 0; y < GRID_SIZE; y++){
					char index_counter_char = to_string(index_counter).c_str()[0];
					grid[x][y] = index_counter_char;
					index_counter++;
				}
			}
		}

		void printGrid(){
			cout << "\033[2J\033[1;1H";
			for(int x = 0; x < GRID_SIZE; x++){
				for(int y = 0; y < GRID_SIZE; y++){
					printf(" %c |", grid[x][y]);
				}
				cout << endl;
			}
		}

		void playerXTurn(){
			string player_move;
			cout << "Player X turn: ";

			getline(cin, player_move);
			char player_move_char = player_move.c_str()[0];

			if(player_move == "" || player_move_char < '0' || player_move_char > '8' || strlen(player_move.c_str()) > 1){
				cout << "Bad Input, please try again!" << endl;
			}
			else{
				int player_move_int = player_move_char - '0';
				int player_move_x_coord = player_move_int / 3 ;
				int player_move_y_coord = player_move_int % 3;
				char choice = grid[player_move_x_coord][player_move_y_coord];
				grid[player_move_x_coord][player_move_y_coord] = 'X';
			}
			
		}

		void playerOTurn(){
			string player_move;
			cout << "Player O turn: " ;

			getline(cin, player_move);
			char player_move_char = player_move.c_str()[0];

			if(player_move == "" || player_move_char < '0' || player_move_char > '8' || strlen(player_move.c_str()) > 1){
				cout << "Bad Input, please try again!" << endl;
			}
			else{
				int player_move_int = player_move_char - '0';
				int player_move_x_coord = player_move_int / 3 ;
				int player_move_y_coord = player_move_int % 3;
				char choice = grid[player_move_x_coord][player_move_y_coord];
				grid[player_move_x_coord][player_move_y_coord] = 'O';
			}
			
		}

		bool checkWins(){
			const char* winning_moves_list[8] = {
				"012",
				"345",
				"678",
				"036",
				"147",
				"258",
				"048",
				"246"
			};
			for(int i = 0; i < 8; i++){
				bool winner = true;
				char previous_turn = '0'; 
				const char* winning_moves = winning_moves_list[i];
				for( int move_index = 0; move_index < 3; move_index++){
					char winning_move = winning_moves[move_index];
					int winning_move_int = winning_move - '0';
					int winning_move_x_coord = winning_move_int / 3;
					int winning_move_y_coord = winning_move_int % 3;
					char winning_move_grid_value = grid[winning_move_x_coord][winning_move_y_coord];
					
					if(previous_turn == '0'){
						previous_turn = winning_move_grid_value;
					}
					else if(previous_turn == winning_move_grid_value){
						continue;
					}
					else{
						winner = false;
						break;
					}
				}

				if(winner){
					printGrid();
					cout << previous_turn << " Wins!" << endl;
					exit(0);
					break;

				}
			}

		}
		Game(){
			generateGrid();
			while(true){
				printGrid();
				playerXTurn();
				checkWins();
				printGrid();
				playerOTurn();
				checkWins();
			}

		}

};

int main(){
	Game game;
	return 0;
}

