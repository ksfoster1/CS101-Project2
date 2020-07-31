/*Kenya Foster
File: main.cpp
CS 101
Project 2
A Game of Sticks
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

class Hat
{
	private:
		int k; //number of balls that can be picked up per round
		vector<int> balls; //number of balls associated with a move
		int comPlay; //# of sticks chosen at a move
	public:
		Hat() {};
		Hat(int num)
		{
			k = num;
			for (int i = 1; i <= k; i++)
			{
				balls.push_back(i);
			}
		}

		void updateCount(int win, int comPlay)//updates count based off of win or loss
		{
			if (win == 1)
			{
				//cout << "SIZEB4" << balls.size() << endl;
				balls.push_back(comPlay);
				//cout <<  "SIZE:" << balls.size() << endl;
			}
			else
			{
				for (int i = 1; i <= k; i++)
				{
					balls.push_back(i);
				}
			}
		}

		int chooseMove(Hat game)//chooses AI move
		{
			srand(time(NULL));
			int comPlay = rand() % game.balls.size();
			while (comPlay == 0)
				comPlay = rand() % game.balls.size();
			return comPlay;
		}

		int getSize()
		{
			return balls.size();
		}

};

void train(Hat game, int numSticksTable, int numSticksRound)
{
	int tv = numSticksTable;
	int play = 0;
	int play2 = 0;
	for (int i = 0; i < 100; i++)
	{
		while (numSticksTable != 0)
		{
			srand(time(NULL));
			play = (rand() % numSticksRound) + 1;

			numSticksTable = numSticksTable - play;
			if (numSticksTable <= 0)
			{
				int win = 1;
				(game).updateCount(win, play2);
				break;
			}

			play2 = game.chooseMove(game);
			
			numSticksTable = numSticksTable - play2;
			if (numSticksTable <= 0)
			{
				break;
			}
		}
		numSticksTable = tv;
	}
}


int main(int argc, char*argv[])
{
	int numSticksTable = 11; //number of sticks on the table intially
	int numSticksRound = 3; //number of sticks picked up per round
	int play = 1; //how many sticks are taken during that play
	int option; //whether to play against AI or another player
	int playAgain = 1; //whether to play another game

	cout << "Welcome to the game of sticks!" << endl;

	while (numSticksTable <= 100 || numSticksTable >= 10)
	{
		cout << "How many sticks are there on the table intially (10-100)?";
		cin >> numSticksTable;
		if (numSticksTable > 100 || numSticksTable < 10)
		{
			cout << "Please enter a number between 10 and 100" << endl;
		}
		else
			break;
	}

	while (numSticksRound <= 20 || numSticksRound >= 2)
	{
		cout << "How many sticks can be picked up per round (2-20)?";
		cin >> numSticksRound;
		if (numSticksRound > 20 || numSticksRound < 2)
		{
			cout << "Please enter a number between 2 and 20" << endl;
		}
		else
			break;
	}

	cout << "Options:" << endl;
	cout << "  Play against a friend(1)" << endl;
	cout << "  Play against the computer(2)" << endl;
	cout << "Which option do you take (1-2)?";
	cin >> option;
	while (option > 2 || option < 1)
	{
		cout << "Please enter an option between 1 and 2";
		cin >> option;
	}

	if (option == 1)
	{
		int tv = numSticksTable;
		while (playAgain == 1)
		{
			while (numSticksTable != 0)
			{
				cout << "There are " << numSticksTable << " sticks on the board" << endl;
				cout << "Player 1: How many sticks do you take (1-" << numSticksRound << ")?";
				cin >> play;
				while (play > numSticksRound)
				{
					cout << "Please enter a number between 1 and " << numSticksRound << endl;
					cout << "Player 1: How many sticks do you take (1-" << numSticksRound << ")?";
					cin >> play;
				}

				numSticksTable = numSticksTable - play;
				if (numSticksTable <= 0)
				{
					cout << "Player 1, you lose." << endl;
					break;
				}

				cout << "There are " << numSticksTable << " sticks on the board" << endl;
				cout << "Player 2: How many sticks do you take (1-" << numSticksRound << ")?";
				cin >> play;
				while (play > numSticksRound)
				{
					cout << "Please enter a number between 1 and " << numSticksRound << endl;
					cout << "Player 2: How many sticks do you take (1-" << numSticksRound << ")?";
					cin >> play;
				}
				numSticksTable = numSticksTable - play;
				if (numSticksTable <= 0)
				{
					cout << "Player 2, you lose." << endl;
					break;
				}
				
			}
			cout << "Play again? (1 = yes, 0 = no)";
			cin >> playAgain;
			numSticksTable = tv;
		}
		
	}
	else //play against AI
	{	
		int tv = numSticksTable;
		Hat *game[100];

		cout << "Training AI, please wait..." << endl;

		for (int i = 0; i < numSticksTable; i++)
		{
			game[i] = new Hat(numSticksRound);
			train(*game[i], numSticksTable, numSticksRound);
		}
	
		while (playAgain == 1)
		{
			int play2 = 0;
			while (numSticksTable != 0)
			{
				cout << "There are " << numSticksTable << " sticks on the board" << endl;
				cout << "Player 1: How many sticks do you take (1-" << numSticksRound << ")?";
				cin >> play;
				while (play > numSticksRound)
				{
					cout << "Please enter a number between 1 and " << numSticksRound << endl;
					cout << "Player 1: How many sticks do you take (1-" << numSticksRound << ")?";
					cin >> play;
				}

				numSticksTable = numSticksTable - play;
				if (numSticksTable <= 0)
				{
					cout << "Player 1, you lose." << endl;
					int win = 1;
					(*game[numSticksTable]).updateCount(win, play2);
					break;
				}

				cout << "There are " << numSticksTable << " sticks on the board" << endl;
				play2 = (*game[numSticksTable]).chooseMove(*game[numSticksTable]);
				cout << "AI selects " << play2 << endl;
				
				
				numSticksTable = numSticksTable - play2;
				if (numSticksTable <= 0)
				{
					cout << "AI loses." << endl;
					break;
				}
			}
			cout << "Play again? (1 = yes, 0 = no)";
			cin >> playAgain;
			numSticksTable = tv;
		}
	}
	return 0;
}
