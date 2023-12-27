#include "loadingwindow.h"
#include <QApplication>
#include <QIcon>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>

const QString loadImagePath = "resources/images/load.png";

loadingWindow::loadingWindow(QWidget *parent)
    : QWidget(parent)
{
    // Set the background color
    setStyleSheet("background-color: rgb(0,0,0);");

    // Create a layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Create and configure the image label
    QLabel *imageLabel = new QLabel(this);
    QPixmap logoPixmap(loadImagePath);
    imageLabel->setPixmap(logoPixmap.scaled(1000, 800, Qt::KeepAspectRatio));
    imageLabel->setAlignment(Qt::AlignCenter);

    // Create and configure the "Powered by" label
    QLabel *poweredByLabel = new QLabel("Powered by Qt and OpenCV", this);
    poweredByLabel->setAlignment(Qt::AlignCenter);
    poweredByLabel->setStyleSheet("color: white; font-size: 24px;");

    // Create and configure the copyright label
    QLabel *copyrightLabel = new QLabel("© Sriram Seelamneni", this);
    copyrightLabel->setAlignment(Qt::AlignCenter);
    copyrightLabel->setStyleSheet("color: white; font-size: 18px;");

    // Add widgets to the layout
    layout->addWidget(imageLabel, 7);
    layout->addWidget(poweredByLabel, 2);
    layout->addStretch(); // Adds space between the labels and copyright
    layout->addWidget(copyrightLabel, 1);

    // Set the layout
    setLayout(layout);
}
