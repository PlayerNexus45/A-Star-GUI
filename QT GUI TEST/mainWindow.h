#pragma once

#include <QtWidgets/QMainWindow>

#include "ui_mainWindow.h"

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    mainWindow(QWidget *parent = nullptr);
    ~mainWindow();
private slots:
    void on_generateButton_clicked();

private:
    Ui::mainWindowClass ui;

};
