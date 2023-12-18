#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <memory.h>

/// Frame duration in milliseconds
const int FrameDuration = 30;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();

}

MainWindow::~MainWindow()
{
    delete ui;
}

