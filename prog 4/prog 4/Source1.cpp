#include "Head.h"
#include "Windows.h"
#include "ctime"
#include <iostream>
#include <vector>
using namespace std;

Game initGame(char userChar)
{
	Game game;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			game.board[i][j] = ' ';
		}
	}
	srand(time(NULL));
	game.isUserTurn = rand() % 2;
	game.userChar = userChar;
	if ((game.userChar == '0') && (game.userChar == 'o')) 
	{
		game.botChar = 'X';
	}
	else 
	{ 
		game.botChar = '0'; 
	}
	game.status = PLAY;
	return game;
}

void updateDisplay(const Game game)
{
	system("cls");
	cout << "_______________" << endl;
	cout << "  | a | b | c |" << endl;
	cout << "_______________" << endl;
	for (size_t i = 0; i < 3; i++)
	{
		cout << i + 1 << " | " << game.board[i][0] << " | " << game.board[i][1] << " | " << game.board[i][2] << " | " << endl;
		cout << "_______________" << endl;
	}
}
void botTurn(Game* game)
{
	int max = -1, counter = 0;
	bool check = true;
	int User_Arr[8] = {};
	int Bot_Arr[8] = {};
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (game->board[i][j] == game->userChar)
			{
				User_Arr[i]++;
				User_Arr[j + 3]++;
			}
			else if (game->board[i][j] == game->botChar)
			{
				Bot_Arr[i]++;
				Bot_Arr[j + 3]++;
			}
			if (i == j && game->board[i][j] == game->userChar)
			{
				User_Arr[6]++;
			}
			else if (i == j && game->board[i][j] == game->botChar)
			{
				Bot_Arr[6]++;
			}
			if ((i + j) == 2 && game->board[i][j] == game->userChar)
			{
				User_Arr[7]++;
			}
			else if ((i + j) == 2 && game->board[i][j] == game->botChar)
			{
				Bot_Arr[7]++;
			}
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (max == User_Arr[i] && (User_Arr[i] + Bot_Arr[i]) < 3)
		{
			counter++;
		}
		else if ((User_Arr[i] + Bot_Arr[i]) == 3)
		{
			User_Arr[i] = -2;
		}
		if (User_Arr[i] > max && (User_Arr[i] + Bot_Arr[i]) < 3)
		{
			max = User_Arr[i];
			counter = 1;
		}
		else if ((User_Arr[i] + Bot_Arr[i]) == 3)
		{
			User_Arr[i] = -2;
		}

	}
	int temp = rand() % counter;

	counter = 0;
	if (max > 0)
	{
		for (int i = 0; i < 8; i++)
		{
			if (max == User_Arr[i])
			{
				if (counter == temp)
				{
					if (i < 3)
					{
						for (size_t j = 0; j < 3; j++)
						{
							if (game->board[i][j] == ' ')
							{
								game->board[i][j] = game->botChar;
								check = false;
								break;
							}
						}
					}
					if (i > 2 && i < 6)
					{
						for (int j = 0; j < 3; j++)
						{
							if (game->board[j][i - 3] == ' ')
							{
								game->board[j][i - 3] = game->botChar;
								check = false;
								break;
							}
						}
					}
					if (i == 6)
					{
						for (int j = 0; j < 3; j++)
						{
							if (game->board[j][j] == ' ')
							{
								game->board[j][j] = game->botChar;
								check = false;
								break;
							}
						}
					}
					if (i == 7)
					{
						int c = 2;
						for (int j = 0; j < 3; j++)
						{

							if (game->board[c - j][j] == ' ')
							{
								game->board[c - j][j] = game->botChar;
								check = false;
								break;
							}
						}
					}
				}
				counter++;
				if (!check)
				{
					break;
				}
			}
		}
	}
	if (max == 0)
	{
		game->board[1][1] = game->botChar;
	}
}

    void userTurn(Game* game)
	{
		int x, y;
		char y_character, x_character;
		bool check = false;
		do
		{
			check = false;
			cin >> x_character;
			cin >> y_character;
			switch (y_character)
			{
			case 'a':
				y = 0;
				break;
			case'b':
				y = 1;
				break;
			case'c':
				y = 2;
				break;
			default:
				cout << "Error!" << endl;
				check = true;
				break;
			}
			if (check)
			{
				continue;
			}
			switch (x_character)
			{
			case '1':
				x = 0;
				break;
			case'2':
				x = 1;
				break;
			case'3':
				x = 2;
				break;
			default:
				cout << "Error!" << endl;
				check = true;
				break;
			}
			if (check)
			{
				continue;
			}
			if (game->board[x][y] == ' ')
			{
				game->board[x][y] = game->userChar;
				check = false;

			}
			else
			{
				cout << "Error!" << endl;
				check = true;
			}
		} while (check);
	}

	bool updateGame(Game* game)
	{
		bool turn = true;
		int Bot_Arr[8] = {};
		int User_Arr[8] = {};
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (game->board[i][j] == ' ')
				{
					turn = false;
					continue;
				}
				game->board[i][j] == game->userChar ? User_Arr[i]++ : Bot_Arr[i]++;
				if (game->board[j][i] == game->userChar)
				{
					User_Arr[j + 3]++;
				}
				else if (game->board[j][i] == '0')
				{
					Bot_Arr[j + 3]++;
				}

				if (i == j)
				{
					game->board[i][j] == game->userChar ? User_Arr[6]++ : Bot_Arr[6]++;
				}
				if (j == (2 - i))
				{
					game->board[i][j] == game->userChar ? User_Arr[7]++ : Bot_Arr[7]++;
				}

			}
			if (User_Arr[0] == 3 || User_Arr[1] == 3 || User_Arr[2] == 3 || User_Arr[3] == 3 || User_Arr[4] == 3 || User_Arr[5] == 3 || User_Arr[6] == 3 || User_Arr[7] == 3)
			{
				game->status = USER_WIN;
				turn = true;
				break;
			}
			else if (Bot_Arr[0] == 3 || Bot_Arr[1] == 3 || Bot_Arr[2] == 3 || Bot_Arr[3] == 3 || Bot_Arr[4] == 3 || Bot_Arr[5] == 3 || Bot_Arr[6] == 3 || Bot_Arr[7] == 3)
			{
				game->status = BOT_WIN;
				turn = true;
				break;
			}
		}

		if (turn && game->status != USER_WIN && game->status != BOT_WIN)
		{
			game->status = NOT_WIN;
			return true;
		}
		game->isUserTurn == true ? game->isUserTurn = false : game->isUserTurn = true;
		return turn;
	}


