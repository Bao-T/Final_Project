#pragma once
#ifndef _TILE_H_
#define _TILE_H_
#include <iostream>

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
	///Constructor
	Tile() {
		robber = false;
		tileValue = -1;
		tileType = 'D';
	}

	////————————————————Accessors
	/**/int getTNode(int index) { return tileNodes[index-1]; }
	/**/int getTSide(int index) { return tileSides[index-1]; }
	/**/bool getTRobber() { return robber; }
	/**/char getTType() { return tileType; }
	/**/int getTValue() { return tileValue; }
	/**/char getTNodeState(int index) { return tileNodesState[index-1]; }
	/**/int *tSideAddress(int x) { return &tileSides[x]; }
	/**/int *tNodeAddress(int x) { return &tileNodes[x]; }
	////—————————————————————————

	////—————————————Manipulators
	/**/void setTType(char x) { tileType = x; }
	/**/void setTValue(int x) { tileValue = x; }
	/**/void setTRobber(bool x) { robber = x; }
	/**/// Fxn definitions for those below found in Tile.cpp
	/**/void setFirstTNodes(int index, int player);
	/**/void setTNodes(int index, int value);
	/**/void setTNodesForSave(int index, int value);
	/**/void setTNodeState(int index, char value);
	/**/void setTSide(int index, int player);
	////—————————————————————————

	

	

};
#endif