#include <iostream>
#include "Board.h"
#include <stdlib.h>
#include "Player.h"
#include <ctime>
#include "Tile.h"
#include <fstream>
using namespace std;

int diceRoll();
void saveGame(int players, Player playerArray[], Board &b1);
void loadGame(int &players, Player playerArray[], Board &b1);
void playGame();

int main()
{
	playGame();
}


int diceRoll()
{
	srand(time(NULL));
	return ((rand() % 6) + 1) + ((rand() % 6) + 1); // Dice 1 + Dice 2
}
void saveGame(int players, Player playerArray[], Board &b1)
{
	//Records attributes of the board and players
	ofstream fout;
	fout.open("Save.txt");
	if (fout.fail()) { cerr << "Error Opening File" << endl; exit(1); }
	fout.clear();
	fout << players << endl;
	for (int row = 0; row < 5; row++)
	{
		for (int column = 0; column < 5 - abs(2 - row); column++) //goes through the 5 by 5 array of tiles in Board
		{
			fout << b1.boardCoordinates[row][column].getTType() << endl;
			fout << b1.boardCoordinates[row][column].getTValue() << endl;
			for (int node = 1; node <= 6; node++)
			{
				fout << b1.boardCoordinates[row][column].getTNode(node) << endl;
				fout << b1.boardCoordinates[row][column].getTNodeState(node) << endl;
				fout << b1.boardCoordinates[row][column].getTSide(node) << endl;
			}

		}
	}
	for (int p = 0; p < players; p++) // gets player data
	{
		fout << playerArray[p].getClay() << endl;
		fout << playerArray[p].getWood() << endl;
		fout << playerArray[p].getWheat() << endl;
		fout << playerArray[p].getOre() << endl;
		fout << playerArray[p].getSheep() << endl;
		fout << playerArray[p].getPlayerScore() << endl;
	}
	fout.close();
}
void loadGame(int &players, Player playerArray[], Board &b1)
{
	// same as the save game function but uses manipulator functions instead of accessors to set board data how it was saved.
	ifstream fin;
	fin.open("Save.txt");

	if (fin.fail()) { cerr << "Error Opening File" << endl; exit(1); }
	fin >> players;
	for (int row = 0; row < 5; row++)
	{
		for (int column = 0; column < 5 - abs(2 - row); column++)
		{
			char x;
			int y;
			fin >> x;  b1.boardCoordinates[row][column].setTType(x);
			fin >> y; b1.boardCoordinates[row][column].setTValue(y);
			for (int node = 1; node <= 6; node++)
			{
				fin >> y; b1.boardCoordinates[row][column].setTNodesForSave(node - 1, y);
				fin >> x; b1.boardCoordinates[row][column].setTNodeState(node - 1, x);
				fin >> y; b1.boardCoordinates[row][column].setTSide(node - 1, y);
			}

		}
	}
	for (int p = 0; p < players; p++)
	{
		int count;
		fin >> count; playerArray[p].changeClay(count);
		fin >> count; playerArray[p].changeWood(count);
		fin >> count; playerArray[p].changeWheat(count);
		fin >> count; playerArray[p].changeOre(count);
		fin >> count; playerArray[p].changeSheep(count);
		fin >> count; playerArray[p].changeScore(count);
	}
	fin.close();
}
void playGame()
{
	int players;
	bool valid = false;
	cout << "Welcome to Settlers of Catron.\nNew game or Load Game? (n,l)\n";
	char newOrLoad;
	do
	{
		cin >> newOrLoad;
	} while (newOrLoad != 'n' && newOrLoad != 'N' && newOrLoad != 'l' && newOrLoad != 'L');
	Board b1(0);
	Player *playerArray;
	// Code to start a new game
	if (newOrLoad == 'n' || newOrLoad == 'N')
	{
		do
		{
			cout << "Please enter how many players are present (2-4):";
			cin >> players;
			if (players < 2)
			{
				cout << "Well that's quite lonely, come back when you have friends :(\n";
				valid = false;
			}
			else if (players > 4)
			{
				cout << "This party is too much for Settlers of Catron, please dispose of extra players :D \n";
				valid = false;
			}
			else
				valid = true;
		} while (valid != true);
		playerArray = new Player[players]; // creates an array dependent on how many players are selected
		system("CLS");
		b1.displayBoard();
		// Code below allows players to set up there first houses/settlements when the game starts. Every player will put down 1 house and 1 road
		for (int i = 0; i < players; i++)
		{
			cout << "Player " << i + 1 << "'s turn!\n";
			int tile;
			int node;
			do {
				cout << "Please place your first house.\n Tile #:";

				cin >> tile;

				cout << "Node #:";

				cin >> node;

			} while (b1.checkFirstNodePlace(i + 1, tile, node) != true);
			b1.placeFirstNode(i + 1, tile, node);
			b1.displayBoard();
			cout << "Player " << i + 1 << "'s turn!\n";
			int rTile;
			int rSide;
			do {
				cout << "Please place your first road.\n Tile #:";

				cin >> rTile;

				cout << "Side #:";
				cin >> rSide;
			} while (b1.checkRoadPlace(i + 1, rTile - 1, rSide - 1) != true);
			b1.placeRoad(i + 1, rTile, rSide);
			b1.displayBoard();

		}
		// Code continues to allow players to set second house and second road
		for (int i = players - 1; i >= 0; i--)
		{
			cout << "Player " << i + 1 << "'s turn!\n";
			int tile;
			int node;
			do {
				cout << "Please place your second house.\n Tile #:";
				cin >> tile;
				cout << "Node #:";
				cin >> node;
			} while (b1.checkFirstNodePlace(i + 1, tile, node) != true);
			b1.placeFirstNode(i + 1, tile, node);
			b1.displayBoard();
			cout << "Player " << i + 1 << "'s turn!\n";
			int rTile;
			int rSide;
			do {
				cout << "Please place your second road.\n Tile #:";
				cin >> rTile;
				cout << "Side #:";
				cin >> rSide;
			} while (b1.checkRoadPlace(i + 1, rTile - 1, rSide - 1) != true);
			b1.placeRoad(i + 1, rTile, rSide);
			b1.displayBoard();

		}
	}
	// Code to load a saved game
	else
	{
		ifstream fin;
		fin.open("Save.txt");

		if (fin.fail()) { cerr << "Error Opening File" << endl; exit(1); }
		fin >> players;
		playerArray = new Player[players];
		loadGame(players, playerArray, b1);
	}

	b1.changePlayerCount(players);

	static int counter = 0;
	system("CLS");
	do
	{
		b1.displayBoard();
		int currentPlayer = counter % players; // cycles from first player to last player in a continuous loop ( to be used for turns)
		int roll = diceRoll();
		cout << "The dice gods have given you a " << roll << "!\n";
		// gives out resources for all players
		if (roll != 7)
		{
			for (int playerID = 1; playerID <= players; playerID++)
			{
				for (int tiles = 0; tiles < 19; tiles++)
				{
					int row = b1.tileToBoardCoordinates(tiles + 1).first;
					int column = b1.tileToBoardCoordinates(tiles + 1).second;
					if (b1.returnTileValue(row, column) == roll && b1.returnRobber(row, column) != true)
					{
						for (int node = 1; node <= 6; node++)
						{
							if (playerID == b1.returnPlayerPosition(row, column, node))
							{
								int add;
								if (b1.returnPlayerHouse(row, column, node) == 'H') // for house
									add = 1;
								if (b1.returnPlayerHouse(row, column, node) == 'T') // for town
									add = 2;
								if (b1.returnTileType(row, column) == 'T')
									playerArray[playerID - 1].changeWood(add);
								if (b1.returnTileType(row, column) == 'W')
									playerArray[playerID - 1].changeWheat(add);
								if (b1.returnTileType(row, column) == 'O')
									playerArray[playerID - 1].changeOre(add);
								if (b1.returnTileType(row, column) == 'B')
									playerArray[playerID - 1].changeClay(add);
								if (b1.returnTileType(row, column) == 'G')
									playerArray[playerID - 1].changeSheep(add);
							}
						}
					}
				}
			}
		}
		// If a theif is rolled, use this code. Checks players if cards > 7 and if so, randomly discard half. Player's turn who rolled 7 gets to assign theif to new tile
		else
		{
			cout << "A theif has come to your lands and robbed the wealthy of their goods!\n";
			for (int playerID = 0; playerID < players; playerID++)
			{
				int cardTotal = playerArray[playerID].getClay() + playerArray[playerID].getWood() + playerArray[playerID].getWheat() + playerArray[playerID].getOre() + playerArray[playerID].getSheep();
				if (cardTotal > 7)
				{
					int halfOfCards = cardTotal / 2;
					for (int i = 0; i < halfOfCards; i)
					{
						int randomCardSelection = rand() % 5;
						if (randomCardSelection == 0 && playerArray[playerID].getClay() != 0)
						{
							playerArray[playerID].changeClay(-1);
							i++;
						}
						if (randomCardSelection == 1 && playerArray[playerID].getWood() != 0)
						{
							playerArray[playerID].changeWood(-1);
							i++;
						}
						if (randomCardSelection == 2 && playerArray[playerID].getWheat() != 0)
						{
							playerArray[playerID].changeWheat(-1);
							i++;
						}
						if (randomCardSelection == 3 && playerArray[playerID].getOre() != 0)
						{
							playerArray[playerID].changeOre(-1);
							i++;
						}
						if (randomCardSelection == 4 && playerArray[playerID].getSheep() != 0)
						{
							playerArray[playerID].changeSheep(-1);
							i++;
						}
					}
				}
			}
			cout << "Please move the Theif Tile:\n Tile #: ";
			int tile;
			cin >> tile;
			b1.setRobber(tile);
			system("CLS");
			b1.displayBoard();
		}

		int option;

		do {

			b1.displayBoard(); // displays dice, player hand, and player options
			cout << "The dice gods have given you a " << roll << "!\n";
			cout << "Wood = " << playerArray[currentPlayer].getWood() << "    Wheat = " << playerArray[currentPlayer].getWheat() << "    Ore = " << playerArray[currentPlayer].getOre() << "    Clay = " << playerArray[currentPlayer].getClay() << "    Sheep = " << playerArray[currentPlayer].getSheep() << endl;
			cout << "What would you like to do?\n";
			cout << "1) Buy Road\n2) Buy House\n3) Buy Town\n0) End Turn\n";
			cin >> option;
			if (option == 1)
			{
				if (playerArray[currentPlayer].getWood() > 0 && playerArray[currentPlayer].getClay() > 0)
				{

					int rTile;
					int rSide;
					do {
						cout << "Please place your road.\n Tile #:";
						cin >> rTile;
						cout << "Side #:";
						cin >> rSide;
					} while (b1.checkRoadPlace(currentPlayer + 1, rTile - 1, rSide - 1) != true);
					b1.placeRoad(currentPlayer + 1, rTile, rSide);
					playerArray[currentPlayer].changeWood(-1);
					playerArray[currentPlayer].changeClay(-1);
				}
				else
				{
					cout << "Sorry, you do not have enough resources for this T-T\n";
				}
			}
			if (option == 2)
			{
				if (playerArray[currentPlayer].getWood() > 0 && playerArray[currentPlayer].getWheat() > 0 && playerArray[currentPlayer].getSheep() > 0 && playerArray[currentPlayer].getClay() > 0)
				{

					int tile;
					int node;
					do {
						cout << "Please place your settlement.\n Tile #:";
						cin >> tile;
						cout << "Node #:";
						cin >> node;
					} while (b1.checkFirstNodePlace(currentPlayer + 1, tile, node) != true);
					b1.placeNode(currentPlayer + 1, tile, node);
					playerArray[currentPlayer].changeWood(-1);
					playerArray[currentPlayer].changeClay(-1);
					playerArray[currentPlayer].changeWheat(-1);
					playerArray[currentPlayer].changeSheep(-1);

				}
				else
				{
					cout << "Sorry, you do not have enough resources for this T-T\n";
				}
			}
			if (option == 3)
			{
				if (playerArray[currentPlayer].getWheat() > 1 && playerArray[currentPlayer].getOre() > 2)
				{


					int tile;
					int node;
					do {
						cout << "Please place your City.\n Tile #:";
						cin >> tile;
						cout << "Node #:";
						cin >> node;
					} while (b1.checkCityPlace(currentPlayer + 1, tile, node) != true);
					b1.placeCity(currentPlayer + 1, tile, node);
					playerArray[currentPlayer].changeWheat(-2);
					playerArray[currentPlayer].changeOre(-3);
				}
				else
				{
					cout << "Sorry, you do not have enough resources for this T-T\n";
				}
			}
			system("CLS");
		} while (option != 0);
		counter++;
		cout << "Is player " << counter % players + 1 << " ready? (y)\n";
		char ready;
		do
		{
			cin >> ready;
		} while (ready != 'y' && ready != 'Y');
		saveGame(players, playerArray, b1);
	} while (playerArray[counter % players].getPlayerScore() < 10); // Until a player wins (no scoring system impemented yet since points can be obtained in more ways than that has been coded.

}