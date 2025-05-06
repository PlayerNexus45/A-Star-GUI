#include "mainWindow.h"
#include "mapViewer.h"
#include "AStarModule.h"
#include <qtextedit.h>
#include <qmessagebox.h>
mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}


mainWindow::~mainWindow()
{}

void mainWindow::on_generateButton_clicked() {
    bool ok1, ok2, ok3, ok4;
    int startX = ui.textBoxStartX->toPlainText().toInt(&ok1);
    int startY = ui.textBoxStartY->toPlainText().toInt(&ok2);
    int endX = ui.textBoxEndX->toPlainText().toInt(&ok3);
    int endY = ui.textBoxEndY->toPlainText().toInt(&ok4);
    if (ok1 && ok2 && ok3 && ok4)
    {
        //QMessageBox::information(this, "Debug", QString("A star algorithm starting with the values:\n Start (%1, %2)\n End(%3, %4)").arg(startX).arg(startY).arg(endX).arg(endY));
        aStar2("map1.map", startX, startY, endX, endY);
        mapViewer* map = new mapViewer();
        map->setWindowTitle("Map Viewer");
        map->setAttribute(Qt::WA_DeleteOnClose);
        map->show();
    }
    else
    {
        QMessageBox::warning(this, "Input Error", "The Text Boxes Must Contain Integer Values");
    }

}

