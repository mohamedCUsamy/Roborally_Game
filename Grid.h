#pragma once

#include "UI_Info.h"
#include "DEFS.h"

#include "Input.h"
#include "Output.h"
#include "CellPosition.h"

// forward declarations (the includes are in the cpp)
class Cell;
class GameObject;
class Player;
class Belt;
class Grid
{
	Output *pOut; // A pointer to the Output object
	Input *pIn;	  // A pointer to the Input object

	Cell *CellList[NumVerticalCells][NumHorizontalCells]; // An array of "Pointers" to All Cells of the Grid Cells
														  // We make it array of pointers not objects because
														  // there are NO default constructor for class Cell

	Player *PlayerList[MaxPlayerCount]; // An array of "Pointers" to the Players of the Game (MaxPlayerCount Players)
	int currPlayerNumber;				// The player number that has the turn to play
										// currPlayerNumber is: from 0 to MaxPlayerCount - 1
	int numAntennas;					// Number of antennas in the grid
	int numWaterPits;
	int numFlag;
	int numDangerZones;
	int numBelts;
	int numWorkshops;
	int numRotatingGears;

	GameObject *Clipboard; // This is used in copy/cut/paste game objects (should be set in copy/cut and got in paste)

	bool endGame; // A boolean indicating if the Game is ended or not (a player reaches the flag cell or not)

public:
	Grid(Input *pIn, Output *pOut); // Gives the Grid a Pointer to the Output Object and the Input Object
									// and makes any needed initializations

	// ========= Adding or Removing GameObjects to Cells =========

	bool AddObjectToCell(GameObject *pNewObject); // Adds a GameObject to the Cell of its "position" data member
												  // only if the Cell does NOT already contain an object,
												  // otherwise return false and don't add

	bool RemoveObjectFromCell(const CellPosition &pos); // Removes the GameObject of the Cell of the passed "position"
														// Note: You may need to change the return type of this function (Think)

	void UpdatePlayerCell(Player *player, const CellPosition &newPosition); // Update the player's pCell with the CellList's Cell pointer of the "newPosition",
																			// Clears the player's circle from the previous cell
																			// and  Draws it in the new cell

	// ========= Setters and Getters Functions =========

	Input *GetInput() const;   // Gets a Pointer to the Input
	Output *GetOutput() const; // Gets a Pointer to the Output

	void SetClipboard(GameObject *gameObject); // A setter to be used in copy/cut (in order NOT to break class responsibilities)
	GameObject *GetClipboard() const;		   // A getter to be used in paste (in order NOT to break class responsibilities)

	void SetEndGame(bool endGame); // A setter for endGame data member
	bool GetEndGame() const;	   // A getter for endGame data member

	void AdvanceCurrentPlayer(); // Increments the currPlayerNum and if reaches MaxPlayerCount reset to 0 (using %)

	/// TODO: add any needed setter/getter "EXCEPT" ANY setters or getters of "CellList" or "PlayerList" (Forbidden for class Responsibilities)
	void SetCurrentPlayer(int playerNum); // A setter for the currPlayerNumber
										  // It sets the current player number to the passed value

	int GetNumAntennas() const;
	void SetNumAntennas(int numAntennas);

	int GetNumFlag() const;
	void SetNumFlag(int numFlag);

	int GetnumWaterPits() const;
	void SetnumWaterPits(int numwp);

	int GetnumDangerZones() const;
	void SetnumDangerZones(int numdg);

	int GetnumBelts() const;
	void SetnumBelts(int numbelts);

	int GetnumWorkshops() const;
	void SetnumWorkshops(int numws);

	int GetnumRotatingGears() const;
	void SetnumRotatingGears(int numrg);

	// ========= Other Getters =========

	Player *GetCurrentPlayer() const;				 // Gets a Pointer to the Current Player
	Belt *GetNextBelt(const CellPosition &position); // Gets a Pointer to the first Belth after the passed "position"

	// ========= User Interface Functions =========

	void UpdateInterface() const; // It Updates the Grid according to the last state of the game
								  // In Design mode, it draws all cells THEN all game objects THEN all players
								  // In Play mode, it only draws the player's info on the right side of the toolbar
								  // Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
								  //       and the belts/flags/waterpits and other gameObjects positions do NOT change already in Play Mode

	void PrintErrorMessage(string msg); // Prints an error message on statusbar, Waits for mouse click then clears statusbar
										// We added this function once here because it is used many times by other classes

	GameObject *GetGameObjectfromCellPosition(const CellPosition &selected_cell);

	void DeleteGameObj(const CellPosition &selected_cell);
	void DeallocateClipboard();
	void SaveAll(ofstream &outfile, int type);

	~Grid(); // A destructor for any needed deallcations
};
