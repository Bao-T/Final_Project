#pragma once
#include <iostream>
#ifndef _TILE_H_
#define _TILE_H_
class Tile {
private:
	/*int tileSides[6] = { 1,1,1,1,1,1 };
	int tileNodes[6] = { -1,-1,1,1,1,1 };*/
	int tileSides[6] = { -1,-1,-1,-1,-1,-1 };
	int tileNodes[6] = { -1,-1,-1,-1,-1,-1 };
	char tileNodesState[6] = { 'H','H','H','H','H','H' };
	bool robber;
	int tileValue;
	char tileType;
public:
	Tile() {
		robber = false;
		tileValue = -1;
		tileType = 'D';
	}
	//Accessors
	int getTNode(int index) { return tileNodes[index-1]; }
	int getTSide(int index) { return tileSides[index-1]; }
	bool getTRobber() { return robber; }
	char getTType() { return tileType; }
	int getTValue() { return tileValue; }
	char getTNodeState(int index) { return tileNodesState[index-1]; }
	//Manipulators
	void setTType(char x) { tileType = x; }
	void setTValue(int x) { tileValue = x; }
	void setTRobber(bool x) { robber = x; }
	void setFirstTNodes(int index, int player)
	{
		tileNodes[index - 1] = player;
	}
	void setTNodes(int index, int value) { 
		int before = abs(((index + 5) % 6));
		int after = abs((index + 1) % 6);
		tileNodes[index] = value;
		tileNodes[before] = -2;
		tileNodes[after] = -2;
		
	}
	void setTNodesForSave(int index, int value) {
		tileNodes[index] = value;

	}
	void setTNodeState(int index, char value)
	{
		tileNodesState[index] = value;
	}
	void setTSide(int index, int player)
	{
		tileSides[index] = player;
	}
	int *tSideAddress(int x) { return &tileSides[x]; }
	int *tNodeAddress(int x) { return &tileNodes[x]; }

};
#endif