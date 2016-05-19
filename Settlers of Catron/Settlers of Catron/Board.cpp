#include "Board.h"
#include <iostream>
#include <Windows.h>
#include "Tile.h"
#include <ctime>
#include <stdlib.h>
#include <iomanip>

// From the Guy That Had to Edit This Mess: \
I'm going to have to recommend downloading this just so you can minimize several of the function definitions. Looking at it all at once is enough to fry one's brain. 

Board::Board(int p) {
	playerCount = p;
	setBoard();
}

void Board::displayBoard()
{
	system("CLS"); // clears screen
	const int extraOffset = 10; // how much the board is position to the right of the screen
	// The rest of the code goes through several loops to create a display that implements the state of variables and assigns colors to ascii values based on the state through color functions.
	for (int i = 0; i < 12 + extraOffset; i++)
	{
		cout << " ";
	}
	for (int j = 0; j < 3; j++)
	{
		colorPlayer(boardCoordinates[0][j].getTNodeState(1), boardCoordinates[0][j].getTNode(1));
		cout << "       ";

	}
	cout << endl;
	for (int i = 0; i < 5; i++)
	{
		int columns = (5 - abs(i - 2));
		int offset = (4 * (abs(i - 2)) + extraOffset);
		static int counter = 1;
		if (counter >18)
		{
			counter = 1;
		}
		for (int i = 0; i < offset; i++)
		{
			cout << " ";
		}
		for (int j = 0; j < columns; j++)
		{
			colorPlayer(boardCoordinates[i][j].getTNodeState(6), boardCoordinates[i][j].getTNode(6));
			colorPlayer('/', boardCoordinates[i][j].getTSide(6));
			cout << "/";
			colorTile(boardCoordinates[i][j].getTType());
			cout << "\\";
			colorPlayer('\\', boardCoordinates[i][j].getTSide(1));
			colorPlayer(boardCoordinates[i][j].getTNodeState(2), boardCoordinates[i][j].getTNode(2));
		}
		cout << endl;
		for (int i = 0; i < offset; i++)
		{
			cout << " ";
		}
		for (int j = 0; j < columns; j++)
		{
			cout << " ";
			colorPlayer('|', boardCoordinates[i][j].getTSide(5));
			cout << "|";
			if (boardCoordinates[i][j].getTRobber() == true)
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 0x0C);
				cout << setfill('0') << setw(2) << boardCoordinates[i][j].getTValue();
				SetConsoleTextAttribute(hConsole, 0x0F);
			}
			else
				cout << setfill('0') << setw(2) << boardCoordinates[i][j].getTValue();
			cout << "|";
			colorPlayer('|', boardCoordinates[i][j].getTSide(2));
			cout << " ";
		}
		cout << endl;
		for (int i = 0; i < offset; i++)
		{
			cout << " ";
		}
		for (int j = 0; j <columns; j++)
		{
			colorPlayer(boardCoordinates[i][j].getTNodeState(5), boardCoordinates[i][j].getTNode(5));
			colorPlayer('\\', boardCoordinates[i][j].getTSide(4));
			cout << "\\";
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 0xF0);
			cout << setfill('0') << setw(2) << counter++;
			SetConsoleTextAttribute(hConsole, 0x0F);
			cout << "/";
			colorPlayer('/', boardCoordinates[i][j].getTSide(3));
			colorPlayer(boardCoordinates[i][j].getTNodeState(3), boardCoordinates[i][j].getTNode(3));
		}
		cout << endl;
	}
	for (int i = 0; i < 12 + extraOffset; i++)
	{
		cout << " ";
	}
	for (int j = 0; j < 3; j++)
	{
		colorPlayer(boardCoordinates[4][j].getTNodeState(4), boardCoordinates[4][j].getTNode(4));
		cout << "       ";

	}
	cout << endl;
}

int Board::returnPlayerPosition(int row, int column, int node)
{
	return boardCoordinates[row][column].getTNode(node);
}

int Board::returnTileValue(int row, int column)
{
	return boardCoordinates[row][column].getTValue();
}

char Board::returnPlayerHouse(int row, int column, int node)
{
	return boardCoordinates[row][column].getTNodeState(node);
}

char Board::returnTileType(int row, int column)
{
	return boardCoordinates[row][column].getTType();
}

bool Board::returnRobber(int row, int column)
{
	return boardCoordinates[row][column].getTRobber();
}

