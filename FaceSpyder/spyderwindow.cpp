#include "spyderwindow.h"
#include <QDesktopServices>
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>
#include <QScrollArea>
#include <QUrl>
#include "FaceRecognition.h"
#include <memory.h>

SpyderWindow::SpyderWindow(QWidget *parent)
    : QWidget(parent)
{
    auto containerLayout = new QHBoxLayout(this);
    containerLayout->setContentsMargins(0, 0, 0, 0);
    // Create the main layout (75% of coantinerLayout)
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    auto scrollArea = new QScrollArea(this);
    // Add widgets to the main layout
    mFaceRecognitionView = new FaceRecognitionView(scrollArea);
    mFaceDetectionView = new FaceDetectionView(this);
    scrollArea->setWidget(mFaceDetectionView);
    scrollArea->setWidgetResizable(true);

    mFaceRecognition = std::make_shared<FaceRecognition>();
    mFaceRecognitionView->SetFaceRecognition(mFaceRecognition);
    mFaceDetectionView->SetFaceRecognition(mFaceRecognition);

    mainLayout->addWidget(mFaceRecognitionView, 3); // 75%
    mainLayout->addWidget(scrollArea, 2);

    auto menuLayout = new QVBoxLayout(this);
    menuLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *label = new QLabel();
    label->setText("<font size=25 color='red'>FaceSpyder</font>");
    label->setAlignment(Qt::AlignCenter);

    QFrame *horizontalLine = new QFrame;
    horizontalLine->setFrameShape(QFrame::HLine);
    horizontalLine->setFrameShadow(QFrame::Sunken);

    // Create the menu layout (25%)
    auto menuTopLayout = new QVBoxLayout(this);
    menuTopLayout->setContentsMargins(0, 20, 0, 2);
    int buttonSpacing = 15;

    // homeButton = new MenuButton("Home",this);
    imageButton = new MenuButton("Open Image", this);
    videoButton = new MenuButton("Open Video", this);
    saveDetectedFacesButton = new MenuButton("Save detected faces", this);

    saveDetectedFacesButton->setDisabled(true);
    // menuTopLayout->addWidget(homeButton);
    // menuTopLayout->addSpacing(buttonSpacing);
    menuTopLayout->addWidget(imageButton);
    menuTopLayout->addSpacing(buttonSpacing);
    menuTopLayout->addWidget(videoButton);
    menuTopLayout->addSpacing(buttonSpacing);
    menuTopLayout->addWidget(saveDetectedFacesButton);
    // Add a stretch to push menuTopLayout to the top
    menuTopLayout->addStretch();

    auto menuBottomLayout = new QVBoxLayout(this);
    menuBottomLayout->setContentsMargins(0, 0, 0, 25);

    //settingsButton = new MenuButton("Settings",this);
    newSessionButton = new QPushButton(this);
    newSessionButton->setStyleSheet(
        "background-color:green; font-size:15px; color:white;border-radius:5px;padding:10px");
    newSessionButton->setText("New Spyder Session...");

    aboutButton = new QPushButton(this);
    aboutButton->setStyleSheet(
        "background-color:blue; font-size:15px; color:white;border-radius:5px;padding:10px");
    aboutButton->setText("About FaceSpyder");

    menuBottomLayout->addWidget(newSessionButton);
    menuBottomLayout->addSpacing(10);
    menuBottomLayout->addWidget(aboutButton);
    menuBottomLayout->addSpacing(10);
    //menuBottomLayout->addWidget(settingsButton);
    menuBottomLayout->addSpacing(10);

    menuLayout->addSpacing(10);
    menuLayout->addWidget(label);
    menuLayout->addSpacing(10);
    menuLayout->addWidget(horizontalLine);
    menuLayout->addLayout(menuTopLayout, 6);
    menuLayout->addLayout(menuBottomLayout, 4);

    containerLayout->addLayout(menuLayout, 1);
    containerLayout->addLayout(mainLayout, 5);

    // connect(homeButton, &MenuButton::clicked, this, &SpyderWindow::onHomeButtonClicked);
    connect(imageButton, &MenuButton::clicked, this, &SpyderWindow::onImageButtonClicked);
    connect(videoButton, &MenuButton::clicked, this, &SpyderWindow::onVideoButtonClicked);
    connect(saveDetectedFacesButton,
            &MenuButton::clicked,
            this,
            &SpyderWindow::onSaveFacesButtonClicked);
    //connect(settingsButton, &MenuButton::clicked, this, &SpyderWindow::onSettingsButtonClicked);
    connect(newSessionButton, &QPushButton::clicked, this, &SpyderWindow::onNewSessionButtonClicked);
    connect(aboutButton, &QPushButton::clicked, this, &SpyderWindow::onAboutButtonClicked);
}

