#include<iostream>
#include<string.h>
#include<queue>
#include<chrono>

using namespace std;
#define ROW 5 // 9   
#define COL 5 // 10

// point to locate in the maze
struct Point
{
	int x;
	int y;
};

// A Data Structure for queue used in BFS
struct queueNode
{
	Point pt; // The coordinates of a cell
	int dist; // cell's distance of from the source
};


// For checking whether the cell is valid or not
bool isValid(int row, int col)
{
	return (row >= 0) && (row < ROW) &&
		(col >= 0) && (col < COL);
}

// for moving up, down, left, right from the current cell
int rowNum[] = {-1, 0, 0, 1};
int colNum[] = {0, -1, 1, 0};

// By using BFS to find the shortest path
int BFS(int mat[][COL], Point src, Point dest)
{
	// check whether the source and destination have cell 1
	if (!mat[src.x][src.y] || !mat[dest.x][dest.y])
		return -1;

	bool visited[ROW][COL];
	memset(visited, false, sizeof visited);
	
	// Mark the source cell as visited
	visited[src.x][src.y] = true;

	// Create a queue for BFS
	queue<queueNode> q;
	
	// Distance of source cell is 0
	queueNode s = {src, 0};
	q.push(s); // Enqueue source cell

	// BFS starting from source cell
	while (!q.empty())
	{
		queueNode curr = q.front();
		Point pt = curr.pt;

		// for checking whether the destination is reached
		if (pt.x == dest.x && pt.y == dest.y)
			return curr.dist;

		// else pop the frontcell from the queue
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int row = pt.x + rowNum[i];
			int col = pt.y + colNum[i];
			
			// if adjacent cell is valid, has path and not visited yet, enqueue it.
			if (isValid(row, col) && mat[row][col] && 
			!visited[row][col])
			{
				visited[row][col] = true;
				queueNode Adjcell = { {row, col}, curr.dist + 1 };
				q.push(Adjcell);
			}
		}
	}

	// Return -1 if destination cannot be reached
	return -1;
}

// Driver program to test above function
int main()
{
	int mat[ROW][COL] =
	{
		{ 1, 0, 1, 1, 1 },
		{ 1, 0, 1, 0, 1 },
		{ 1, 1, 1, 0, 1 },
		{ 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 0, 1 }};
	/*
	{
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 0, 1, 0, 1, 1, 1, 0, 1, 1 },
		{ 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
		{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 0, 0, 0, 0, 1, 0, 0, 1 }
	};
	*/

	Point source = {0, 0};
	Point dest = {2, 1};

	// int dist = BFS(mat, source, dest);
	
	auto begin = std::chrono::high_resolution_clock::now();
	int dist = BFS(mat, source, dest);

	auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	printf("Time measured: %.9f seconds.\n", elapsed.count() * 1e-9);

	if (dist != -1)
		cout << "Shortest Path is " << dist ;
	else
		cout << "Shortest Path doesn't exist";

	return 0;
}