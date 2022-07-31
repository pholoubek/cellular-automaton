#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;

const int GRID_SIZE = 50;
const char LIVE_CELL = '#';

void displayGrid(const vector<vector<char>> &grid);
void runIteration(vector<vector<char>> &grid);
void populateGrid(vector<vector<char>> &grid, int row, int col);
char determineCellLife(vector<vector<char>> &grid, int x, int y);

int main()
{
	vector<vector<char>> grid(GRID_SIZE, vector<char>(GRID_SIZE, ' '));

	// initial configuration
	grid[25][25] = LIVE_CELL;
	grid[24][25] = LIVE_CELL;
	grid[26][25] = LIVE_CELL;
	grid[26][26] = LIVE_CELL;
	grid[26][24] = LIVE_CELL;
	grid[27][24] = LIVE_CELL;
	grid[30][31] = LIVE_CELL;

	grid[33][22] = LIVE_CELL;
	grid[34][20] = LIVE_CELL;

	grid[5][2] = LIVE_CELL;
	grid[8][3] = LIVE_CELL;

	bool done = false;
	int row;
	int col;
	string popCmd = "";
	while (!done)
	{
		cout << "Row: " << endl;
		cin >> row;
		cout << "Col: " << endl;
		cin >> col;
		populateGrid(grid, row, col);
		displayGrid(grid);
		cout << "Continue?" << endl;
		cin >> popCmd;

		if (popCmd != "y")
			done = true;
	}

	string cmd = "";
	done = false;
	while (!done)
	{
		runIteration(grid);
		displayGrid(grid);

		cout << "Next iteration" << endl;
		cin >> cmd;

		if (cmd != "y")
			done = true;
	}
	return 0;
}

// not  pure function but will do here...
void populateGrid(vector<vector<char>> &grid, int row, int col)
{
	grid[row][col] = LIVE_CELL;
}

void runIteration(vector<vector<char>> &grid)
{
	int grid_size = grid[0].size();
	for (int i = 0; i < grid_size; i++)
	{
		for (int j = 0; j < grid_size; j++)
		{
			grid[i][j] = determineCellLife(grid, i, j);
		}
	}
}

void displayGrid(const vector<vector<char>> &grid)
{
	int grid_size = grid[0].size();
	for (int i = 0; i < grid_size; i++)
	{
		for (int j = 0; j < grid_size; j++)
		{
			cout << grid[i][j];
		}
		cout << endl;
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

	cout << "( " << x << " , " << y << " ) "
		 << "'" << grid[x][y] << "'"
		 << " ";

	if (x == 0 && y == 0)
	{
		cout << "case 1 " << endl;
		if (grid[x][y + 1] == LIVE_CELL)
			negbrs++;
		if (grid[x + 1][y + 1] == LIVE_CELL)
			negbrs++;
		if (grid[x + 1][y] == LIVE_CELL)
			negbrs++;
	}
	else if (x == 0 && y == max_length)
	{
		cout << "case 2 " << endl;
		if (grid[x][y - 1] == LIVE_CELL)
			negbrs++;
		if (grid[x + 1][y - 1] == LIVE_CELL)
			negbrs++;
		if (grid[x + 1][y] == LIVE_CELL)
			negbrs++;
	}
	else if (x == max_length && y == 0)
	{
		cout << "case 3 " << endl;
		if (grid[x][y + 1] == LIVE_CELL)
			negbrs++;
		if (grid[x - 1][y + 1] == LIVE_CELL)
			negbrs++;
		if (grid[x - 1][y] == LIVE_CELL)
			negbrs++;
	}
	else if (x == max_length && y == max_length)
	{
		cout << "case 4 " << endl;
		if (grid[x][y - 1] == LIVE_CELL)
			negbrs++;
		if (grid[x - 1][y - 1] == LIVE_CELL)
			negbrs++;
		if (grid[x - 1][y] == LIVE_CELL)
			negbrs++;
	}
	else if (x == 0)
	{
		cout << "case 5 " << endl;
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
		cout << "case 6 " << endl;
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
		cout << "case 7 " << endl;
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
	cout << "negbrs: " << negbrs << endl;

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