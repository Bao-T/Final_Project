#pragma once
#include <iostream>
#include <Windows.h>
#include "Tile.h"
#include <ctime>
#include <stdlib.h>
#include <iomanip>
using namespace std;
class Board {
private:
	
	// a massive headache of a coordinate system to keep track of sides.
	int *sideAddressCoordinates[19][6] =
	{ { boardCoordinates[0][0].tSideAddress(0),boardCoordinates[0][0].tSideAddress(1),boardCoordinates[0][0].tSideAddress(2),boardCoordinates[0][0].tSideAddress(3),boardCoordinates[0][0].tSideAddress(4),boardCoordinates[0][0].tSideAddress(5) }, // Tile 1
	{ boardCoordinates[0][1].tSideAddress(0),boardCoordinates[0][1].tSideAddress(1),boardCoordinates[0][1].tSideAddress(2),boardCoordinates[0][1].tSideAddress(3),boardCoordinates[0][1].tSideAddress(4),boardCoordinates[0][1].tSideAddress(5) },
	{ boardCoordinates[0][2].tSideAddress(0),boardCoordinates[0][2].tSideAddress(1),boardCoordinates[0][2].tSideAddress(2),boardCoordinates[0][2].tSideAddress(3),boardCoordinates[0][2].tSideAddress(4),boardCoordinates[0][2].tSideAddress(5) },
	{ boardCoordinates[1][0].tSideAddress(0),boardCoordinates[1][0].tSideAddress(1),boardCoordinates[1][0].tSideAddress(2),boardCoordinates[1][0].tSideAddress(3),boardCoordinates[1][0].tSideAddress(4),boardCoordinates[1][0].tSideAddress(5) },
	{ boardCoordinates[1][1].tSideAddress(0),boardCoordinates[1][1].tSideAddress(1),boardCoordinates[1][1].tSideAddress(2),boardCoordinates[1][1].tSideAddress(3),boardCoordinates[1][1].tSideAddress(4),boardCoordinates[1][1].tSideAddress(5) },
	{ boardCoordinates[1][2].tSideAddress(0),boardCoordinates[1][2].tSideAddress(1),boardCoordinates[1][2].tSideAddress(2),boardCoordinates[1][2].tSideAddress(3),boardCoordinates[1][2].tSideAddress(4),boardCoordinates[1][2].tSideAddress(5) },
	{ boardCoordinates[1][3].tSideAddress(0),boardCoordinates[1][3].tSideAddress(1),boardCoordinates[1][3].tSideAddress(2),boardCoordinates[1][3].tSideAddress(3),boardCoordinates[1][3].tSideAddress(4),boardCoordinates[1][3].tSideAddress(5) },
	{ boardCoordinates[2][0].tSideAddress(0),boardCoordinates[2][0].tSideAddress(1),boardCoordinates[2][0].tSideAddress(2),boardCoordinates[2][0].tSideAddress(3),boardCoordinates[2][0].tSideAddress(4),boardCoordinates[2][0].tSideAddress(5) },
	{ boardCoordinates[2][1].tSideAddress(0),boardCoordinates[2][1].tSideAddress(1),boardCoordinates[2][1].tSideAddress(2),boardCoordinates[2][1].tSideAddress(3),boardCoordinates[2][1].tSideAddress(4),boardCoordinates[2][1].tSideAddress(5) },
	{ boardCoordinates[2][2].tSideAddress(0),boardCoordinates[2][2].tSideAddress(1),boardCoordinates[2][2].tSideAddress(2),boardCoordinates[2][2].tSideAddress(3),boardCoordinates[2][2].tSideAddress(4),boardCoordinates[2][2].tSideAddress(5) },
	{ boardCoordinates[2][3].tSideAddress(0),boardCoordinates[2][3].tSideAddress(1),boardCoordinates[2][3].tSideAddress(2),boardCoordinates[2][3].tSideAddress(3),boardCoordinates[2][3].tSideAddress(4),boardCoordinates[2][3].tSideAddress(5) },
	{ boardCoordinates[2][4].tSideAddress(0),boardCoordinates[2][4].tSideAddress(1),boardCoordinates[2][4].tSideAddress(2),boardCoordinates[2][4].tSideAddress(3),boardCoordinates[2][4].tSideAddress(4),boardCoordinates[2][4].tSideAddress(5) },
	{ boardCoordinates[3][0].tSideAddress(0),boardCoordinates[3][0].tSideAddress(1),boardCoordinates[3][0].tSideAddress(2),boardCoordinates[3][0].tSideAddress(3),boardCoordinates[3][0].tSideAddress(4),boardCoordinates[3][0].tSideAddress(5) },
	{ boardCoordinates[3][1].tSideAddress(0),boardCoordinates[3][1].tSideAddress(1),boardCoordinates[3][1].tSideAddress(2),boardCoordinates[3][1].tSideAddress(3),boardCoordinates[3][1].tSideAddress(4),boardCoordinates[3][1].tSideAddress(5) },
	{ boardCoordinates[3][2].tSideAddress(0),boardCoordinates[3][2].tSideAddress(1),boardCoordinates[3][2].tSideAddress(2),boardCoordinates[3][2].tSideAddress(3),boardCoordinates[3][2].tSideAddress(4),boardCoordinates[3][2].tSideAddress(5) },
	{ boardCoordinates[3][3].tSideAddress(0),boardCoordinates[3][3].tSideAddress(1),boardCoordinates[3][3].tSideAddress(2),boardCoordinates[3][3].tSideAddress(3),boardCoordinates[3][3].tSideAddress(4),boardCoordinates[3][3].tSideAddress(5) },
	{ boardCoordinates[4][0].tSideAddress(0),boardCoordinates[4][0].tSideAddress(1),boardCoordinates[4][0].tSideAddress(2),boardCoordinates[4][0].tSideAddress(3),boardCoordinates[4][0].tSideAddress(4),boardCoordinates[4][0].tSideAddress(5) },
	{ boardCoordinates[4][1].tSideAddress(0),boardCoordinates[4][1].tSideAddress(1),boardCoordinates[4][1].tSideAddress(2),boardCoordinates[4][1].tSideAddress(3),boardCoordinates[4][1].tSideAddress(4),boardCoordinates[4][1].tSideAddress(5) },
	{ boardCoordinates[4][2].tSideAddress(0),boardCoordinates[4][2].tSideAddress(1),boardCoordinates[4][2].tSideAddress(2),boardCoordinates[4][2].tSideAddress(3),boardCoordinates[4][2].tSideAddress(4),boardCoordinates[4][2].tSideAddress(5)} }; // Tile 19
	// a massive headache of a coordinate system to keep track of nodes.
	int *nodeReferenceCoordinates[19][6] =
	{ { boardCoordinates[0][0].tNodeAddress(0),boardCoordinates[0][0].tNodeAddress(1),boardCoordinates[0][0].tNodeAddress(2),boardCoordinates[0][0].tNodeAddress(3),boardCoordinates[0][0].tNodeAddress(4),boardCoordinates[0][0].tNodeAddress(5) }, // Tile 1
	{ boardCoordinates[0][1].tNodeAddress(0),boardCoordinates[0][1].tNodeAddress(1),boardCoordinates[0][1].tNodeAddress(2),boardCoordinates[0][1].tNodeAddress(3),boardCoordinates[0][1].tNodeAddress(4),boardCoordinates[0][1].tNodeAddress(5) },
	{ boardCoordinates[0][2].tNodeAddress(0),boardCoordinates[0][2].tNodeAddress(1),boardCoordinates[0][2].tNodeAddress(2),boardCoordinates[0][2].tNodeAddress(3),boardCoordinates[0][2].tNodeAddress(4),boardCoordinates[0][2].tNodeAddress(5) },
	{ boardCoordinates[1][0].tNodeAddress(0),boardCoordinates[1][0].tNodeAddress(1),boardCoordinates[1][0].tNodeAddress(2),boardCoordinates[1][0].tNodeAddress(3),boardCoordinates[1][0].tNodeAddress(4),boardCoordinates[1][0].tNodeAddress(5) },
	{ boardCoordinates[1][1].tNodeAddress(0),boardCoordinates[1][1].tNodeAddress(1),boardCoordinates[1][1].tNodeAddress(2),boardCoordinates[1][1].tNodeAddress(3),boardCoordinates[1][1].tNodeAddress(4),boardCoordinates[1][1].tNodeAddress(5) },
	{ boardCoordinates[1][2].tNodeAddress(0),boardCoordinates[1][2].tNodeAddress(1),boardCoordinates[1][2].tNodeAddress(2),boardCoordinates[1][2].tNodeAddress(3),boardCoordinates[1][2].tNodeAddress(4),boardCoordinates[1][2].tNodeAddress(5) },
	{ boardCoordinates[1][3].tNodeAddress(0),boardCoordinates[1][3].tNodeAddress(1),boardCoordinates[1][3].tNodeAddress(2),boardCoordinates[1][3].tNodeAddress(3),boardCoordinates[1][3].tNodeAddress(4),boardCoordinates[1][3].tNodeAddress(5) },
	{ boardCoordinates[2][0].tNodeAddress(0),boardCoordinates[2][0].tNodeAddress(1),boardCoordinates[2][0].tNodeAddress(2),boardCoordinates[2][0].tNodeAddress(3),boardCoordinates[2][0].tNodeAddress(4),boardCoordinates[2][0].tNodeAddress(5) },
	{ boardCoordinates[2][1].tNodeAddress(0),boardCoordinates[2][1].tNodeAddress(1),boardCoordinates[2][1].tNodeAddress(2),boardCoordinates[2][1].tNodeAddress(3),boardCoordinates[2][1].tNodeAddress(4),boardCoordinates[2][1].tNodeAddress(5) },
	{ boardCoordinates[2][2].tNodeAddress(0),boardCoordinates[2][2].tNodeAddress(1),boardCoordinates[2][2].tNodeAddress(2),boardCoordinates[2][2].tNodeAddress(3),boardCoordinates[2][2].tNodeAddress(4),boardCoordinates[2][2].tNodeAddress(5) },
	{ boardCoordinates[2][3].tNodeAddress(0),boardCoordinates[2][3].tNodeAddress(1),boardCoordinates[2][3].tNodeAddress(2),boardCoordinates[2][3].tNodeAddress(3),boardCoordinates[2][3].tNodeAddress(4),boardCoordinates[2][3].tNodeAddress(5) },
	{ boardCoordinates[2][4].tNodeAddress(0),boardCoordinates[2][4].tNodeAddress(1),boardCoordinates[2][4].tNodeAddress(2),boardCoordinates[2][4].tNodeAddress(3),boardCoordinates[2][4].tNodeAddress(4),boardCoordinates[2][4].tNodeAddress(5) },
	{ boardCoordinates[3][0].tNodeAddress(0),boardCoordinates[3][0].tNodeAddress(1),boardCoordinates[3][0].tNodeAddress(2),boardCoordinates[3][0].tNodeAddress(3),boardCoordinates[3][0].tNodeAddress(4),boardCoordinates[3][0].tNodeAddress(5) },
	{ boardCoordinates[3][1].tNodeAddress(0),boardCoordinates[3][1].tNodeAddress(1),boardCoordinates[3][1].tNodeAddress(2),boardCoordinates[3][1].tNodeAddress(3),boardCoordinates[3][1].tNodeAddress(4),boardCoordinates[3][1].tNodeAddress(5) },
	{ boardCoordinates[3][2].tNodeAddress(0),boardCoordinates[3][2].tNodeAddress(1),boardCoordinates[3][2].tNodeAddress(2),boardCoordinates[3][2].tNodeAddress(3),boardCoordinates[3][2].tNodeAddress(4),boardCoordinates[3][2].tNodeAddress(5) },
	{ boardCoordinates[3][3].tNodeAddress(0),boardCoordinates[3][3].tNodeAddress(1),boardCoordinates[3][3].tNodeAddress(2),boardCoordinates[3][3].tNodeAddress(3),boardCoordinates[3][3].tNodeAddress(4),boardCoordinates[3][3].tNodeAddress(5) },
	{ boardCoordinates[4][0].tNodeAddress(0),boardCoordinates[4][0].tNodeAddress(1),boardCoordinates[4][0].tNodeAddress(2),boardCoordinates[4][0].tNodeAddress(3),boardCoordinates[4][0].tNodeAddress(4),boardCoordinates[4][0].tNodeAddress(5) },
	{ boardCoordinates[4][1].tNodeAddress(0),boardCoordinates[4][1].tNodeAddress(1),boardCoordinates[4][1].tNodeAddress(2),boardCoordinates[4][1].tNodeAddress(3),boardCoordinates[4][1].tNodeAddress(4),boardCoordinates[4][1].tNodeAddress(5) },
	{ boardCoordinates[4][2].tNodeAddress(0),boardCoordinates[4][2].tNodeAddress(1),boardCoordinates[4][2].tNodeAddress(2),boardCoordinates[4][2].tNodeAddress(3),boardCoordinates[4][2].tNodeAddress(4),boardCoordinates[4][2].tNodeAddress(5) } }; // Tile 19
	// the number of players inhabiting the board.
	int playerCount = 0;

public:
	Tile boardCoordinates[5][5];

