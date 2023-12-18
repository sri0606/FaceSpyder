#include "mainwindow.h"
#include "authwindow.h"
#include "spyderwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SpyderWindow w;
    w.show();
    // AuthWindow w1;
    // w1.show();
    // //if logged in/signed up/ skipped head to main wind
    // // Connect signals from AuthWindow to slots for handling transitions
    // QObject::connect(&w1, &AuthWindow::loggedIn, [&]() {
    //     MainWindow* w2 = new MainWindow;
    //     w2->show();
    //     w1.close(); // Close the AuthWindow
    // });

    // QObject::connect(&w1, &AuthWindow::signedUp, [&]() {
    //     MainWindow* w2 = new MainWindow;
    //     w2->show();
    //     w1.close(); // Close the AuthWindow
    // });

    // QObject::connect(&w1, &AuthWindow::skipped, [&]() {
    //     MainWindow w2;
    //     w2.show();
    //     w1.close(); // Close the AuthWindow
    // });
    return a.exec();
}