SpyderWindow::~SpyderWindow() {}

void SpyderWindow::onHomeButtonClicked()
{
    // Handle the Home button click
}

void SpyderWindow::onImageButtonClicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open Image"),
        QString(),
        tr("Image Files (*.png *.jpg *.jpeg *.bmp *.gif *.tiff *.ico);;All Files (*)"));

    if (!fileName.isEmpty()) {
        mFaceRecognition->LoadImage(fileName);
        mFaceRecognition->UpdateObservers();
        saveDetectedFacesButton->setDisabled(false);
        imageButton->setDisabled(true);
        videoButton->setDisabled(true);
    }
}

void SpyderWindow::onVideoButtonClicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open Video"),
        QString(),
        tr("Video Files (*.mp4 *.avi *.mkv *.mov *.wmv *.flv);;All Files (*)"));

    if (!fileName.isEmpty()) {
        mFaceRecognition->LoadVideo(fileName, mFaceRecognitionView);
        mFaceRecognition->UpdateObservers();
        saveDetectedFacesButton->setDisabled(false);
        imageButton->setDisabled(true);
        videoButton->setDisabled(true);
    }
}

void SpyderWindow::onSettingsButtonClicked()
{
    // Handle the Settings button click
}

void SpyderWindow::onNewSessionButtonClicked()
{
    mFaceRecognition->Clear();
    imageButton->setDisabled(false);
    videoButton->setDisabled(false);
    saveDetectedFacesButton->setDisabled(true);
    update();
}

void SpyderWindow::onSaveFacesButtonClicked()
{
    if (mFaceDetectionView->IsFacesDetected()) {
        QString folderPath
            = QFileDialog::getExistingDirectory(this,
                                                tr("Select Folder to Save Detected Faces"),
                                                QString(),
                                                QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
        if (folderPath.isEmpty()) {
            // User canceled or didn't select a folder
            return;
        }
        mFaceDetectionView->SaveDetectedFaces(folderPath);
    } else {
        QMessageBox::critical(nullptr, "Error", "No faces Detected!.", QMessageBox::Ok);
        return;
    }
}

void SpyderWindow::onAboutButtonClicked()
{
    QMessageBox aboutBox;
    aboutBox.setWindowTitle("About FaceSpyder");
    QString description
        = "This is a face recognition app which enables users to load media elements like images "
          "and videos to detect faces. It also includes a feature to save the faces detected."
          "<br>For more detailed information, please visit our <a "
          "href='https://github.com/sri0606/FaceSpyder'>official project page</a>.";

    aboutBox.setText(description);
    // Add buttons
    aboutBox.setStandardButtons(QMessageBox::Ok);
    aboutBox.setDefaultButton(QMessageBox::Ok);

    // Add an informative text with URLs
    QString informativeText
        = "<a href='https://github.com/sri0606/FaceSpyder/issues'>Submit bug reports or feature "
          "requests here.</a><br>"
          "<br> Created by <a href='https://sri0606.github.io/'>Sriram Seelamneni</a>";
    aboutBox.setInformativeText(informativeText);

    // Enable Rich Text for URLs
    aboutBox.setTextFormat(Qt::RichText);
    // Display the about box
    aboutBox.exec();
}