	// constructor that takes in a number of players to initialize the board.
	Board(int p);

	void displayBoard();

	////——————————————Accessors
	/**/int returnPlayerPosition(int row, int column, int node);
	/**/int returnTileValue(int row, int column);
	/**/char returnPlayerHouse(int row, int column, int node);
	/**/char returnTileType(int row, int column);
	/**/bool returnRobber(int row, int column);
	////———————————————————————

	// pseudo-randomly assigns the tiles of the board their type (sheep/brick/wood/ore/wheat) and value (2-12).\
	Assigns one tile the designation "Desert," and sets that tile to start with the Thief.
	void setBoard();

	// might not even be a necessary function
	void changePlayerCount(int x);

	// assigns color to the player based upon their int value (1-4)
	void colorPlayer(char text, int player);

	// assigns color to the tile based upon the tile's resource type (sheep/brick/wood/ore/wheat)
	void colorTile(char type);

	// takes in a tile, returns coordinates that correspond to boardCoordinates
	pair<int, int> tileToBoardCoordinates(int tile);

	// allows a given player to claim a road on the board
	void placeRoad(int player, int tile, int side);

	// sets a tile to have the robber
	void setRobber(int tile);

	// ?? (probably checks to see if road claim is legal)
	bool checkRoadPlace(int player, int tile, int side);

	// allows a given player to claim a node on the board
	void placeNode(int player, int tile, int node);

	// allows a given player to upgrade a claimed node
	void placeCity(int player, int tile, int node);

	// ?? (probably checks to see if node claim is legal)
	bool checkNodePlace(int player, int tile, int node);

	// ?? (probably checks to see if node upgrade is legal)
	bool checkCityPlace(int player, int tile, int node);

	// allows the claim of the first nodes of the game (each player gets two)
	void placeFirstNode(int player, int tile, int node);

	// ?? (probably checks to see if first node claim is legal)
	bool checkFirstNodePlace(int player, int tile, int node);
};