void Board::setBoard()
{
	// Creates random tile values
	srand(time(NULL));
	int values[19] = { 0,2,3,3,4,4,5,5,6,6,8,8,9,9,10,10,12,11,11 };
	int randomD = rand() % 2;
	if (randomD != 0) // allows more randomness if D is allowed to be in the center row or not.
	{
		int temp = values[0];
		values[0] = values[1];
		values[1] = temp;
	}
	int oddOrEven = rand() % 2;
	static int evenCounter = 0;
	static int oddCounter = 0;
	static int index = 0;
	//main code to set the board
	for (static int i = 0; i < 6; i++)
	{
		if (oddOrEven == 0) // starts with row 1 or 3
		{
			if (evenCounter < 4) // even rows ( rows 2 and 4 (index 3 or 5)) only have 4 columns
			{
				int tempRow = rand() % 2;
				if (tempRow == 0) // row 1 start
				{
					int tempColumn = rand() % 4;
					do
					{
						tempColumn = rand() % 4; // random column after row is determined
					} while (boardCoordinates[1][tempColumn].getTValue() != -1);
					boardCoordinates[1][tempColumn].setTValue(values[index]);
					index++;
					do
					{
						tempColumn = rand() % 4;
					} while (boardCoordinates[3][tempColumn].getTValue() != -1);
					boardCoordinates[3][tempColumn].setTValue(values[index]);
					index++;
				}
				else // row 3 start
				{
					int tempColumn = rand() % 4;
					do
					{
						tempColumn = rand() % 4;
					} while (boardCoordinates[3][tempColumn].getTValue() != -1);
					boardCoordinates[3][tempColumn].setTValue(values[index]);
					index++;
					do
					{
						tempColumn = rand() % 4;
					} while (boardCoordinates[1][tempColumn].getTValue() != -1);
					boardCoordinates[1][tempColumn].setTValue(values[index]);
					index++;
				}
				evenCounter++;
			}

			///////
			if (oddCounter <6) // rows 0 and 4 are counted seperately. if row 0, row 0 and row 2 get assigned. if row 4, row 4 and row 2 get assigned. since row 0 and 4 have 3 tiles, together they make up 6 indexes
			{

				int tempColumn = rand() % 3;
				do
				{
					tempColumn = rand() % 3;
				} while (boardCoordinates[0][tempColumn].getTValue() != -1);
				boardCoordinates[0][tempColumn].setTValue(values[index]);
				index++;
				if (oddCounter != 5) {
					do
					{
						tempColumn = rand() % 5;
					} while (boardCoordinates[2][tempColumn].getTValue() != -1);
					boardCoordinates[2][tempColumn].setTValue(values[index]);
					index++;
				}
				oddCounter++;

				tempColumn = rand() % 3;
				do
				{
					tempColumn = rand() % 3;
				} while (boardCoordinates[4][tempColumn].getTValue() != -1);
				boardCoordinates[4][tempColumn].setTValue(values[index]);
				index++;
				if (oddCounter != 5) {
					do
					{
						tempColumn = rand() % 5;
					} while (boardCoordinates[2][tempColumn].getTValue() != -1);
					boardCoordinates[2][tempColumn].setTValue(values[index]);
					index++;
				}
				oddCounter++;
			}
		}
		else // does the same thing but starts with rows 0, 2, or 4
		{
			if (oddCounter < 6)
			{

				int tempColumn = rand() % 3;
				do
				{
					tempColumn = rand() % 3;
				} while (boardCoordinates[0][tempColumn].getTValue() != -1);
				boardCoordinates[0][tempColumn].setTValue(values[index]);
				index++;
				if (oddCounter != 5) {
					do
					{
						tempColumn = rand() % 5;
					} while (boardCoordinates[2][tempColumn].getTValue() != -1);
					boardCoordinates[2][tempColumn].setTValue(values[index]);
					index++;
				}
				oddCounter++;

				tempColumn = rand() % 3;
				do
				{
					tempColumn = rand() % 3;
				} while (boardCoordinates[4][tempColumn].getTValue() != -1);
				boardCoordinates[4][tempColumn].setTValue(values[index]);
				index++;
				if (oddCounter != 5) {
					do
					{
						tempColumn = rand() % 5;
					} while (boardCoordinates[2][tempColumn].getTValue() != -1);
					boardCoordinates[2][tempColumn].setTValue(values[index]);
					index++;
				}
				oddCounter++;
			}
			if (evenCounter < 4)
			{
				int tempRow = rand() % 2;
				if (tempRow == 0) // row 1 start
				{
					int tempColumn = rand() % 4;
					do
					{
						tempColumn = rand() % 4;
					} while (boardCoordinates[1][tempColumn].getTValue() != -1);
					boardCoordinates[1][tempColumn].setTValue(values[index]);
					index++;
					do
					{
						tempColumn = rand() % 4;
					} while (boardCoordinates[3][tempColumn].getTValue() != -1);
					boardCoordinates[3][tempColumn].setTValue(values[index]);
					index++;
				}
				else // row 3 start
				{
					int tempColumn = rand() % 4;
					do
					{
						tempColumn = rand() % 4;
					} while (boardCoordinates[3][tempColumn].getTValue() != -1);
					boardCoordinates[3][tempColumn].setTValue(values[index]);
					index++;
					do
					{
						tempColumn = rand() % 4;
					} while (boardCoordinates[1][tempColumn].getTValue() != -1);
					boardCoordinates[1][tempColumn].setTValue(values[index]);
					index++;
				}
				evenCounter++;
			}

		}
	}

	// Creates random tile types;
	char type[18] = { 'T','T','T','T','G','G','G','G','W','W', 'W', 'W', 'O','O','O','B','B','B' };
	for (int i = 0; i < 18; i++)
	{
		int chooseRandom = rand() % 18;
		char temp = type[i];
		type[i] = type[chooseRandom];
		type[chooseRandom] = temp;
	}
	static int typeIndex = 0;
	for (int i = 0; i < 5; i++)
	{
		int columns = (5 - abs(i - 2));
		for (int j = 0; j < columns; j++)
		{
			if (boardCoordinates[i][j].getTValue() != 0)
			{
				boardCoordinates[i][j].setTType(type[typeIndex]);
				typeIndex++;
			}
			else
			{
				boardCoordinates[i][j].setTType('D');
				boardCoordinates[i][j].setTRobber(true);
			}

		}
	}

}

void Board::changePlayerCount(int x)
{
	playerCount = x;
}

void Board::colorPlayer(char text, int player) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (player <= -1)
		SetConsoleTextAttribute(hConsole, 0x00); // Black
	if (player == 1)
		SetConsoleTextAttribute(hConsole, 0x0C); // Red
	if (player == 2)
		SetConsoleTextAttribute(hConsole, 0x0E); // Yellow
	if (player == 3)
		SetConsoleTextAttribute(hConsole, 0x0A); // Green
	if (player == 4)
		SetConsoleTextAttribute(hConsole, 0x0D); // Purple
	cout << text;
	SetConsoleTextAttribute(hConsole, 0x0F); // Default
}

