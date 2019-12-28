#pragma once
#include <stack>
#include <set>

class Game
{
public:
	void run();

private:

	struct Index
	{
		int row{ -1 };
		int col{ -1 };
	} m_currentIndex{ 0,0 };

	void printNumbers();
	void solve();
	Index findFirstEmpty();
	bool checkLegal(Index t_index, int t_num);

	static const int NUM_ROWS{ 9 };
	static const int NUM_COLS{ 9 };

	// EASY
	/*int m_grid[NUM_ROWS][NUM_COLS] = {
		{0,6,0,0,0,0,0,0,0},
		{9,0,0,4,0,0,0,6,1},
		{0,0,1,0,0,5,7,0,0},
		{3,1,0,0,9,4,0,2,8},
		{0,0,0,0,0,0,0,0,0},
		{4,5,0,8,2,0,0,9,6},
		{0,0,8,2,0,0,9,0,0},
		{1,7,0,0,0,8,0,0,4},
		{0,0,0,0,0,0,0,3,0}
	};*/

	// MEDIUM
	int m_grid[NUM_ROWS][NUM_COLS] = {
		{0,0,0,0,0,9,0,0,0},
		{0,0,0,0,3,0,0,0,5},
		{2,0,1,0,0,0,0,7,8},
		{0,2,4,5,0,0,6,0,0},
		{0,0,7,0,9,2,0,0,0},
		{0,1,9,4,0,0,3,0,0},
		{5,0,6,0,0,0,0,2,9},
		{0,0,0,0,5,0,0,0,6},
		{0,0,0,0,0,1,0,0,0}
	};

	// HARD
	//int m_grid[NUM_ROWS][NUM_COLS] = {
	//	{0,0,0,0,0,1,0,0,7},
	//	{0,0,0,0,7,0,0,0,0},
	//	{0,0,8,0,9,2,0,6,0},
	//	{0,0,0,0,2,0,0,0,0},
	//	{0,6,7,8,0,0,0,2,4},
	//	{1,0,4,0,0,0,0,3,0},
	//	{0,0,0,0,0,0,0,0,0},
	//	{0,0,9,0,8,3,0,4,1},
	//	{4,0,0,0,6,0,0,9,2}
	//};

	// WORLDS HARDEST
	/*int m_grid[NUM_ROWS][NUM_COLS] = {
		{8,0,0,0,0,0,0,0,0},
		{0,0,3,6,0,0,0,0,0},
		{0,7,0,0,9,0,2,0,0},
		{0,5,0,0,0,7,0,0,0},
		{0,0,0,0,4,5,7,0,0},
		{0,0,0,1,0,0,0,3,0},
		{0,0,1,0,0,0,0,6,8},
		{0,0,8,5,0,0,0,1,0},
		{0,9,0,0,0,0,4,0,0}
	};*/

	int temp_ffeCount{ 0 };
	int temp_ffeCountIterations{ 0 };
	int temp_checkLegalCount{ 0 };
	int temp_popBackCount{ 0 };
	int temp_correctGuessCount{ 0 };
	int temp_wrongGuessCount{ 0 };

	std::stack<Index> m_gameStates;

	std::stack<Index> m_freeCells;

	// Keeps track of the numbers local to a cell
	// (I.e., in the same row, column, or box)
	std::set<int, int> m_localSet;
};