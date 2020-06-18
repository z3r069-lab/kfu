#include <iostream>
#include <ctime>
#include "Head.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	Game game;
	char character;
	cout << "введите символ для игры (x | o)" << endl;
	cin >> character;
	while ((character != 'X') && (character != 'x') && (character != 'o') && (character != '0')) {
		cout << "неверный символ попробуйте еще раз";
	}
	game = initGame(character);
	updateDisplay(game);
	while (!updateGame(&game))
	{
		game.isUserTurn == true ? userTurn(&game) : botTurn(&game);
		updateDisplay(game);		
	}
	if (game.status == USER_WIN)
	{
		cout << "победа" << endl;
	}
	else if (game.status == BOT_WIN)
	{
		cout << "победил бот" << endl;
	}
	else
	{
		cout << "ничья" << endl;
	}
}

