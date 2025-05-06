#include <iostream>
#include "MinHeap.h"
#include <fstream>

const char WALL = '@';
const char FREE = '.';

using namespace std;

cell** getGridFromMap(int& W, int& H, string filename);
void computeCellMinHeap(cell current, cell& neighor, cell end, MinHeap& pq);
void reconstructPath(cell**& grid, cell end, int w, int h);
void aStar2(string filename, int startX, int startY, int endX, int endY);
double hDist(cell start, cell end);
void saveToFile(cell** map, int W, int H);