void Board::colorTile(char type) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (type == 'T')
		SetConsoleTextAttribute(hConsole, 0xA0); // Black on Green
	if (type == 'G')
		SetConsoleTextAttribute(hConsole, 0x2A); // Green on Dark Green
	if (type == 'O')
		SetConsoleTextAttribute(hConsole, 0x78); // Gray on Light Gray
	if (type == 'D')
		SetConsoleTextAttribute(hConsole, 0x66); // Gold
	if (type == 'B')
		SetConsoleTextAttribute(hConsole, 0x4F); // White on Maroon
	if (type == 'W')
		SetConsoleTextAttribute(hConsole, 0xE6); // Gold on Yellow

	cout << type << type;
	SetConsoleTextAttribute(hConsole, 0x0F); // Default
}


pair<int, int> Board::tileToBoardCoordinates(int tile) // converts tile input to board coordinates
{
	pair <int, int> boardCoordinates;
	
	switch (tile) {

	case 1:
		boardCoordinates.first = 0;
		boardCoordinates.second = 0;
		break;

	case 2:
		boardCoordinates.first = 0;
		boardCoordinates.second = 1;
		break;

	case 3:
		boardCoordinates.first = 0;
		boardCoordinates.second = 2;
		break;

	case 4:
		boardCoordinates.first = 1;
		boardCoordinates.second = 0;
		break;

	case 5:
		boardCoordinates.first = 1;
		boardCoordinates.second = 1;
		break;

	case 6:
		boardCoordinates.first = 1;
		boardCoordinates.second = 2;
		break;

	case 7:
		boardCoordinates.first = 1;
		boardCoordinates.second = 3;
		break;

	case 8:
		boardCoordinates.first = 2;
		boardCoordinates.second = 0;
		break;

	case 9:
		boardCoordinates.first = 2;
		boardCoordinates.second = 1;
		break;

	case 10:
		boardCoordinates.first = 2;
		boardCoordinates.second = 2;
		break;

	case 11:
		boardCoordinates.first = 2;
		boardCoordinates.second = 3;
		break;

	case 12:
		boardCoordinates.first = 2;
		boardCoordinates.second = 4;
		break;

	case 13:
		boardCoordinates.first = 3;
		boardCoordinates.second = 0;
		break;

	case 14:
		boardCoordinates.first = 3;
		boardCoordinates.second = 1;
		break;

	case 15:
		boardCoordinates.first = 3;
		boardCoordinates.second = 2;
		break;

	case 16:
		boardCoordinates.first = 3;
		boardCoordinates.second = 3;
		break;

	case 17:
		boardCoordinates.first = 4;
		boardCoordinates.second = 0;
		break;

	case 18:
		boardCoordinates.first = 4;
		boardCoordinates.second = 1;
		break;

	case 19:
		boardCoordinates.first = 4;
		boardCoordinates.second = 2;
		break;

	}
	return boardCoordinates;
}

void Board::placeRoad(int player, int tile, int side)
{
	if (checkRoadPlace(player, tile - 1, side - 1) == true)
	{
		*sideAddressCoordinates[tile - 1][side - 1] = player;
		if (side == 1) // side 1
		{
			int nextTo[19] = { -1,-1,-1,0,1,2,-1,3,4,5,6,-1,8,9,10,11,13,14,15 }; // arrays used to reference which tiles are adjacent to that side, -1 means no tiles adjacent
			int oppositeSide = (side + 2) & 6 + 1; // adjacent sides will always be opposites in hexagon
			if (nextTo[tile - 1] != -1) // sets the adjacent tile and opposite side to same player so board display will be correct since tiles can share the same sides
			{
				*sideAddressCoordinates[nextTo[tile - 1]][oppositeSide] = player;
			}
		}
		if (side == 2) // same thing
		{
			int nextTo[19] =
			{
				1,2,-1,
				4,5,6,-1,
				8,9,10,11,-1,
				13,14,15,-1,
				17,18,-1
			};
			int oppositeSide = (side + 2) % 6 + 1;
			if (nextTo[tile - 1] != -1)
			{
				*sideAddressCoordinates[nextTo[tile - 1]][oppositeSide] = player;
			}
		}
		if (side == 3)
		{
			int nextTo[19] =
			{
				4,5,6,
				8,9,10,11,
				12,13,14,15,-1,
				16,17,18,-1,
				-1,-1,-1
			};
			int oppositeSide = (side + 2) %6 + 1;
			if (nextTo[tile - 1] != -1)
			{
				*sideAddressCoordinates[nextTo[tile - 1]][oppositeSide] = player;
			}
		}
		if (side == 4)
		{
			int nextTo[19] =
			{
				3,4,5,
				7,8,9,10,
				-1,12,13,14,15,
				-1,16,17,18,
				-1,-1,-1
			};
			int oppositeSide = (side + 2) % 6 + 1;
			if (nextTo[tile - 1] != -1)
			{
				*sideAddressCoordinates[nextTo[tile - 1] - 1][oppositeSide] = player;
			}
		}
		if (side == 5)
		{
			int nextTo[19] =
			{
				-1,0,1,
				-1,3,4,5,
				-1,7,8,8,10,
				-1,12,13,14,
				-1,16,17
			};
			int oppositeSide = (side + 2) % 6 + 1;
			if (nextTo[tile - 1] != -1)
			{
				*sideAddressCoordinates[nextTo[tile - 1] - 1][oppositeSide] = player;
			}
		}
		if (side == 6)
		{
			int nextTo[19] =
			{
				-1,-1,-1,
				-1,0,1,2,
				-1,3,4,5,6,
				7,8,9,10,
				12,13,14
			};
			int oppositeSide = (side + 4)% 6;
			if (nextTo[tile - 1] != -1)
			{
				*sideAddressCoordinates[nextTo[tile - 1]][oppositeSide] = player;
			}
		}
	}
	else
	{
		cout << "Not a valid location\n";
	}
};

