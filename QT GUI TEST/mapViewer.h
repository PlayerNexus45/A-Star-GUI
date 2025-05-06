#pragma once

#include <QtWidgets/QMainWindow>
#include <qstringlist.h>

class mapViewer : public QMainWindow
{
    Q_OBJECT

public:
    mapViewer(QWidget* parent = nullptr);
    ~mapViewer();
    void paintEvent(QPaintEvent*);
    void wheelEvent(QWheelEvent*);
    QSize mapSize();

private:
    QStringList mapData;
    const int minCellSize = 2;
    const int maxCellSize = 100;
    int cellSize = 20;

    void loadMap();
    void updateSize();
};
