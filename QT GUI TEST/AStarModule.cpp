#include "AStarModule.h"

double hDist(cell start, cell end) {
    //Obliczanie minimalnej odleg³oœci z trygonometrii
    return (double)sqrt(pow((end.x - start.x), 2) + pow((end.y - start.y), 2));
    // 
    // Obliczanie tz. Taxicab distance   
    //return abs(end.x - start.x) + abs(end.y - start.y); 
    // 
    //obliczanie do octile map
    //int dx = abs(start.x - end.x);
    //int dy = abs(start.y - end.y);
    //return sqrt(2) * min(dx, dy) + abs(dx - dy);
    //modified to fix sidestepping issues
    //int dx = abs(start.x - end.x);
    //int dy = abs(start.y - end.y);
    //return 1*(dx+dy) + (sqrt(2) - 2) * min(dx, dy);
}
cell** getGridFromMap(int& W, int& H, string filename) {

    ifstream file(filename);

    file.ignore(18);
    file >> H;
    file.ignore(6);
    file >> W;
    file.ignore(4);


    cell** grid = new cell * [H];
    for (int i = 0; i < H; i++) grid[i] = new cell[W];

    for (int i = 0; i < H; i++)
    {
        string row = "";
        file >> row;
        for (int j = 0; j < W; j++)
        {
            grid[i][j].x = j;
            grid[i][j].y = i;
            grid[i][j].c = row[j];

            grid[i][j].g = INT_MAX;
            grid[i][j].f = INT_MAX;
            grid[i][j].visited = false;
        }
    }
    file.close();

    return grid;
}
bool checkWall(cell lookedAt) {
    return (lookedAt.c == WALL || lookedAt.c == '#');
}
void computeCellMinHeap(cell current, cell& neighor, cell end, MinHeap& pq) {

    if (checkWall(neighor))
    {
        return;
    }
    double newG = current.g + hDist(current, neighor);
    double newH = hDist(neighor, end);
    double newF = newG + newH;

    if (neighor.g > newG)
    {
        neighor.parentX = current.x;
        neighor.parentY = current.y;

        neighor.g = newG;
        neighor.f = newF;
        if (!pq.isInHeap(neighor))
        {
            pq.insertKey(neighor);
        }
    }
}
void reconstructPath(cell**& grid, cell end, int w, int h) {
    cout << "Droga: ";
    int row = end.y;
    int col = end.x;
    MinHeapG recPath(10);
    while (!(grid[row][col].parentY == row && grid[row][col].parentX == col))
    {
        grid[row][col].c = '#';
        recPath.insertKey(grid[row][col]);
        int nCol = grid[row][col].parentX;
        int nRow = grid[row][col].parentY;
        row = nRow;
        col = nCol;
    }
    grid[row][col].c = '#';
    recPath.insertKey(grid[row][col]);

    while (recPath.getSize() > 1)
    {
        cell curr = recPath.extractMin();
        cout << '(' << curr.x << ',' << curr.y << ")->";
    }

    cell curr = recPath.extractMin();
    cout << '(' << curr.x << ',' << curr.y << ")" << endl;

    saveToFile(grid, w, h);
}
void aStar2(string filename, int startX, int startY, int endX, int endY) {
    
    int h = 0;
    int w = 0;

    cell** grid = getGridFromMap(w, h, filename);
    cell start = grid[startY][startX];
    cell end = grid[endY][endX];
    MinHeap pq = MinHeap(10);
    cell current;

    grid[start.y][start.x].g = 0;
    grid[start.y][start.x].f = hDist(start, end);
    grid[start.y][start.x].parentX = grid[start.y][start.x].x;
    grid[start.y][start.x].parentY = grid[start.y][start.x].y;

    pq.insertKey(grid[start.y][start.x]);

    while (pq.getSize() != -1)
    {
        current = pq.extractMin();
        grid[current.y][current.x].visited = true;
        if (current.x - 1 >= 0)
        {
            if (grid[current.y][current.x - 1].x == end.x && grid[current.y][current.x - 1].y == end.y)
            {
                grid[current.y][current.x - 1].parentX = current.x;
                grid[current.y][current.x - 1].parentY = current.y;
                reconstructPath(grid, end, w, h);
                pq.deleteHeap();
                return;
            }
            computeCellMinHeap(current, grid[current.y][current.x - 1], end, pq);

            if (current.y - 1 >= 0)
            {
                if (grid[current.y - 1][current.x - 1].x == end.x && grid[current.y - 1][current.x - 1].y == end.y)
                {
                    grid[current.y - 1][current.x - 1].parentX = current.x;
                    grid[current.y - 1][current.x - 1].parentY = current.y;
                    reconstructPath(grid, end, w, h);
                    pq.deleteHeap();
                    return;
                }
                computeCellMinHeap(current, grid[current.y - 1][current.x - 1], end, pq);

            }
            if (current.y + 1 < h)
            {
                if (grid[current.y + 1][current.x - 1].x == end.x && grid[current.y + 1][current.x - 1].y == end.y)
                {
                    grid[current.y + 1][current.x - 1].parentX = current.x;
                    grid[current.y + 1][current.x - 1].parentY = current.y;
                    reconstructPath(grid, end, w, h);
                    pq.deleteHeap();
                    return;
                }
                computeCellMinHeap(current, grid[current.y + 1][current.x - 1], end, pq);
            }
        }
        if (current.x + 1 < w)
        {
            if (grid[current.y][current.x + 1].x == end.x && grid[current.y][current.x + 1].y == end.y)
            {
                grid[current.y][current.x + 1].parentX = current.x;
                grid[current.y][current.x + 1].parentY = current.y;
                reconstructPath(grid, end, w, h);
                pq.deleteHeap();
                return;
            }
            computeCellMinHeap(current, grid[current.y][current.x + 1], end, pq);
            if (current.y - 1 >= 0)
            {
                if (grid[current.y - 1][current.x + 1].x == end.x && grid[current.y - 1][current.x + 1].y == end.y)
                {
                    grid[current.y - 1][current.x + 1].parentX = current.x;
                    grid[current.y - 1][current.x + 1].parentY = current.y;
                    reconstructPath(grid, end, w, h);
                    pq.deleteHeap();
                    return;
                }
                computeCellMinHeap(current, grid[current.y - 1][current.x + 1], end, pq);
            }
            if (current.y + 1 < h)
            {
                if (grid[current.y + 1][current.x + 1].x == end.x && grid[current.y + 1][current.x + 1].y == end.y)
                {
                    grid[current.y + 1][current.x + 1].parentX = current.x;
                    grid[current.y + 1][current.x + 1].parentY = current.y;
                    reconstructPath(grid, end, w, h);
                    pq.deleteHeap();
                    return;
                }
                computeCellMinHeap(current, grid[current.y + 1][current.x + 1], end, pq);
            }
        }
        if (current.y - 1 >= 0)
        {
            if (grid[current.y - 1][current.x].x == end.x && grid[current.y - 1][current.x].y == end.y)
            {
                grid[current.y - 1][current.x].parentX = current.x;
                grid[current.y - 1][current.x].parentY = current.y;
                reconstructPath(grid, end, w, h);
                pq.deleteHeap();
                return;
            }
            computeCellMinHeap(current, grid[current.y - 1][current.x], end, pq);
        }
        if (current.y + 1 < h)
        {
            if (grid[current.y + 1][current.x].x == end.x && grid[current.y + 1][current.x].y == end.y)
            {
                grid[current.y + 1][current.x].parentX = current.x;
                grid[current.y + 1][current.x].parentY = current.y;
                reconstructPath(grid, end, w, h);
                pq.deleteHeap();
                return;
            }
            computeCellMinHeap(current, grid[current.y + 1][current.x], end, pq);
        }
    }
}
void saveToFile(cell** map, int W, int H) {
    ofstream file("map.txt");

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            file << map[i][j].c;
        }
        file << endl;
    }
}