void Board::setRobber(int tile)
{
	int row = tileToBoardCoordinates(tile).first;
	int column = tileToBoardCoordinates(tile).second;
	for (int i = 0; i < 5; i++) //find the current robber and set it to false
	{
		for (int j = 0; j < 5 - abs(2 - i); j++)
		{
			if (boardCoordinates[i][j].getTRobber() == true)
			{
				boardCoordinates[i][j].setTRobber(false);
			}
		}
	}
	boardCoordinates[row][column].setTRobber(true); // set target tile to robber true
}

bool Board::checkRoadPlace(int player, int tile, int side)
{

	if (side < 0 || side >5) // valid row
	{
		return false;
	}
	if (tile < 0 || tile >18) // valid tile
	{
		return false;
	}
	if (*sideAddressCoordinates[tile][side] != -1) // if side has no player value
	{
		return false;
	}
	if (*nodeReferenceCoordinates[tile][side] == player || *nodeReferenceCoordinates[tile][(side + 1) % 6] == player) // if house/town is connected to the road
	{
		return true;
	}
	// turns index to tile values for ease of use and reference to other functions
	side++;
	tile++;
	if (side == 1) // side one
	{
		int nextTo[19] = { -1,-1,-1,0,1,2,-1,3,4,5,6,-1,8,9,10,11,13,14,15 }; // assigns adjacent tiles
		int oppositeSide = abs((side + 1) % 6); // check the sides the is represented as the same side on the board
		if (nextTo[tile - 1] != -1)
		{
			if (*sideAddressCoordinates[nextTo[tile - 1]][(oppositeSide + 1) % 6] != player && *sideAddressCoordinates[nextTo[tile - 1]][(oppositeSide - 1) % 6] != player && *sideAddressCoordinates[tile - 1][abs((side - 2) % 6)] != player &&*sideAddressCoordinates[tile - 1][(abs(side) % 6)] != player)
				return false;
		}
		else
		{
			if (*sideAddressCoordinates[tile - 1][abs((side - 2) % 6)] != player && *sideAddressCoordinates[tile - 1][((side) % 6)] != player)
				return false;
		}
	}
	if (side == 2) // code repeates but with different reference sides
	{
		int nextTo[19] =
		{
			1,2,-1,
			4,5,6,-1,
			8,9,10,11,-1,
			13,14,15,-1,
			17,18,-1
		};
		int oppositeSide = abs((side + 1) % 6);
		if (nextTo[tile - 1] != -1)
		{
			if (*sideAddressCoordinates[nextTo[tile - 1]][(oppositeSide + 1) % 6] != player && *sideAddressCoordinates[nextTo[tile - 1]][(oppositeSide - 1) % 6] != player && *sideAddressCoordinates[tile - 1][abs((side - 2) % 6)] != player &&*sideAddressCoordinates[tile - 1][(abs(side) % 6)] != player)
				return false;
		}
		else
		{
			if (*sideAddressCoordinates[tile - 1][abs((side - 2) % 6)] != player && *sideAddressCoordinates[tile - 1][((side) % 6)] != player)
				return false;
		}
	}
	if (side == 3)
	{
		int nextTo[19] =
		{
			4,5,6,
			8,9,10,11,
			12,13,14,15,-1,
			16,17,18,-1,
			-1,-1,-1
		};
		int oppositeSide = abs((side + 1) % 6);
		if (nextTo[tile - 1] != -1)
		{
			if (*sideAddressCoordinates[nextTo[tile - 1]][(oppositeSide + 1) % 6] != player && *sideAddressCoordinates[nextTo[tile - 1]][(oppositeSide - 1) % 6] != player && *sideAddressCoordinates[tile - 1][abs((side - 2) % 6)] != player &&*sideAddressCoordinates[tile - 1][(abs(side) % 6)] != player)
				return false;
		}
		else
		{
			if (*sideAddressCoordinates[tile - 1][abs((side - 2) % 6)] != player && *sideAddressCoordinates[tile - 1][((side) % 6)] != player)
				return false;
		}
	}
	if (side == 4)
	{
		int nextTo[19] =
		{
			3,4,5,
			7,8,9,10,
			-1,12,13,14,15,
			-1,16,17,18,
			-1,-1,-1
		};
		int oppositeSide = abs((side + 1) % 6);
		if (nextTo[tile - 1] != -1)
		{
			if (*sideAddressCoordinates[nextTo[tile - 1]][(oppositeSide + 1) % 6] != player && *sideAddressCoordinates[nextTo[tile - 1]][(oppositeSide - 1) % 6] != player && *sideAddressCoordinates[tile - 1][abs((side - 2) % 6)] != player &&*sideAddressCoordinates[tile - 1][(abs(side) % 6)] != player)
				return false;
		}
		else
		{
			if (*sideAddressCoordinates[tile - 1][abs((side - 2) % 6)] != player && *sideAddressCoordinates[tile - 1][((side) % 6)] != player)
				return false;
		}
	}
	if (side == 5)
	{
		int nextTo[19] =
		{
			-1,0,1,
			-1,3,4,5,
			-1,7,8,8,10,
			-1,12,13,14,
			-1,16,17
		};
		int oppositeSide = abs((side + 1) % 6);
		if (nextTo[tile - 1] != -1)
		{
			if (*sideAddressCoordinates[nextTo[tile - 1]][(oppositeSide + 1) % 6] != player && *sideAddressCoordinates[nextTo[tile - 1]][(oppositeSide - 1) % 6] != player && *sideAddressCoordinates[tile - 1][abs((side - 2) % 6)] != player &&*sideAddressCoordinates[tile - 1][(abs(side) % 6)] != player)
				return false;
		}
		else
		{
			if (*sideAddressCoordinates[tile - 1][abs((side - 2) % 6)] != player && *sideAddressCoordinates[tile - 1][((side) % 6)] != player)
				return false;
		}
	}
	if (side == 6)
	{
		int nextTo[19] =
		{
			-1,-1,-1,
			-1,0,1,2,
			-1,3,4,5,6,
			7,8,9,10,
			12,13,14
		};
		int oppositeSide = abs((side + 1) % 6);
		if (nextTo[tile - 1] != -1)
		{
			if (*sideAddressCoordinates[nextTo[tile - 1]][(oppositeSide + 1) % 6] != player && *sideAddressCoordinates[nextTo[tile - 1]][(oppositeSide - 1) % 6] != player && *sideAddressCoordinates[tile - 1][abs((side - 2) % 6)] != player &&*sideAddressCoordinates[tile - 1][(abs(side) % 6)] != player)
				return false;
		}
		else
		{
			if (*sideAddressCoordinates[tile - 1][abs((side - 2) % 6)] != player && *sideAddressCoordinates[tile - 1][((side) % 6)] != player)
				return false;
		}
	}
	return true;
}

