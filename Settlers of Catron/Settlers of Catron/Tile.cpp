#include <iostream>
#include "Tile.h"

void Tile::setFirstTNodes(int index, int player)
{
	tileNodes[index - 1] = player;
}

void Tile::setTNodes(int index, int value) 
{
	int before = abs(((index + 5) % 6));
	int after = abs((index + 1) % 6);
	tileNodes[index] = value;
	tileNodes[before] = -2;
	tileNodes[after] = -2;

}

void Tile::setTNodesForSave(int index, int value) 
{
	tileNodes[index] = value;
}

void Tile::setTNodeState(int index, char value)
{
	tileNodesState[index] = value;
}

void Tile::setTSide(int index, int player)
{
	tileSides[index] = player;
}
