#include "Game.h"
#include <iostream>
#include <chrono>

void Game::run()
{
	std::cout << "Original:" << std::endl;
	printNumbers();

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	solve();
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "Solved:" << std::endl;
	printNumbers();

	std::cout << "'correct' guesses: " << temp_correctGuessCount << std::endl;
	std::cout << "incorrect guesses: " << temp_wrongGuessCount << std::endl;
	std::cout << "find first empty checks: " << temp_ffeCount << std::endl;
	std::cout << "find first empty check iterations: " << temp_ffeCountIterations << std::endl;
	std::cout << "check legal: " << temp_checkLegalCount << std::endl;
	std::cout << "num pop backs: " << temp_popBackCount << std::endl;

	std::cout << "Time to solve = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000.0 << "[ms]" << std::endl;

	system("PAUSE");
}

//////////////////////////////////

void Game::printNumbers()
{
	for (int i = 0; i < NUM_ROWS; i++)
	{
		for (int j = 0; j < NUM_COLS; j++)
		{
			std::cout << m_grid[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

//////////////////////////////////

void Game::solve()
{
	m_currentIndex = findFirstEmpty(); // next empty cell

	m_gameStates.push(m_currentIndex);

	do
	{
		// start with number in cell plus 1
		int numToTry{ m_grid[m_currentIndex.row][m_currentIndex.col] + 1 };

		while (numToTry < 10)
		{
			if (checkLegal(m_currentIndex, numToTry)) // if that number is legal
			{
				temp_correctGuessCount++;

				m_grid[m_currentIndex.row][m_currentIndex.col] = numToTry; // add it
				
				m_gameStates.push(m_currentIndex); // push our index to the gamestates to run back to


				if (!m_freeCells.empty())
				{
					m_currentIndex = m_freeCells.top();
					m_freeCells.pop();
				}
				else
				{
					m_currentIndex = findFirstEmpty();
				}
				break;
			}
			else
			{
				temp_wrongGuessCount++;
				numToTry++; // otherwise, increment the number
			}
		}

		// if no numbers fit
		if (numToTry > 9)
		{
			m_grid[m_currentIndex.row][m_currentIndex.col] = 0;

			m_freeCells.push(m_currentIndex);
			m_currentIndex = m_gameStates.top();

			if (m_gameStates.size() > 1)
			{
				temp_popBackCount++;

				m_gameStates.pop(); // pop back to the last
			}
			else
			{
				break;
			}
		}

	} while (m_currentIndex.row != -1);
}

//////////////////////////////////

Game::Index Game::findFirstEmpty()
{
	temp_ffeCount++;

	for (int i = 0; i < NUM_ROWS; i++)
	{
		for (int j = 0; j < NUM_COLS; j++)
		{
			temp_ffeCountIterations++;
			if (m_grid[i][j] == 0)
			{
				return Index{i, j};
			}
		}
	}

	return Index();
}

//////////////////////////////////

bool Game::checkLegal(Index t_index, int t_num)
{
	temp_checkLegalCount++;

	// check rows
	for (int row = 0; row < NUM_ROWS; row++)
	{
		// if any of the entries match our num
		if (t_num == m_grid[row][t_index.col])
		{
			return false;
		}
	}

	// check cols
	for (int col = 0; col < NUM_COLS; col++)
	{
		// if any of the entires match our num
		if (t_num == m_grid[t_index.row][col])
		{
			return false;
		}
	}

	int rowStart = -1;
	int colStart = -1;

	// check box
	if (t_index.row < 3)
	{
		rowStart = 0;
	}
	else if (t_index.row < 6)
	{
		rowStart = 3;
	}
	else
	{
		rowStart = 6;
	}

	if (t_index.col < 3)
	{
		colStart = 0;
	}
	else if (t_index.col < 6)
	{
		colStart = 3;
	}
	else
	{
		colStart = 6;
	}

	for (int row = rowStart; row < rowStart + 3; row++)
	{
		for (int col = colStart; col < colStart + 3; col++)
		{
			if (t_num == m_grid[row][col])
			{
				return false;
			}
		}
	}

	return true;
}