void Board::placeNode(int player, int tile, int node)
{

	if (checkNodePlace(player, tile, node) == true) // checks if valid
	{
		// converts to array coordinates
		int row = tileToBoardCoordinates(tile).first;
		int column = tileToBoardCoordinates(tile).second;
		// allows for index to start at 0
		node--;
		boardCoordinates[row][column].setTNodes(node, player); // sets target node
		// code identifies nodes that are the same on the board display but within different Tile objects
		// for each of the following if statements, code sets corresponding nodes from adjacent tiles to the same player to be displayed on the board.
		if (node == 0)
		{

			if (row <= 2 && row != 0)
			{
				if (column == 0)
				{
					boardCoordinates[row - 1][column].setTNodes(4, player);
				}
				else if (column == (5 - abs(row - 3)))
				{
					boardCoordinates[row - 1][column - 1].setTNodes(2, player);
				}
				else
				{
					boardCoordinates[row - 1][column].setTNodes(4, player);
					boardCoordinates[row - 1][column - 1].setTNodes(2, player);
				}
			}
			if (row > 2)
			{
				if (column == 0)
				{
					boardCoordinates[row - 1][column].setTNodes(2, player);
					boardCoordinates[row - 1][column + 1].setTNodes(4, player);
				}
				else if (column == (5 - abs(row - 3)))
				{
					boardCoordinates[row - 1][column].setTNodes(2, player);
					boardCoordinates[row - 1][column + 1].setTNodes(4, player);
				}
				else
				{
					boardCoordinates[row - 1][column + 1].setTNodes(4, player);
					boardCoordinates[row - 1][column].setTNodes(2, player);
				}
			}
		}
		if (node == 1)
		{
			if (row == 0 && column != 2)
			{
				boardCoordinates[row][column + 1].setTNodes(5, player);
			}
			if (row <= 2 && row != 0)
			{
				if (column == 0)
				{
					boardCoordinates[row - 1][column].setTNodes(3, player);
				}
				else if (column == (5 - abs(row - 3)))
				{

				}
				else
				{
					boardCoordinates[row - 1][column].setTNodes(3, player);
					boardCoordinates[row][column + 1].setTNodes(5, player);
				}
			}
			if (row > 2)
			{
				if (column == 0)
				{
					boardCoordinates[row - 1][column + 1].setTNodes(3, player);
					boardCoordinates[row][column + 1].setTNodes(5, player);
				}
				else if (column == (5 - abs(row - 3)))
				{
					boardCoordinates[row - 1][column + 1].setTNodes(3, player);
				}
				else
				{
					boardCoordinates[row - 1][column + 1].setTNodes(3, player);
					boardCoordinates[row][column + 1].setTNodes(5, player);
				}
			}
		}
		if (node == 2)
		{
			if (row < 2)
			{
				if (column == 0)
				{
					boardCoordinates[row][column + 1].setTNodes(4, player);
					boardCoordinates[row + 1][column + 1].setTNodes(0, player);
				}
				else if (column == (5 - abs(row - 3)))
				{
					boardCoordinates[row + 1][column + 1].setTNodes(0, player);
				}
				else
				{
					boardCoordinates[row][column + 1].setTNodes(4, player);
					boardCoordinates[row + 1][column + 1].setTNodes(0, player);
				}
			}
			else if (row >= 2 && row != 4)
			{
				if (column == 0)
				{
					boardCoordinates[row + 1][column].setTNodes(0, player);
					boardCoordinates[row][column + 1].setTNodes(4, player);
				}
				else if (column == (5 - abs(row - 3)))
				{
				}
				else
				{
					boardCoordinates[row + 1][column].setTNodes(0, player);
					boardCoordinates[row][column + 1].setTNodes(4, player);
				}
			}
			else if (row == 4)
			{
				if (column == (5 - abs(row - 3)))
				{
				}
				else
				{
					boardCoordinates[row][column + 1].setTNodes(4, player);
				}
			}
		}
		if (node == 3)
		{
			{
				if (row < 2)
				{

					boardCoordinates[row + 1][column].setTNodes(1, player);
					boardCoordinates[row + 1][column + 1].setTNodes(5, player);

				}

				else if (row >= 2 && row != 4)
				{
					if (column == 0)
					{
						boardCoordinates[row + 1][column].setTNodes(5, player);

					}
					else if (column == (5 - abs(row - 3)))
					{
						boardCoordinates[row + 1][column - 1].setTNodes(1, player);
					}
					else
					{
						boardCoordinates[row + 1][column].setTNodes(5, player);
						boardCoordinates[row + 1][column - 1].setTNodes(1, player);
					}
				}

			}
		}
		if (node == 4)
		{
			if (row < 2)
			{
				if (column == 0)
				{
					boardCoordinates[row + 1][column].setTNodes(0, player);
				}
				else if (column == (5 - abs(row - 3)))
				{
					boardCoordinates[row + 1][column].setTNodes(0, player);
					boardCoordinates[row][column - 1].setTNodes(2, player);
				}
				else
				{
					boardCoordinates[row + 1][column].setTNodes(0, player);
					boardCoordinates[row][column - 1].setTNodes(2, player);
				}
			}
			else if (row >= 2 && row != 4)
			{
				if (column == 0)
				{

				}
				else if (column == (5 - abs(row - 3)))
				{
					boardCoordinates[row + 1][column - 1].setTNodes(0, player);
					boardCoordinates[row][column - 1].setTNodes(2, player);
				}
				else
				{
					boardCoordinates[row + 1][column - 1].setTNodes(0, player);
					boardCoordinates[row][column - 1].setTNodes(2, player);
				}
			}
			else if (row == 4)
			{
				if (column > 0)
				{
					boardCoordinates[row][column - 1].setTNodes(2, player);
				}
			}
		}
		if (node == 5)
		{
			if (row == 0)
			{
				if (column != 0)
				{
					boardCoordinates[row][column - 1].setTNodes(1, player);
				}
			}
			else if (row <= 2)
			{
				if (column == 0)
				{

				}
				else if (column == (5 - abs(row - 3)))
				{
					boardCoordinates[row][column - 1].setTNodes(1, player);
				}
				else
				{
					boardCoordinates[row][column - 1].setTNodes(1, player);
					boardCoordinates[row - 1][column - 1].setTNodes(3, player);
				}
			}
			if (row > 2)
			{
				if (column == 0)
				{
					boardCoordinates[row - 1][column].setTNodes(3, player);
				}
				else if (column == (5 - abs(row - 3)))
				{
					boardCoordinates[row - 1][column].setTNodes(3, player);
					boardCoordinates[row][column - 1].setTNodes(1, player);
				}
				else
				{
					boardCoordinates[row - 1][column].setTNodes(3, player);
					boardCoordinates[row][column - 1].setTNodes(1, player);
				}
			}
		}
	}
	else
	{
		cout << "Not a Valid Position:";
	}
}


