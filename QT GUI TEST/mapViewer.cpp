#include "mapViewer.h"
#include<qpainter.h>
#include<qfile.h>
#include<Qwheelevent>

mapViewer::mapViewer(QWidget* parent)
    : QMainWindow(parent)
{
    loadMap();
    resize(mapSize());
}
void mapViewer::loadMap() {
    QFile mapFile("map.txt");
    if (mapFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&mapFile);
        while (!in.atEnd())
        {
            mapData.append(in.readLine());
        }
    }
}
void mapViewer::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setPen(Qt::black);
    for (int y = 0; y < mapData.size(); y++)
    {
        QString line = mapData[y];
        for (int x = 0; x < line.length(); x++)
        {
            QRect rect(x * cellSize, y * cellSize, cellSize, cellSize);
            QChar c = line[x];
            if (c == '.')
            {
                painter.fillRect(rect, Qt::darkGray);
            }
            else if (c == '@') {
                painter.fillRect(rect, Qt::black);
            }
            else if (c == '#') {
                painter.fillRect(rect, Qt::green);
            }
            painter.drawRect(rect);
        }
    }
}
void mapViewer::wheelEvent(QWheelEvent* event) {
    int delta = event->angleDelta().y();
    if (delta > 0 && cellSize < maxCellSize)
    {
        cellSize += 2;
    }
    else if (delta < 0 && cellSize > minCellSize)
    {
        cellSize -= 2;
    }
    updateSize();
    update();
}
QSize mapViewer::mapSize() {
    int w = mapData.isEmpty() ? 400 : mapData[0].length() * cellSize;
    int h = mapData.size() * cellSize;
    return QSize(w, h);
}
void mapViewer::updateSize() {
    setMinimumSize(mapSize());
    resize(mapSize());
}

mapViewer::~mapViewer()
{}
