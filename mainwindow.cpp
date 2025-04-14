#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
}

MainWindow::~MainWindow()
{
    delete ui;
}