void Board::placeCity(int player, int tile, int node)
{

	if (checkCityPlace(player, tile, node) == true) // checks if node is already assigned a player and that player is valid
	{
		char state = 'T';
		// codes does the same as placeNode but changes the nodestatus to a T instead of and H
		int row = tileToBoardCoordinates(tile).first;
		int column = tileToBoardCoordinates(tile).second;
		node--;
		boardCoordinates[row][column].setTNodes(node, player);
		if (node == 0)
		{

			if (row <= 2 && row != 0)
			{
				if (column == 0)
				{
					boardCoordinates[row - 1][column].setTNodeState(4, state);
				}
				else if (column == (5 - abs(row - 3)))
				{
					boardCoordinates[row - 1][column - 1].setTNodeState(2, state);
				}
				else
				{
					boardCoordinates[row - 1][column].setTNodeState(4, state);
					boardCoordinates[row - 1][column - 1].setTNodeState(2, state);
				}
			}
			if (row > 2)
			{
				if (column == 0)
				{
					boardCoordinates[row - 1][column].setTNodeState(2, state);
					boardCoordinates[row - 1][column + 1].setTNodeState(4, state);
				}
				else if (column == (5 - abs(row - 3)))
				{
					boardCoordinates[row - 1][column].setTNodeState(2, state);
					boardCoordinates[row - 1][column + 1].setTNodeState(4, state);
				}
				else
				{
					boardCoordinates[row - 1][column + 1].setTNodeState(4, state);
					boardCoordinates[row - 1][column].setTNodeState(2, state);
				}
			}
		}
		if (node == 1)
		{
			if (row == 0 && column != 2)
			{
				boardCoordinates[row][column + 1].setTNodeState(5, state);
			}
			if (row <= 2 && row != 0)
			{
				if (column == 0)
				{
					boardCoordinates[row - 1][column].setTNodeState(3, state);
				}
				else if (column == (5 - abs(row - 3)))
				{

				}
				else
				{
					boardCoordinates[row - 1][column].setTNodeState(3, state);
					boardCoordinates[row][column + 1].setTNodeState(5, state);
				}
			}
			if (row > 2)
			{
				if (column == 0)
				{
					boardCoordinates[row - 1][column + 1].setTNodeState(3, state);
					boardCoordinates[row][column + 1].setTNodeState(5, state);
				}
				else if (column == (5 - abs(row - 3)))
				{
					boardCoordinates[row - 1][column + 1].setTNodeState(3, state);
				}
				else
				{
					boardCoordinates[row - 1][column + 1].setTNodeState(3, state);
					boardCoordinates[row][column + 1].setTNodeState(5, state);
				}
			}
		}
		if (node == 2)
		{
			if (row < 2)
			{
				if (column == 0)
				{
					boardCoordinates[row][column + 1].setTNodeState(4, state);
					boardCoordinates[row + 1][column + 1].setTNodeState(0, state);
				}
				else if (column == (5 - abs(row - 3)))
				{
					boardCoordinates[row + 1][column + 1].setTNodeState(0, state);
				}
				else
				{
					boardCoordinates[row][column + 1].setTNodeState(4, state);
					boardCoordinates[row + 1][column + 1].setTNodeState(0, state);
				}
			}
			else if (row >= 2 && row != 4)
			{
				if (column == 0)
				{
					boardCoordinates[row + 1][column].setTNodeState(0, state);
					boardCoordinates[row][column + 1].setTNodeState(4, state);
				}
				else if (column == (5 - abs(row - 3)))
				{
				}
				else
				{
					boardCoordinates[row + 1][column].setTNodeState(0, state);
					boardCoordinates[row][column + 1].setTNodeState(4, state);
				}
			}
			else if (row == 4)
			{
				if (column == (5 - abs(row - 3)))
				{
				}
				else
				{
					boardCoordinates[row][column + 1].setTNodeState(4, state);
				}
			}
		}
		if (node == 3)
		{
			{
				if (row < 2)
				{

					boardCoordinates[row + 1][column].setTNodeState(1, state);
					boardCoordinates[row + 1][column + 1].setTNodeState(5, state);

				}

				else if (row >= 2 && row != 4)
				{
					if (column == 0)
					{
						boardCoordinates[row + 1][column].setTNodeState(5, state);

					}
					else if (column == (5 - abs(row - 3)))
					{
						boardCoordinates[row + 1][column - 1].setTNodeState(1, state);
					}
					else
					{
						boardCoordinates[row + 1][column].setTNodeState(5, state);
						boardCoordinates[row + 1][column - 1].setTNodeState(1, state);
					}
				}

			}
		}
		if (node == 4)
		{
			if (row < 2)
			{
				if (column == 0)
				{
					boardCoordinates[row + 1][column].setTNodeState(0, state);
				}
				else if (column == (5 - abs(row - 3)))
				{
					boardCoordinates[row + 1][column].setTNodeState(0, state);
					boardCoordinates[row][column - 1].setTNodeState(2, state);
				}
				else
				{
					boardCoordinates[row + 1][column].setTNodeState(0, state);
					boardCoordinates[row][column - 1].setTNodeState(2, state);
				}
			}
			else if (row >= 2 && row != 4)
			{
				if (column == 0)
				{

				}
				else if (column == (5 - abs(row - 3)))
				{
					boardCoordinates[row + 1][column - 1].setTNodeState(0, state);
					boardCoordinates[row][column - 1].setTNodeState(2, state);
				}
				else
				{
					boardCoordinates[row + 1][column - 1].setTNodeState(0, state);
					boardCoordinates[row][column - 1].setTNodeState(2, state);
				}
			}
			else if (row == 4)
			{
				if (column > 0)
				{
					boardCoordinates[row][column - 1].setTNodeState(2, state);
				}
			}
		}
		if (node == 5)
		{
			if (row == 0)
			{
				if (column != 0)
				{
					boardCoordinates[row][column - 1].setTNodeState(1, state);
				}
			}
			else if (row <= 2)
			{
				if (column == 0)
				{

				}
				else if (column == (5 - abs(row - 3)))
				{
					boardCoordinates[row][column - 1].setTNodeState(1, state);
				}
				else
				{
					boardCoordinates[row][column - 1].setTNodeState(1, state);
					boardCoordinates[row - 1][column - 1].setTNodeState(3, state);
				}
			}
			if (row > 2)
			{
				if (column == 0)
				{
					boardCoordinates[row - 1][column].setTNodeState(3, state);
				}
				else if (column == (5 - abs(row - 3)))
				{
					boardCoordinates[row - 1][column].setTNodeState(3, state);
					boardCoordinates[row][column - 1].setTNodeState(1, state);
				}
				else
				{
					boardCoordinates[row - 1][column].setTNodeState(3, state);
					boardCoordinates[row][column - 1].setTNodeState(1, state);
				}
			}
		}
	}
	else
	{
		cout << "Not a Valid Position:";
	}
}

