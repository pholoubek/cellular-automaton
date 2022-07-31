#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;

const int GRID_SIZE = 50;
const char LIVE_CELL = '#';

void displayGrid(const vector<vector<char>> &grid, int grid_size);
char determineCellLife(const vector<vector<char>> &grid, int x, int y);

int main()
{
	vector<vector<char>> grid(GRID_SIZE, vector<char>(GRID_SIZE, ' '));

	// initial configuration
	grid[25][25] = LIVE_CELL;
	grid[24][25] = LIVE_CELL;
	grid[26][25] = LIVE_CELL;
	grid[33][22] = LIVE_CELL;
	grid[34][20] = LIVE_CELL;

	grid[5][2] = LIVE_CELL;
	grid[8][3] = LIVE_CELL;

	displayGrid(grid, GRID_SIZE);
	return 0;
}

void displayGrid(vector<vector<char>> &grid, int grid_size)
{

	while (1 == 1)
	{
		for (int i = 0; i < grid_size; i++)
		{
			for (int j = 0; j < grid[i].size(); j++)
			{
				cout << determineCellLife(grid, i, j);
			}
			cout << endl;
		}
		std::chrono::duration<int, std::milli> timespan(1000);
		std::this_thread::sleep_for(timespan);
	}
}
/*

edge cases:

	grid[n-1][0] -> by the left border
	grid[0][0 - n - 1] -> by the upper border
	grid[n-1][0 - n - 1] -> by the lower border
	grid[0 - n - 1][n - 1] -> by the right border

**/

char determineCellLife(vector<vector<char>> &grid, int x, int y)
{
	int max_length = grid[0].size() - 1;
	int negbrs = 0;

	// cout << "(x, y): " << x << " , " << y << endl;

	if (x == 0 && y == 0)
	{
		// cout << " case 1 " << endl;
		if (grid[x][y + 1] == LIVE_CELL)
			negbrs++;
		if (grid[x + 1][y + 1] == LIVE_CELL)
			negbrs++;
		if (grid[x + 1][y] == LIVE_CELL)
			negbrs++;
	}
	else if (x == 0 && y == max_length)
	{
		// cout << " case 2 " << endl;
		if (grid[x][y - 1] == LIVE_CELL)
			negbrs++;
		if (grid[x + 1][y - 1] == LIVE_CELL)
			negbrs++;
		if (grid[x + 1][y] == LIVE_CELL)
			negbrs++;
	}
	else if (x == max_length && y == 0)
	{
		// cout << " case 3 " << endl;
		if (grid[x][y + 1] == LIVE_CELL)
			negbrs++;
		if (grid[x - 1][y + 1] == LIVE_CELL)
			negbrs++;
		if (grid[x - 1][y] == LIVE_CELL)
			negbrs++;
	}
	else if (x == max_length && y == max_length)
	{
		// cout << " case 4 " << endl;
		if (grid[x][y - 1] == LIVE_CELL)
			negbrs++;
		if (grid[x - 1][y - 1] == LIVE_CELL)
			negbrs++;
		if (grid[x - 1][y] == LIVE_CELL)
			negbrs++;
	}
	else if (x == 0)
	{
		// cout << " case 5 " << endl;
		if (grid[x][y - 1] == LIVE_CELL)
			negbrs++;
		if (grid[x][y + 1] == LIVE_CELL)
			negbrs++;
		if (grid[x + 1][y] == LIVE_CELL)
			negbrs++;
		if (grid[x + 1][y - 1] == LIVE_CELL)
			negbrs++;
		if (grid[x + 1][y + 1] == LIVE_CELL)
			negbrs++;
	}
	else if (x == max_length)
	{
		// cout << " case 6 " << endl;
		if (grid[x][y - 1] == LIVE_CELL)
			negbrs++;
		if (grid[x][y + 1] == LIVE_CELL)
			negbrs++;
		if (grid[x - 1][y] == LIVE_CELL)
			negbrs++;
		if (grid[x - 1][y - 1] == LIVE_CELL)
			negbrs++;
		if (grid[x - 1][y + 1] == LIVE_CELL)
			negbrs++;
	}
	else
	{
		// cout << " case 7 " << endl;
		if (grid[x + 1][y] == LIVE_CELL)
			negbrs++;
		if (grid[x + 1][y + 1] == LIVE_CELL)
			negbrs++;
		if (grid[x][y + 1] == LIVE_CELL)
			negbrs++;
		if (grid[x - 1][y + 1] == LIVE_CELL)
			negbrs++;
		if (grid[x - 1][y] == LIVE_CELL)
			negbrs++;
		if (grid[x - 1][y - 1] == LIVE_CELL)
			negbrs++;
		if (grid[x][y - 1] == LIVE_CELL)
			negbrs++;
		if (grid[x + 1][y - 1] == LIVE_CELL)
			negbrs++;
	}

	// Any live cell with fewer than two live neighbours dies, as if by underpopulation.
	// Any live cell with two or three live neighbours lives on to the next generation.
	// Any live cell with more than three live neighbours dies, as if by overpopulation.
	// Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

	if (grid[x][y] == LIVE_CELL)
	{
		if (negbrs < 2)
			return ' ';
		if (negbrs > 3)
			return ' ';
	}
	else
	{
		if (negbrs == 3)
			return '#';
	}

	return ' ';
}