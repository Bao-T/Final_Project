#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player
{
private:
	//-- Resources --//
	static int pID;
	int ore=0; // ore standin
	int clay=0; // clay standin
	int wood=0; // wood standin
	int sheep=0; // sheep standin
	int wheat=0; // wheat standin
			   // ------------- //

	int score = 0;

public:
	//Constructor
	Player() {}
	////覧覧覧覧覧Accessors
	/**/int getOre() { return ore; }
	/**/int getClay() { return clay; }
	/**/int getWood() { return wood; }
	/**/int getSheep() { return sheep; }
	/**/int getWheat() { return wheat; }
	/**/int getPlayer() { return pID; }
	/**/int getPlayerScore() { return score; }
	////覧覧覧覧覧覧覧覧覧覧


	////覧覧Incremental Mutators
	/**/void changeOre(int amount) { ore += amount; }
	/**/void changeClay(int amount) { clay += amount; }
	/**/void changeWood(int amount) { wood += amount; }
	/**/void changeSheep(int amount) { sheep += amount; }
	/**/void changeWheat(int amount) { wheat += amount; }
	/**/void changeScore(int amount) { score += amount; }
	////覧覧覧覧覧覧覧覧覧覧覧�
};

#endif