bool Board::checkNodePlace(int player, int tile, int node)
{
	node--;
	tile--;
	if (node < 0 || node > 5 || tile < 0 || tile > 18) // checks for valid index
	{
		return false;
	}
	if (*nodeReferenceCoordinates[tile][node] == player) // checks if node is already assigned
	{
		return false;
	}
	if (*nodeReferenceCoordinates[tile][node] != -1 || *nodeReferenceCoordinates[tile][node] == -2) // checks if node is vacant and is not too close to another node
	{
		return false;
	}
	// converts to array indexes
	int row = tileToBoardCoordinates(tile).first;
	int column = tileToBoardCoordinates(tile).second;

	if (*sideAddressCoordinates[tile][node] == player || *sideAddressCoordinates[tile][((node)+5) % 6] == player) // checks if a road is adjacent to a tile
	{
		return true;
	}
	return false;
}

bool Board::checkCityPlace(int player, int tile, int node)
{
	node--;
	tile--;
	if (node < 0 || node > 5 || tile < 0 || tile > 18) // checks if valid position
	{
		return false;
	}
	if (*nodeReferenceCoordinates[tile][node] == player) // checks if player already own the node
	{
		return true;
	}
	if (*nodeReferenceCoordinates[tile][node] != -1 || *nodeReferenceCoordinates[tile][node] == -2) // checks if the node is unclaimed 
	{
		return false;
	}
	
	return false;
}

