#include <stdio.h> 
#include <conio.h>
#include <windows.h>


//putting spaces in the board
void emptyboard(char board[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			board[i][j] = ' ';
		}
	}
}


int input_reset()
{
	int i = 3;
	char enter;
	char reset = getch();
	if (reset == 'r')            // reset
		i = 8;
	else
	{
		printf("%c", reset);
		if (reset == '0')
		{
			enter = getch();
			if (enter == 13)
			{
				i = 0;
			}
		}
		else if (reset == '1')
		{
			enter = getch();
			if (enter == 13)
			{
				i = 1;
			}
		}
		else if (reset == '2')
		{
			enter = getch();
			if (enter == 13)
			{
				i = 2;
			}
		}
		else
		{
			enter = getch();
			if (enter == 13)
			{
				i = 3;
			}
		}
	}
	return i;
}


void printingboard(char board[3][3])
{
	// print the board

	for (int i = 0; i < 3; i++)
	{
		printf("\t\t-------------\n\t\t");
		for (int j = 0; j < 3; j++)
		{
			printf("| %c ", board[i][j]);

		}
		printf("|");
		printf("\n");
	}
	printf("\t\t-------------\n");
}


int checkwin(char board[3][3], char z1, char z2)
{
	int m_counter = 0;
	// checking for the win condtions

	// rows
	for (int i = 0; i < 3; i++)
	{
		if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
		{
			if (board[i][0] == z1)
				return -1;
			else if (board[i][0] == z2)
				return 1;
		}
	}
	// columns
	for (int i = 0; i < 3; i++)
	{
		if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
		{
			if (board[0][i] == z1)
				return -1;
			else if (board[0][i] == z2)
				return 1;
		}
	}
	// main diagonal
	if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
	{

		if (board[0][0] == z1)
			return -1;
		else if (board[0][0] == z2)
			return 1;
	}
	// inverse main diagonal 
	else if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
	{

		if (board[0][2] == z1)
			return -1;
		else if (board[0][2] == z2)
			return 1;
	}

	else
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j] == ' ')
					break;
				else
					m_counter++;
			}
		}
		if (m_counter == 9)
			return 0;
	}
	return 3;
}

// 1 player condition
int minimax(char board[3][3], char z1, char z2, bool cturn)
{

	if (checkwin(board, z1, z2) == 1)
		return 1;

	if (checkwin(board, z1, z2) == -1)
		return -1;

	if (checkwin(board, z1, z2) == 0)
		return 0;

	if (cturn) //for player 2 (computer) play in all the empty indexes and see the best place to play in then remove the others again
	{
		int best = -1;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j] == ' ')
				{
					board[i][j] = z2;
					if (best < minimax(board, z1, z2, false))
						best = minimax(board, z1, z2, false);

					board[i][j] = ' ';
				}
			}
		}
		return best;
	}

	else //for player 1 play in all the empty indexes and calculate the total score then remove them again
	{
		int best = 1;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j] == ' ')
				{
					board[i][j] = z1;
					if (best > minimax(board, z1, z2, true))
						best = minimax(board, z1, z2, true);

					board[i][j] = ' ';
				}
			}
		}
		return best;

	}

}


void computermove(char board[3][3], char z1, char z2) //playing in the best place
{
	int score = -10, besti = 0, bestj = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == ' ')
			{
				board[i][j] = z2;
				int currentscore = minimax(board, z1, z2, false);

				if (currentscore > score)
				{
					score = currentscore;
					besti = i;
					bestj = j;
				}
				board[i][j] = ' ';
			}
		}
	}
	board[besti][bestj] = z2;

}


