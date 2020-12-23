#include <iostream>
#include <string>
using namespace std;
#define GRID_SIZE 3

class Game{
	private:
		char grid[GRID_SIZE][GRID_SIZE];

	public:
		// generate the X-O Grid from 0 to 8
		void generateGrid(){
			int index_counter = 0;
			for(int x = 0; x < GRID_SIZE; x++){
				for(int y = 0; y < GRID_SIZE; y++){
					// converts the int variable "index_counter" to a char
					char index_counter_char = to_string(index_counter).c_str()[0];
					grid[x][y] = index_counter_char;
					index_counter++;
				}
			}
		}

		// Will print the generated grid on the screen
		void printGrid(){
			// special characters which clears the screen before each print
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

			// checks for possible bad inputs
			if(player_move == "" || player_move_char < '0' || player_move_char > '8' || strlen(player_move.c_str()) > 1){
				cout << "Bad Input, please try again!" << endl;
			}
			else{
				// converts char to int
				int player_move_int = player_move_char - '0'; 	
				// locates the x,y coordiantes in my 2D array for the input move
				int player_move_x_coord = player_move_int / 3 ;
				int player_move_y_coord = player_move_int % 3;
				char choice = grid[player_move_x_coord][player_move_y_coord];
				// checks if the grind have an existing O value so that players don't
				// overwrite each other
				if(grid[player_move_x_coord][player_move_y_coord] != 'O'){
					grid[player_move_x_coord][player_move_y_coord] = 'X';
				}
				else{
					cout << "Please choose another move!" << endl;
					playerXTurn();
				}
				grid[player_move_x_coord][player_move_y_coord] = 'X';
			}
			
		}

		// same as playerXTurn
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
				if(grid[player_move_x_coord][player_move_y_coord] != 'X'){
					grid[player_move_x_coord][player_move_y_coord] = 'O';
				}
				else{
					cout << "Please choose another move!" << endl;
					playerOTurn();
				}
			}
			
		}

		// will check if any player has won and announce him then exit the game
		bool checkWins(){
			// array containing all possible winning moves
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

			// loop through the winning moves
			for(int i = 0; i < 8; i++){
				// assume we have a winner
				bool winner = true;

				// counter variable to track each turn
				char previous_turn = '0'; 

				// variable that traverses the array of strings
				const char* winning_moves = winning_moves_list[i];

				// loop through each single character in the winning moves sub array
				for( int move_index = 0; move_index < 3; move_index++){
					char winning_move = winning_moves[move_index];
					int winning_move_int = winning_move - '0';
					int winning_move_x_coord = winning_move_int / 3;
					int winning_move_y_coord = winning_move_int % 3;
					// this variable contains the value (X/O) of the winning move
					char winning_move_grid_value = grid[winning_move_x_coord][winning_move_y_coord];
					
					// if this is the first round, set the counter to our winning move value
					if(previous_turn == '0'){
						previous_turn = winning_move_grid_value;
					}
					// if this is not the first round, check if the last winning move value
					// is equal to the current winning move value where the winning move
					// is for example 0 in the first iteration, then 1 in the second iteration
					// then 2 in the third iteration.
					//
					// example: 
					// Round 1: we have an X at a winning move location: 0
					// Round 2: we have an X at the second winning move location: 1
					// Round 3: we have another X at the third winning move location: 2
					// Player Wins!
					//
					// (this process is done after each round)
					else if(previous_turn == winning_move_grid_value){
						continue;
					}
					// if nothing of the above mets, then we have a loser!
					else{
						winner = false;
						break;
					}
				}

				// will announce winner and exits if the winner flag is set to True
				if(winner){
					printGrid();
					cout << previous_turn << " Wins!" << endl;
					exit(0);
					break;

				}
			}

		}
		//
		// constructor which will contain the game loop
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

