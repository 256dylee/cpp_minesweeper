#include <iostream>
#include <ctime>
#include <array>
using namespace std;

const int boardLen{ 3 };
int bombProb{ 20 };
enum class Status { CONTINUE, WON, LOST };

Status gameStep(array <array <int, boardLen>, boardLen>&, const array<int, 2>&);
void printBoard(const array <array <int, boardLen>, boardLen>&);
void printAllBomb(const array <array <int, boardLen>, boardLen>& board);
int getBombCount(int row, int col, array<array<int, boardLen>, boardLen>& board);
void printBombToCharB(const array <array <int, boardLen>, boardLen>& board, const array<int, 2>& move);

int main()
{
	// TO-DO
	// You must implement main function!
	// You can use below template codes, but you have to design the overall algorithm and implement the C++ code yourself.
	array <array <int, boardLen>, boardLen> board{};

	srand(static_cast<unsigned int>(time(0)));

	// √ ±‚»≠ : -1
	for (int i{ 0 }; i < boardLen; i++) {
		for (int j{ 0 }; j < boardLen; j++) {
			board[i][j] = -1;
		}
	}

	int bombAmount{ 0 };

	for (int i{ 0 }; i < boardLen; i++) {
		for (int j{ 0 }; j < boardLen; j++) {
			if ((rand() % 100) < bombProb) {
				board[i][j] = -2;
				bombAmount = bombAmount + 1;
			}
		}
	}
	printBoard(board);

	int row;
	int col;
	Status status;
	array <int, 2> oneDim{};


	int playCount{ 0 };

	while (true) {
		while (true)
		{
			cout << "Enter the row number of your next move: ";
			cin >> row;
			cout << "Enter the column number of your next move: ";
			cin >> col;
			if ((row >= boardLen) || (row < 0) || (col >= boardLen) || (col < 0)) {
				cout << "Please enter correct row/column!" << endl;
				continue;
			}
			if ((board[row][col] != -1) && (board[row][col] != -2)) {
				cout << "Please enter the valid move!" << endl;
				continue;
			}
			else {
				break;
			}
		}

		oneDim[0] = row;
		oneDim[1] = col;
		status = gameStep(board, oneDim);
		if (status == Status::CONTINUE) {
			playCount = playCount + 1;
			if (playCount + bombAmount == boardLen * boardLen) {
				status = Status::WON;

				printAllBomb(board);
				cout << "Congratulations! You won.";
				break;
			}
			printBoard(board);
			continue;
		}
		else if(status == Status::LOST) {
			if (board[row][col] == -2) {
				printBombToCharB(board, oneDim);
			}
			cout << endl;
			cout << "BOOM! You lost.";
			break;
		}
	}
}

	Status gameStep(array <array <int, boardLen>, boardLen>& board, const array<int, 2>& move) {
		int row = move[0];
		int col = move[1];
		Status status;
		int bombNum{0};
		

		if (board[row][col] == -2) {
			status = Status::LOST;
		}
		else if(board[row][col] == -1) {
			status = Status::CONTINUE;
			bombNum = getBombCount(row, col, board);
			board[row][col] = bombNum;
		}
		else  {
		status = Status::WON;
		}

		return status;
}

void printAllBomb(const array <array <int, boardLen>, boardLen>& board) {
	// TO-DO
	// You must implement printAllBomb function!
	cout << "    ";
	for (int i{ 0 }; i < boardLen; i++) {
		cout << i << " ";
	}
	cout << "\n   ";
	for (int i{ 0 }; i < boardLen; i++) {
		cout << "__";
	}
	cout << endl;
	for (int i{ 0 }; i < boardLen; i++) {
		cout << i << " | ";
		for (int j{ 0 }; j < boardLen; j++) {
			if (board[i][j] == -2) {
				cout << "B ";
			}
			else if (board[i][j] == -1) {
				cout << ". ";
			}
			else {
				cout << board[i][j] << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

void printBoard(const array <array <int, boardLen>, boardLen>& board) {
	// Caution!
	// Do not edit the printBoard function!
	cout << "    ";
	for (int i{ 0 }; i < boardLen; i++) {
		cout << i << " ";
	}
	cout << "\n   ";
	for (int i{ 0 }; i < boardLen; i++) {
		cout << "__";
	}
	cout << endl;
	for (int i{ 0 }; i < boardLen; i++) {
		cout << i << " | ";
		for (int j{ 0 }; j < boardLen; j++) {
			if (board[i][j] == -2) {
				cout << ". ";
			}
			else if (board[i][j] == -1) {
				cout << ". ";
			}
			else {
				cout << board[i][j] << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

void printBombToCharB(const array <array <int, boardLen>, boardLen>& board, const array<int, 2>& move) {
	
	int row = move[0];
	int col = move[1];
	cout << "    ";
	for (int i{ 0 }; i < boardLen; i++) {
		cout << i << " ";
	}
	cout << "\n   ";
	for (int i{ 0 }; i < boardLen; i++) {
		cout << "__";
	}
	cout << endl;
	for (int i{ 0 }; i < boardLen; i++) {
		cout << i << " | ";
		for (int j{ 0 }; j < boardLen; j++) {
			if (board[i][j] == -2) {
				if (i == row && j == col) {
					cout << "B ";
				}
				else {
					cout << ". ";
				}
			}
			else if (board[i][j] == -1) {
				cout << ". ";
			}
			else {
				cout << board[i][j] << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}
			


int getBombCount(int row, int col, array<array<int, boardLen>, boardLen>& board) {
	int bombCount = 0;
	
	array<array<int, 2>, 8> find {
		{//{row,col}
		{0,-1},
		{-1,-1},
		{-1,0},
		{-1,1},
		{0,1},
		{1,1},
		{1,0},
		{1,-1}
		}
	};

	for (int i{ 0 }; i < find.size(); i++) {
		int rowChange = row + find[i][0];
		int colChange = col + find[i][1];
		
		if ((rowChange >= 0) && (rowChange <= 2)) {
			if ((colChange >= 0) && (colChange <= 2)) {
				if (board[rowChange][colChange] == -2) {
					bombCount = bombCount + 1;
				}
			}
		}
	}
	
	return bombCount;
}