int main()
{
	bool startagain;
	do
	{
		char board[3][3], z1 = ' ', z2 = ' ';
		int player = 0;
		startagain = false;


		emptyboard(board);


		do //choosing no. of players and keep scaning again if user entered number other than 1 or 2
		{
			printf("\nChoose the number of players (1 or 2) : ");
			scanf("%d", &player);
		} while (player != 1 && player != 2);


		do //choosing whether to play with X or O for player 1 and keep scaning again if user entered letter other than X or O
		{
			printf("Player1 please choose (X or O) : ");
			scanf(" %c", &z1);
		} while (z1 != 'x' && z1 != 'o');

		if (z1 == 'x') //setting z1 as whether (X or O) and z2 with the other by default
			z2 = 'o';
		else if (z1 == 'o')
			z2 = 'x';

		int flag = 1;

		// for 2 players condition
		if (player == 2)
		{
			printf("\n\n*Press 'r' to reset the game*\n\n");
			printingboard(board);

			for (int i = 1; i < 10; i++) //to play z1 in odd turns and z2 in even turns
			{
				char input;
				if (i % 2 == 0)
				{
					input = z2;
					printf("Player2 :\n");
				}
				else
				{
					input = z1;
					printf("Player1 :\n");
				}

				int a = 3, b = 3;

				do
				{
					do
					{
						printf("Enter number of the row (0,1,2) : ");   //input placement
						a = input_reset();
						printf("\n");
						if (a == 8)
						{
							printf("\n==========================================\n");
							startagain = true;
							break;
						}
					} while (a >= 3 || a < 0);

					if (startagain == true)
						break;

					do
					{
						printf("Enter number of the column (0,1,2) : ");   //input placement
						b = input_reset();
						printf("\n");
						if (b == 8)
						{
							printf("\n==========================================\n");
							startagain = true;
							break;
						}
					} while (b >= 3 || b < 0);

					if (startagain == true)
						break;

				} while (board[a][b] != ' ');

				if (startagain == true)
					break;

				board[a][b] = input;


				printingboard(board);


				if (checkwin(board, z1, z2) == -1)
				{
					printf("\n\t\t*Player1 won*\n");
					Beep(400, 300);
					break;
				}
				else if (checkwin(board, z1, z2) == 1)
				{
					printf("\n\t\t*Player2 won*\n");
					Beep(400, 300);
					break;
				}
			}
		}
		//for 1 player conition
		else if (player == 1)
		{
			int i = 1, e = 10, turn;
			do
			{
				printf("Choose you turn (1 or 2) : ");
				scanf("%d", &turn);
				if (turn == 2)
				{
					i++;
					e++;
					flag = 0;
					break;
				}
			} while (turn != 1);

			printf("\n\n*Press 'r' to reset the game anytime*\n\n");

			if (i == 1)
				printingboard(board);

			for (i; i < e; i++)
			{
				int a = 3, b = 3;
				if (i % 2 == 0)
				{
					computermove(board, z1, z2);
					printingboard(board);


					if (checkwin(board, z1, z2) == -1)
					{
						printf("\n\t\t You won\n");
						Beep(400, 300);
						break;
					}
					else if (checkwin(board, z1, z2) == 1)
					{
						printf("\n\t\t You lost\n");
						Beep(400, 300);
						break;
					}

				}

				else
				{
					do   // check if the index is empty
					{
						do
						{
							printf("Enter number of the row (0,1,2) : ");   //input placement
							a = input_reset();
							printf("\n");
							if (a == 8)
							{
								printf("\n==========================================\n");
								startagain = true;
								break;
							}
						} while (a >= 3 || a < 0);

						if (startagain == true)
							break;

						do
						{
							printf("Enter number of the column (0,1,2) : ");   //input placement
							b = input_reset();
							printf("\n");
							if (b == 8)
							{
								printf("\n==========================================\n");
								startagain = true;
								break;
							}
						} while (b >= 3 || b < 0);

						if (startagain == true)
							break;

					} while (board[a][b] != ' ');

					if (startagain == true)
						break;

					board[a][b] = z1;

				}
			}
		}


		// for draw condition
		if (checkwin(board, z1, z2) == 0)
		{
			if (flag == 1)
				printingboard(board);

			printf("\n\t\t   Draw!\n");
			Beep(400, 300);
		}


		// for playing again
		if (startagain == false)
		{
			printf("\n\n\t*Press enter to play again*\n\n");
			char playagain = getch();
			if (playagain == 13)
			{
				startagain = true;
				printf("\n==========================================\n");
			}
		}

	} while (startagain);
	return 0;
}