// looked like a switch could clean this one up too
void Board::placeFirstNode(int player, int tile, int node)
{
	//same code as place node but without checking if there are roads connecting yet
	if (checkFirstNodePlace(player, tile, node) == true)
	{
		int row = tileToBoardCoordinates(tile).first;
		int column = tileToBoardCoordinates(tile).second;
		node--;
		boardCoordinates[row][column].setTNodes(node, player);
		if (node == 0)
		{

			if (row <= 2 && row != 0)
			{
				if (column == 0)
				{
					boardCoordinates[row - 1][column].setTNodes(4, player);
				}
				else if (column == (5 - abs(row - 3)))
				{
					boardCoordinates[row - 1][column - 1].setTNodes(2, player);
				}
				else
				{
					boardCoordinates[row - 1][column].setTNodes(4, player);
					boardCoordinates[row - 1][column - 1].setTNodes(2, player);
				}
			}
			if (row > 2)
			{
				if (column == 0)
				{
					boardCoordinates[row - 1][column].setTNodes(2, player);
					boardCoordinates[row - 1][column + 1].setTNodes(4, player);
				}
				else if (column == (5 - abs(row - 3)))
				{
					boardCoordinates[row - 1][column].setTNodes(2, player);
					boardCoordinates[row - 1][column + 1].setTNodes(4, player);
				}
				else
				{
					boardCoordinates[row - 1][column + 1].setTNodes(4, player);
					boardCoordinates[row - 1][column].setTNodes(2, player);
				}
			}
		}
		if (node == 1)
		{
			if (row == 0 && column != 2)
			{
				boardCoordinates[row][column + 1].setTNodes(5, player);
			}
			if (row <= 2 && row != 0)
			{
				if (column == 0)
				{
					boardCoordinates[row - 1][column].setTNodes(3, player);
				}
				else if (column == (5 - abs(row - 3)))
				{

				}
				else
				{
					boardCoordinates[row - 1][column].setTNodes(3, player);
					boardCoordinates[row][column + 1].setTNodes(5, player);
				}
			}
			if (row > 2)
			{
				if (column == 0)
				{
					boardCoordinates[row - 1][column + 1].setTNodes(3, player);
					boardCoordinates[row][column + 1].setTNodes(5, player);
				}
				else if (column == (5 - abs(row - 3)))
				{
					boardCoordinates[row - 1][column + 1].setTNodes(3, player);
				}
				else
				{
					boardCoordinates[row - 1][column + 1].setTNodes(3, player);
					boardCoordinates[row][column + 1].setTNodes(5, player);
				}
			}
		}
		if (node == 2)
		{
			if (row < 2)
			{
				if (column == 0)
				{
					boardCoordinates[row][column + 1].setTNodes(4, player);
					boardCoordinates[row + 1][column + 1].setTNodes(0, player);
				}
				else if (column == (5 - abs(row - 3)))
				{
					boardCoordinates[row + 1][column + 1].setTNodes(0, player);
				}
				else
				{
					boardCoordinates[row][column + 1].setTNodes(4, player);
					boardCoordinates[row + 1][column + 1].setTNodes(0, player);
				}
			}
			else if (row >= 2 && row != 4)
			{
				if (column == 0)
				{
					boardCoordinates[row + 1][column].setTNodes(0, player);
					boardCoordinates[row][column + 1].setTNodes(4, player);
				}
				else if (column == (5 - abs(row - 3)))
				{
				}
				else
				{
					boardCoordinates[row + 1][column].setTNodes(0, player);
					boardCoordinates[row][column + 1].setTNodes(4, player);
				}
			}
			else if (row == 4)
			{
				if (column == (5 - abs(row - 3)))
				{
				}
				else
				{
					boardCoordinates[row][column + 1].setTNodes(4, player);
				}
			}
		}
		if (node == 3)
		{
			{
				if (row < 2)
				{

					boardCoordinates[row + 1][column].setTNodes(1, player);
					boardCoordinates[row + 1][column + 1].setTNodes(5, player);

				}

				else if (row >= 2 && row != 4)
				{
					if (column == 0)
					{
						boardCoordinates[row + 1][column].setTNodes(5, player);

					}
					else if (column == (5 - abs(row - 3)))
					{
						boardCoordinates[row + 1][column - 1].setTNodes(1, player);
					}
					else
					{
						boardCoordinates[row + 1][column].setTNodes(5, player);
						boardCoordinates[row + 1][column - 1].setTNodes(1, player);
					}
				}

			}
		}
		if (node == 4)
		{
			if (row < 2)
			{
				if (column == 0)
				{
					boardCoordinates[row + 1][column].setTNodes(0, player);
				}
				else if (column == (5 - abs(row - 3)))
				{
					boardCoordinates[row + 1][column].setTNodes(0, player);
					boardCoordinates[row][column - 1].setTNodes(2, player);
				}
				else
				{
					boardCoordinates[row + 1][column].setTNodes(0, player);
					boardCoordinates[row][column - 1].setTNodes(2, player);
				}
			}
			else if (row >= 2 && row != 4)
			{
				if (column == 0)
				{

				}
				else if (column == (5 - abs(row - 3)))
				{
					boardCoordinates[row + 1][column - 1].setTNodes(0, player);
					boardCoordinates[row][column - 1].setTNodes(2, player);
				}
				else
				{
					boardCoordinates[row + 1][column - 1].setTNodes(0, player);
					boardCoordinates[row][column - 1].setTNodes(2, player);
				}
			}
			else if (row == 4)
			{
				if (column > 0)
				{
					boardCoordinates[row][column - 1].setTNodes(2, player);
				}
			}
		}
		if (node == 5)
		{
			if (row == 0)
			{
				if (column != 0)
				{
					boardCoordinates[row][column - 1].setTNodes(1, player);
				}
			}
			else if (row <= 2)
			{
				if (column == 0)
				{

				}
				else if (column == (5 - abs(row - 3)))
				{
					boardCoordinates[row][column - 1].setTNodes(1, player);
				}
				else
				{
					boardCoordinates[row][column - 1].setTNodes(1, player);
					boardCoordinates[row - 1][column - 1].setTNodes(3, player);
				}
			}
			if (row > 2)
			{
				if (column == 0)
				{
					boardCoordinates[row - 1][column].setTNodes(3, player);
				}
				else if (column == (5 - abs(row - 3)))
				{
					boardCoordinates[row - 1][column].setTNodes(3, player);
					boardCoordinates[row][column - 1].setTNodes(1, player);
				}
				else
				{
					boardCoordinates[row - 1][column].setTNodes(3, player);
					boardCoordinates[row][column - 1].setTNodes(1, player);
				}
			}
		}
	}
	else
	{
		cout << "Not a Valid Position:";
	}
}

bool Board::checkFirstNodePlace(int player, int tile, int node)
{
	// does not need to have a road adjacent to the node
	node--;
	tile--;
	if (node < 0 || node > 5 || tile < 0 || tile > 18)
	{
		return false;
	}
	if (*nodeReferenceCoordinates[tile][node] != -1 || *nodeReferenceCoordinates[tile][node] == -2)
	{
		return false;
	}

	return true;
}