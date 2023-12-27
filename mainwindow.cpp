#include "mainwindow.h"
#include "spyderwindow.h"
#include "loadingwindow.h"
#include <QApplication>
#include <QMainWindow>
#include <QStackedWidget>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    setStyleSheet("background-color:rgb(0,0,0);");
    // Create the stacked widget
    QStackedWidget* stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // Create your "windows" as widgets
    loadingWidget = new loadingWindow;
    spyderWidget = new SpyderWindow;

    // Add the widgets to the stacked widget
    stackedWidget->addWidget(loadingWidget);
    stackedWidget->addWidget(spyderWidget);

    // Show the loading widget first
    stackedWidget->setCurrentWidget(loadingWidget);

    // Create a QTimer to switch after some time
    QTimer::singleShot(3000, [this, stackedWidget]() {
        stackedWidget->setCurrentWidget(spyderWidget);
    });

}

// void MainWindow::closeEvent(QCloseEvent *event) {
//     spyderWidget->processCloseEvent();
//     QMainWindow::closeEvent(event);
// }
