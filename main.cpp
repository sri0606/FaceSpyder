#include "mainwindow.h"
#include "authwindow.h"
#include "spyderwindow.h"
#include <QApplication>
#include "videoplayer.h"
#include <QFileDialog>
#include <QDir>

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    AuthWindow w1;
    w1.show();
    //if logged in/signed up/ skipped head to main wind
    // Connect signals from AuthWindow to slots for handling transitions
    QObject::connect(&w1, &AuthWindow::loggedIn, [&]() {
        SpyderWindow* w2 = new SpyderWindow;
        w2->show();
        w1.close(); // Close the AuthWindow
    });

    QObject::connect(&w1, &AuthWindow::signedUp, [&]() {
        SpyderWindow* w2 = new SpyderWindow;
        w2->show();
        w1.close(); // Close the AuthWindow
    });

    QObject::connect(&w1, &AuthWindow::skipped, [&]() {
        SpyderWindow w2;
        w2.show();
        w1.close(); // Close the AuthWindow
    });

    return app.exec();
}
